#pragma once
#include "material.h"
#include "geometry.h"

// ����� ������� ����
struct HitPoint
{
    Vec3f color;
    Material material;
    Vec3f N;
    Vec3f point;
};
