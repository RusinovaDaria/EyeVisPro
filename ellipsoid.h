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

    Ellipsoid(const Material& m) : material(m), center(Vec3f(0, 0, 0)), d(Vec3f(1, 1, 1)) {}
    Ellipsoid(Vec3f c, Vec3f d, const Material& m) : material(m), center(c), d(d) {}

    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const {

        Vec3f OC = orig - center;


        float a = 0;
        float b = 0;
        float c = 0;
        for (size_t i = 0; i < 3; i++)
        {
            a += (dir[i] * dir[i]) / (d[i] * d[i]);
            b += (dir[i] * OC[i]) / (d[i] * d[i]);
            c += (OC[i] * OC[i]) / (d[i] * d[i]);
        }
        c -= 1;
        b *= 2;

        float root = b * b - 4 * a * c;
        if (root < 0) return false;

        t0 = (-b - sqrt(root)) / (2 * a);
        Vec3f p = orig + dir * t0;

        if (t0 < 0 || !inBorders(p))
        {
            t0 = (-b + sqrt(root)) / (2 * a);
            p = orig + dir * t0;
        }

        if (t0 < 0 || !inBorders(p)) return false;

        return true;
    }
    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, HitPoint& hit, float& dist, bool rotate = false) const
    {
        if (rotate)
        {
            Vec3f new_orig = to_cartesian(get_rotation().getMatrix() * to_homogeneous(orig, 1));
            Vec3f new_dir = to_cartesian(get_rotation().getMatrix() * to_homogeneous(dir, 0));
            float t0;
            if (ray_intersect(new_orig, new_dir, t0) && t0 < dist)
            {
                hit.point = new_orig + new_dir * t0;
                hit.color = this->material.diffuse_color;
                hit.N = this->findN(hit.point);

                hit.point = to_cartesian(get_rotation().getMatrix_inv() * to_homogeneous(hit.point, 1));
                hit.N = to_cartesian(get_rotation().getMatrix_inv() * to_homogeneous(hit.N, 0));

                hit.material = this->material;
                dist = t0;

                return true;

            }
        }
        else
        {
            float t0;
            if (ray_intersect(orig, dir, t0) && t0 < dist)
            {
                hit.point = orig + dir * t0;
                hit.color = this->material.diffuse_color;
                hit.N = this->findN(hit.point);

                hit.material = this->material;
                dist = t0;

                return true;

            }
        }

        return false;
    }

    Vec3f findN(Vec3f& hit) const {

        float dX = 2 * (hit.x - center.x) / (d.x * d.x);
        float dY = 2 * (hit.y - center.y) / (d.y * d.y);
        float dZ = 2 * (hit.z - center.z) / (d.z * d.z);
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
};

