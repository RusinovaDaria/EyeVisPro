#pragma once
#include "geometry.h"

class Material {
public:
    Material(const float r, const Vec4f& a, const Vec3f& color, const float spec) : refractive_index(r), albedo(a), color(color), specular_exponent(spec) {}
    Material() : refractive_index(1), albedo(1, 0, 0, 0), color(), specular_exponent() {}
    
    float refractive_index;
    Vec4f albedo;
    Vec3f color;
    float specular_exponent;
};