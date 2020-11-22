#pragma once
#include "raytracer.h"

// задача которую надо выполнить над сценой 
interface struct Task {
    virtual void execute(Scene& scene);
};

ref class RotateCameraTask : Task
{
    float angle_ox;
    float angle_oy;
    float angle_oz;

public:
    RotateCameraTask(float aox, float aoy, float aoz) :
        angle_ox(aox), angle_oy(aoy), angle_oz(aoz) {};

    virtual void execute(Scene& scene)
    {
        scene.get_camera().rotate(angle_ox, angle_oy, angle_oz);
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

    virtual void execute(Scene& scene)
    {
        scene.get_camera().move(dx, dy, dz);
    }
};

ref class RenderSceneTask : Task
{
    System::Drawing::Bitmap^ bitmap;

public:
    RenderSceneTask(System::Drawing::Bitmap^ bmp) : bitmap(bmp) {};

    virtual void execute(Scene& scene)
    {
        render(bitmap, scene);
    }
};


int manageTask(Task^ task);