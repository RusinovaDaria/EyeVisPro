#pragma once
#include "geometry.h"
#include "hitpoint.h"
#include "material.h"
#include "transform.h"
#include "texture.h"
#include "normalmap.h"

class Solid
{
public:

    // поиск параметра точки пересечения если она есть
    virtual bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const = 0;

    // поиск точки пересечения если она есть  
    virtual bool ray_intersect(const Vec3f& orig, const Vec3f& dir, HitPoint& hitp, float& dist, bool rotate = false) const = 0;

    virtual Vec3f findN(Vec3f& hit) const = 0;
    virtual Vec3f modifyN(HitPoint& hit) const = 0;

    virtual bool inBorders(Vec3f& point) const { return true; }

    virtual Vec3f get_center() const = 0;
    virtual Material get_material() const = 0;
    virtual Rotation get_rotation() const = 0;

    virtual void set_rotation(const Vec3f& c, float ax, float ay, float az) = 0;
    virtual void set_texture(const Texture& txt) = 0;
    virtual void set_material(const Material& mtr) = 0;
    virtual void set_normal_map(const NormalMap& nm) = 0;
};
