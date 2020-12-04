#pragma once

#include "perlinnoise.h"
#include "geometry.h"
#include <iostream>

class NormalMap {
private:
    PerlinNoise perlin;
    double scale;
    double amount;

public:
    NormalMap(double s, double a) : scale(s), amount(a) {};
    NormalMap() = default;

    Vec3f modifyNormal(const Vec3f& n, const Vec3f& p) const;
    Vec3f modifyNormal(const Vec3f& n1, const Vec3f% p, int sin) const;
};
