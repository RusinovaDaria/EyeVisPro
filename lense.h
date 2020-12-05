#pragma once
#include "ellipsoid.h"

class Lense : public Ellipsoid
{
public:
    Lense() = default;
    Lense(const Material& m) : Ellipsoid(m) {}
    Lense(Vec3f c, Vec3f d, const Material& m) : Ellipsoid(c, d, m) {}
};
