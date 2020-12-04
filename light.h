#pragma once
#include "geometry.h"

class Light {
public:

    Light() = default;
    Light(const Vec3f& p, const float i) : position(p), intensity(i) {}

    Vec3f position;
    float intensity;
};