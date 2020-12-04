#pragma once
#include "material.h"
#include "geometry.h"

// точка падения луча
struct HitPoint
{
    Vec3f color;
    Material material;
    Vec3f N;
    Vec3f point;
};
