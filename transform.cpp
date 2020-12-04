#include "transform.h"

vec<4, Vec4f> identity_mtrx()
{
    return vec<4, Vec4f>(
        Vec4f(1, 0, 0, 0),
        Vec4f(0, 1, 0, 0),
        Vec4f(0, 0, 1, 0),
        Vec4f(0, 0, 0, 1)
        );
}

Vec4f to_homogeneous(const Vec3f& v, int is_point)
{
    return Vec4f(v[0], v[1], v[2], is_point);
}

Vec3f to_cartesian(const Vec4f& v)
{
    return Vec3f(v[0], v[1], v[2]);
}

Vec3f rotate_Ox(const Vec3f& v, float rotx, const Vec3f& c, int dir)
{
    if (rotx)
    {
        float _sin = sin(dir * rotx);
        float _cos = cos(dir * rotx);

        float new_y = c.y + _cos * (-c.y + v.y) + _sin * (-c.z + v.z);
        float new_z = c.z - _sin * (-c.y + v.y) + _cos * (-c.z + v.z);

        return Vec3f(v.x, new_y, new_z);
    }

    return v;
}

Vec3f rotate_Oy(const Vec3f& v, float roty, const Vec3f& c, int dir)
{
    if (roty)
    {
        float _sin = sin(dir * roty);
        float _cos = cos(dir * roty);

        float new_x = c.x + _cos * (v.x - c.x) + _sin * (v.z - c.z);
        float new_z = c.z - _sin * (v.x - c.x) + _cos * (v.z - c.z);

        return Vec3f(new_x, v.y, new_z);
    }

    return v;
}

Vec3f rotate_Oz(const Vec3f& v, float rotz, const Vec3f& c, int dir)
{
    if (rotz)
    {
        float _sin = sin(dir * rotz);
        float _cos = cos(dir * rotz);

        float new_x = c.x + _cos * (v.x - c.x) + _sin * (v.y - c.y);
        float new_y = c.y - _sin * (v.x - c.x) + _cos * (v.y - c.y);

        return Vec3f(new_x, new_y, v.z);
    }

    return v;
}