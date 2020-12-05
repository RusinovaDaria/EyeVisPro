#pragma once

#include <ctime>
#include "raytracer.h"
#include "eye.h"
#include "utils.h"
#include <string.h>
#include <fstream>
#include "filemanager.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Drawing;

// задача которую надо выполнить над сценой 
// взаимодействует с интерфейсом
interface struct Task {
    virtual int execute(Scene& scene);
};

int manageTask(Task^ task);

ref class UpdateLabelTask : Task
{
    Label^ label;

public:
    UpdateLabelTask(Label^ lbl) : label(lbl) {};

    virtual int execute(Scene& scene)
    {
        Vec3f pos = scene.get_camera().get_location();
        Vec3f sight = scene.get_camera().get_sight() * 57.3;
        label->Text = String::Format("location : ({0:0.##}  {1:0.##}  {2:0.##}), sight angle : ({3:0.##}  {4:0.##}  {5:0.##})",
            pos.x, pos.y, pos.z,
            sight.x, sight.y, sight.z);

        return 0;
    }
};


ref class RotateCameraTask : Task
{
    float angle_ox;
    float angle_oy;
    float angle_oz;

    Label^ label;

public:
    RotateCameraTask(float aox, float aoy, float aoz, Label^ lbl) :
        angle_ox(aox), angle_oy(aoy), angle_oz(aoz), label(lbl) {};

    virtual int execute(Scene& scene)
    {
        scene.get_camera().rotate(angle_ox, angle_oy, angle_oz);
        manageTask(gcnew UpdateLabelTask(label));

        return 0;
    }
};

ref class MoveCameraTask : Task
{
    float dx;
    float dy;
    float dz;

    Label^ label;

public:
    MoveCameraTask(float dx_p, float dy_p, float dz_p, Label^ lbl) :
        dx(dx_p), dy(dy_p), dz(dz_p), label(lbl) {};

    virtual int execute(Scene& scene)
    {
        scene.get_camera().move(dx, dy, dz);
        manageTask(gcnew UpdateLabelTask(label));

        return 0;
    }
};

ref class DeleteCameraTask : Task
{
    // delete from camera ud
    DomainUpDown^ cameras_ud;

    // delete from bmps 
    List<Bitmap^>^ bitmaps;
    
public:

    DeleteCameraTask(DomainUpDown^ ud, List<Bitmap^>^ bmps) : cameras_ud(ud), bitmaps(bmps) {};

    virtual int execute(Scene& scene)
    {
        int index = cameras_ud->SelectedIndex;

        // delete from scene
        std::vector<Camera>& cameras = scene.get_cameras();
        cameras.erase(cameras.begin() + index);
        int last_index = cameras.size() - 1;
        
        // delete from inteface
        bitmaps->RemoveAt(index);

        cameras_ud->Items->RemoveAt(index);
        cameras_ud->SelectedIndex = std::min(index, last_index);

        return 0;
    }
};

ref class RenderSceneTask : Task
{
    Bitmap^ bitmap;

public:
    RenderSceneTask(Bitmap^ bmp) : bitmap(bmp) {};

    virtual int execute(Scene& scene)
    {
        render(bitmap, scene);
        return 0;
    }
};

ref class RenderAllTask : Task
{
    List<Bitmap^>^ bitmaps;

public:
    RenderAllTask(List<Bitmap^>^ bmps) : bitmaps(bmps) {};

    virtual int execute(Scene& scene)
    {
        clock_t start = std::clock();
        std::vector<Camera> cams = scene.get_cameras();

        if (cams.size() == 1)
            render(bitmaps[0], scene);
        else
        {
            #pragma omp parallel for
            for (int i = 0; i < bitmaps->Count; i++)
            {
                render(bitmaps[i], scene, cams[i]);
            }
        }

        clock_t end = std::clock();
        
        FILE* f;
        f = fopen("log.txt", "w");
        fprintf(f, "time: %ld\n", end - start);
        fclose(f);

        return 0;
    }
};

ref class LoadFromFileTask : Task 
{
    System::String ^filepath;

public:

    LoadFromFileTask(char* path) 
    {
        std::string scene_path;
        std::ifstream config_file(path);

        if (!config_file.is_open())
            throw std::exception("Can't open config file");
            
        if (!std::getline(config_file, scene_path))
            throw("Reading path to scene file failed");

        filepath = gcnew System::String(scene_path.c_str());
    };
        
    virtual int execute(Scene& scene)
    {
        return FileManager::read_scene(filepath, scene);
    }
};

ref class SetActiveCameraTask : Task
{
    size_t indx;
    Label^ label;

public:

    SetActiveCameraTask(size_t i, Label^ lbl) : indx(i), label(lbl) {};

    virtual int execute(Scene& scene)
    {
        scene.set_active_camera(indx);
        
        Vec3f pos = scene.get_camera().get_location();
        Vec3f sight = scene.get_camera().get_sight() * 57.3;
        label->Text = String::Format("location : ({0:0.##}  {1:0.##}  {2:0.##}), sight angle : ({3:0.##}  {4:0.##}  {5:0.##})",
            pos.x, pos.y, pos.z, 
            sight.x, sight.y, sight.z);

        return 0;
    };
};

ref class FillWidgetsTask : Task
{
    DomainUpDown^ updown;
    Label^ label;

public:
    FillWidgetsTask(DomainUpDown^ ud, Label^ lbl) : updown(ud), label(lbl) {};

    virtual int execute(Scene& scene)
    {
        updown->Items->Clear();
        std::vector<Camera> cams = scene.get_cameras();
        for (int i = 0; i < cams.size(); i++)
        {
            System::String^ msg = System::String::Format("camera {0,3:D2}", i);
            updown->Items->Add(msg);
        }

        manageTask(gcnew SetActiveCameraTask(0, label));

        updown->SelectedItem = updown->Items[0];
        updown->Update();
        updown->Refresh();
        return 0;
    };
};

ref class AddCameraTask : Task
{
    DomainUpDown^ updown;
    Panel^ panel;
    List<Bitmap^>^ bitmaps;
    Label^ label;

    float pos_x;
    float pos_y;
    float pos_z;

    float ang_x;
    float ang_y;
    float ang_z;

public:
    AddCameraTask(float px, float py, float pz,
        float ax, float ay, float az, DomainUpDown^ ud,
        Panel^ pl, List<Bitmap^>^ bmps, Label^ lbl) :
        pos_x(px), pos_y(py), pos_z(pz),
        ang_x(ax), ang_y(ay), ang_z(az), updown(ud),
        panel(pl), bitmaps(bmps), label(lbl) {};

    virtual int execute(Scene& scene)
    {
        int indx = updown->Items->Count;

        // add camera to scene and set it as active
        scene.add_camera(Camera(Vec3f(pos_x, pos_y, pos_z), Vec3f(ang_x, ang_y, ang_z)));
        scene.set_active_camera(indx);

        // add camera to widgets
        Int32 prev = Convert::ToInt32(updown->Items[indx - 1]->ToString()->Substring(6));
        System::String^ cam_msg = System::String::Format("camera {0,3:D2}", prev+1);
        updown->Items->Add(cam_msg);
        manageTask(gcnew SetActiveCameraTask(indx, label));

        bitmaps->Add(gcnew Bitmap(panel->Width, panel->Height));
        manageTask(gcnew RenderSceneTask(bitmaps[indx]));

        updown->SelectedIndex = indx;
        updown->Update();
        updown->Refresh();

        return 0;
    }
};

