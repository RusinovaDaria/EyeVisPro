#include "NormalMap.h"

NormalMap::NormalMap(std::istream& in) {
    in >> scale;
    in >> amount;
}

Vec3f NormalMap::modifyNormal(const Vec3f& normal, const Vec3f& point) const {
    Vec3f noise;
    double x = point.x / scale;
    double y = point.y / scale;
    double z = point.z / scale;

    noise.x = (float)(perlin.noise(x, y, z));
    noise.y = (float)(perlin.noise(y, z, x));
    noise.z = (float)(perlin.noise(z, x, y));

    return (normal + noise * amount).normalize();
}

Vec3f NormalMap::modifyNormal(const Vec3f& normal, const Vec3f% point, int sin) const
{
    Vec3f noise;
    double x = point.x / scale;
    double y = point.y / scale;
    double z = point.z / scale;

    double arc = atan(float(y)/ z);

    noise.x = (float)(perlin.noise(y, y, z));
    noise.y = (float)(perlin.noise(y, z, y));
    noise.z = (float)(perlin.noise(z, y, y));

    return (normal + noise * amount).normalize();
}