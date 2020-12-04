#pragma once

#include "geometry.h"
#include "transform.h"

// наблюдатель (камера)
// напрвление взгляда камеры задается углами относительно направления (0,0,-1) (в отрицательное направление оси Z)
class Camera
{
public:

    // где стоит камера
    Vec3f location;

    // куда смотрит камера - углы относительно направления (0,0,-1) вокруг каждой из осей
    // как нужно повернуть вектор (0,0,-1)
    Vec3f sight;

    Camera() = default;
    Camera(const Vec3f& l, const Vec3f& s) : location(l), sight(s) {}

    // подвинуть камеру
    void move(float dx, float dy, float dz)
    {
        location = location + Vec3f(dx, dy, dz);
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
