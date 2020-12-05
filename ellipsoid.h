#pragma once

#include "solid.h"
#include "geometry.h"
#include "hitpoint.h"
#include "material.h"
#include "transform.h"

class Ellipsoid : public Solid {
public:

    Material material;
    Vec3f center;
    Vec3f d;
    Rotation rot;

    NormalMap nmap;
    bool is_normal_map = false;

    float dx_2 = 0.5;
    float dy_2 = 0.5;
    float dz_2 = 0.5;

    Ellipsoid(): d(Vec3f(1, 1, 1)) {}
    Ellipsoid(const Material& m) : material(m), center(Vec3f(0, 0, 0)), d(Vec3f(1, 1, 1)) {}
    Ellipsoid(Vec3f c, Vec3f d, const Material& m) : material(m), center(c), d(d),
        dx_2(d.x * d.x / 2.), dy_2(d.y * d.y / 2.), dz_2(d.z*d.z / 2.) {}

    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const {

        Vec3f OC = orig - center;

        float a = 0;
        float b = 0;
        float c = 0;
        for (size_t i = 0; i < 3; i++)
        {
            float dd_i = d[i] * d[i];

            a += (dir[i] * dir[i]) / dd_i;
            b += (dir[i] * OC[i]) / dd_i;
            c += (OC[i] * OC[i]) / dd_i;
        }
        c -= 1;
        b *= 2;

        float root = b * b - 4 * a * c;
        if (root < 0) return false;

        float sqrt_root = sqrt(root);
        float a_2 = 2 * a;

        t0 = (-b - sqrt_root) / a_2;
        Vec3f p = orig + dir * t0;

        if (t0 < 0 || !inBorders(p))
        {
            t0 = (-b + sqrt_root) / a_2;
            p = orig + dir * t0;
        }

        if (t0 < 0 || !inBorders(p)) return false;

        return true;
    }
    
    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, HitPoint& hit, float& dist, bool rotate = false) const
    {
        Vec3f new_orig = rotate ? to_cartesian(get_rotation().getMatrix() * to_homogeneous(orig, 1)) : orig;
        Vec3f new_dir = rotate ? to_cartesian(get_rotation().getMatrix() * to_homogeneous(dir, 0)) : dir;
        float t0;
        if (ray_intersect(new_orig, new_dir, t0) && t0 < dist)
        {
            hit.point = new_orig + new_dir * t0;
            hit.color = this->material.color;
            hit.N = this->findN(hit.point);

            if (rotate)
            {
                hit.point = to_cartesian(get_rotation().getMatrix_inv() * to_homogeneous(hit.point, 1));
                hit.N = to_cartesian(get_rotation().getMatrix_inv() * to_homogeneous(hit.N, 0));
            }

            hit.material = this->material;
            dist = t0;

            return true;
        }

        return false;
    }

    Vec3f findN(Vec3f& hit) const {

        float dX = (hit.x - center.x) / dx_2;
        float dY = (hit.y - center.y) / dy_2;
        float dZ = (hit.z - center.z) / dz_2;
        
        return Vec3f(dX, dY, dZ).normalize();
    }

    Vec3f get_center() const
    {
        return center;
    }
    Material get_material() const
    {
        return material;
    }
    Rotation get_rotation() const { return rot; };
    
    void set_rotation(const Vec3f& c, float ax, float ay, float az) { rot.setParameters(c, Vec3f(ax, ay, az)); };
    virtual Vec3f modifyN(HitPoint& hit) const
    {
        return hit.N;
    }
    virtual Vec3f get_color(Vec3f point) const
    {
        return material.color;
    }

    virtual void set_texture(const Texture& txt) {};
    virtual void set_material(const Material& mtr) { material = mtr; };
    virtual void set_normal_map(const NormalMap& nm) { is_normal_map = true; nmap = nm; };
    
};

