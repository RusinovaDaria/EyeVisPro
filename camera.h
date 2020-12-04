#pragma once

#include "geometry.h"
#include "transform.h"

// ����������� (������)
// ���������� ������� ������ �������� ������ ������������ ����������� (0,0,-1) (� ������������� ����������� ��� Z)
class Camera
{
public:

    // ��� ����� ������
    Vec3f location;

    // ���� ������� ������ - ���� ������������ ����������� (0,0,-1) ������ ������ �� ����
    // ��� ����� ��������� ������ (0,0,-1)
    Vec3f sight;

    Camera() = default;
    Camera(const Vec3f& l, const Vec3f& s) : location(l), sight(s) {}

    // ��������� ������
    void move(float dx, float dy, float dz)
    {
        location = location + Vec3f(dx, dy, dz);
    }

    //  ��������� ������ (��������� ������ ������������ ������������ ������)
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
