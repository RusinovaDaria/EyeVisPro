#pragma once

#include <ctime>
#include "raytracer.h"
#include "eye.h"
#include "utils.h"
#include <string.h>
#include <fstream>
#include "filemanager.h"

using namespace System::Windows::Forms;

// задача которую надо выполнить над сценой 
// взаимодействует с интерфейсом
interface struct Task {
    virtual int execute(Scene& scene);
};

ref class RotateCameraTask : Task
{
    float angle_ox;
    float angle_oy;
    float angle_oz;

public:
    RotateCameraTask(float aox, float aoy, float aoz) :
        angle_ox(aox), angle_oy(aoy), angle_oz(aoz) {};

    virtual int execute(Scene& scene)
    {
        scene.get_camera().rotate(angle_ox, angle_oy, angle_oz);
        return 0;
    }
};

ref class MoveCameraTask : Task
{
    float dx;
    float dy;
    float dz;

public:
    MoveCameraTask(float dx_p, float dy_p, float dz_p) :
        dx(dx_p), dy(dy_p), dz(dz_p) {};

    virtual int execute(Scene& scene)
    {
        scene.get_camera().move(dx, dy, dz);
        return 0;
    }
};

ref class AddCameraTask : Task 
{
    DomainUpDown^ updown;

    float pos_x;
    float pos_y;
    float pos_z;

    float ang_x;
    float ang_y;
    float ang_z;

public:
    AddCameraTask(float px, float py, float pz, 
        float ax, float ay, float az, DomainUpDown^ud) :
        pos_x(px), pos_y(py), pos_z(pz),
        ang_x(ax), ang_y(ay), ang_z(az), updown(ud) {};

    virtual int execute(Scene& scene)
    {
        scene.add_camera(Camera(Vec3f(pos_x, pos_y, pos_z), Vec3f(ang_x, ang_y, ang_z)));
        int indx = updown->Items->Count;


        System::String^ cam_msg = System::String::Format("camera {0}", indx);
        updown->Items->Add(cam_msg);

        scene.set_active_camera(indx);
        updown->SelectedItem = updown->Items[indx];

        updown->Update();
        updown->Refresh();

        return 0;
    }
};

ref class RenderSceneTask : Task
{
    System::Drawing::Bitmap^ bitmap;

public:
    RenderSceneTask(System::Drawing::Bitmap^ bmp) : bitmap(bmp) {};

    virtual int execute(Scene& scene)
    {
        render(bitmap, scene);
        return 0;
    }
};

ref class RenderAllTask : Task
{
    System::Collections::Generic::List<System::Drawing::Bitmap^>^ bitmaps;

public:
    RenderAllTask(System::Collections::Generic::List<System::Drawing::Bitmap^>^ bmps) : bitmaps(bmps) {};

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

        if (config_file.is_open() && std::getline(config_file, scene_path))
            filepath = gcnew System::String(scene_path.c_str());
    };
        
    virtual int execute(Scene& scene)
    {
        return FileManager::read_scene(filepath, scene);
    }
};

ref class FillWidgetsTask : Task
{
    System::Windows::Forms::DomainUpDown^ updown;
public:
    FillWidgetsTask(System::Windows::Forms::DomainUpDown^ ud) : updown(ud) {};

    virtual int execute(Scene& scene) 
    {
        updown->Items->Clear();

        std::vector<Camera> cams = scene.get_cameras();
        for (int i = 0; i < cams.size(); i++)
        {
            System::String ^msg = System::String::Format("camera {0}", i);
            updown->Items->Add(msg);
        }

        updown->SelectedItem = updown->Items[0];
        updown->Update();
        updown->Refresh();
        return 0;
    };
};



ref class SetActiveCameraTask : Task
{
    size_t indx;
public:

    SetActiveCameraTask(size_t i) : indx(i) {};

    virtual int execute(Scene& scene)
    {
        scene.set_active_camera(indx);
        return 0;
    };
};

int manageTask(Task^ task);