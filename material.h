#pragma once
#include "geometry.h"

class Material {
public:
    Material(const float r, const Vec4f& a, const Vec3f& color) : refractive_index(r), coeffs(a), color(color) {}
    Material() : refractive_index(1), coeffs(1, 0, 0, 0), color() {}
    
    float refractive_index;
    Vec4f coeffs;
    Vec3f color;
};