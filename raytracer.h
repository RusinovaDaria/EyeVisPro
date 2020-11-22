#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "geometry.h"
#include "poly.h"
#include "transform.h"
#include "normalmap.h"
#include "texture.h"
#include "material.h"
#include "solid.h"

// наблюдатель (камера)
// напрвление взгляда камеры задается углами относительно направления (0,0,-1) (в отрицательное направление оси Z)
class Camera
{
    // где стоит камера
    Vec3f location;

    // куда смотрит камера - углы относительно направления (0,0,-1) вокруг каждой из осей
    // как нужно повернуть вектор (0,0,-1)
    Vec3f sight;

public:

    Camera(const Vec3f& l, const Vec3f& s): location(l), sight(s){}

    // подвинуть камеру
    void move(float dx, float dy, float dz)
    {
        Movement mov(dx, dy, dz);
        Vec3f newloc = to_cartesian(mov.getMatrix() * to_homogeneous(location, 1)).normalize();
        location = newloc;
    }

    //  повернуть камеру (повернуть взгляд относительно расположения камеры)
    void rotate(float ax, float ay, float az)
    {
        sight = sight + Vec3f(ax, ay, az);
    }

    void set_location(const Vec3f& newloc)
    {
        location = newloc;
    }

    void set_sight(const Vec3f& newsight)
    {
        sight = newsight; 
    }

    const Vec3f& get_location() const
    {
        return location;
    }

    const Vec3f& get_sight() const
    {
        return sight;
    }
};

class Light { 
public:

    Light(const Vec3f& p, const float i) : position(p), intensity(i) {}
    Vec3f position;
    float intensity;
};

// сцена = наблюдатель, тела, источники света
class Scene
{
    // камера
    Camera camera;

    // тела сцены: вектор указателей
    std::vector<std::shared_ptr<Solid>> solids;

    // источники света
    std::vector<Light> lights;

public:

    Scene(const Camera& cam) : camera(cam) {};
    Scene(const Camera& cam, const std::vector<Light>& lgh) : camera(cam), lights(lgh) {};
    Scene(const Camera& cam, const std::vector<Light>& lgh, const std::vector<std::shared_ptr<Solid>>& sld) : camera(cam), lights(lgh), solids(sld) {};

    void add_solid(std::shared_ptr<Solid> s) { solids.push_back(s); }

    Camera& get_camera() { return camera; };
    std::vector<std::shared_ptr<Solid>>& get_solids() { return solids; };
    std::vector<Light>& get_lights() { return lights; };

};

Vec3f reflect(const Vec3f& I, const Vec3f& N);
Vec3f refract(const Vec3f& I, const Vec3f& N, const float eta_t, const float eta_i = 1.f);

bool scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<std::shared_ptr<Solid>>& solids, HitPoint& hit);
Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, const std::vector<std::shared_ptr<Solid>>& solids, const std::vector<Light>& lights, size_t depth = 0);
void render(System::Drawing::Bitmap^ bmp, Scene& scene);