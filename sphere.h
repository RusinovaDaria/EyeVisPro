#pragma once

#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "solid.h"
#include "geometry.h"

class Sphere : public Solid
{
public:

    Material material;
    Vec3f center;
    float radius;
    Rotation rot;

    Texture texture;
    bool is_texture = false;

    NormalMap nmap;
    bool is_normal_map = false;
    
    Sphere() = default;
    Sphere(const Vec3f& c, const float r) : center(c), radius(r) {}
    Sphere(const Vec3f& c, const float r, const Material& m) : material(m), center(c), radius(r) {}
    Sphere(const Vec3f& c, const float r, const Material& m, const Texture& t) : material(m), center(c), radius(r), texture(t), is_texture(true) {}
    Sphere(const Vec3f& c, const float r, const Material& m, const Texture& t, const NormalMap& nm) : material(m), center(c), radius(r), texture(t), is_texture(true), nmap(nm), is_normal_map(true) {}
    Sphere(const Vec3f& c, const float r, const Material& m, const NormalMap& nm, const Rotation& rt) : material(m), center(c), radius(r), nmap(nm), is_normal_map(true), rot(rt) {}
    Sphere(const Vec3f& c, const float r, const Material& m, const NormalMap& nm) : material(m), center(c), radius(r), nmap(nm), is_normal_map(true) {}
    
    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const {
        Vec3f L = center - orig;
        float tca = L * dir;
        float d2 = L * L - tca * tca;
        if (d2 > radius* radius) return false;
        float thc = sqrtf(radius * radius - d2);

        t0 = tca - thc;
        Vec3f p = orig + dir * t0;
        float t1 = tca + thc;

        if (t0 < 0 || !inBorders(p))
        {
            t0 = t1;
            p = orig + dir * t0;
        };

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
            hit.color = get_color(hit.point);
            hit.N = this->findN(hit.point);
            hit.N = this->modifyN(hit);

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

    Vec3f findN(Vec3f& hit) const
    {
        return (hit - center).normalize();
    }
    virtual Vec3f modifyN(HitPoint& hit) const
    {
        if (!is_normal_map)
            return hit.N;

        return nmap.modifyNormal(hit.N, hit.point);
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
    
    virtual void set_rotation(const Vec3f& c, float ax, float ay, float az) { rot.setParameters(c, Vec3f(ax, ay, az)); };
    virtual void set_texture(const Texture& txt) { is_texture = true; texture = txt; }
    virtual void set_material(const Material& mtr) { material = mtr; };
    virtual void set_normal_map(const NormalMap& nm) { is_normal_map = true; nmap = nm; };
    virtual Vec3f get_color(Vec3f point) const
    {
        if (is_texture)
        {
            // проблема: тригонометрические функции долго 
            double teta = asin((point.x - center.x) / radius) / (2.0 * M_PI);
            double gama = atan2((point.y - center.y), (point.z - center.z)) / M_PI;

            float U = 0.5 + teta;
            float V = 0.5 - gama;

            int i = (int)(U * texture.height) % texture.height;
            int j = (int)(V * texture.width) % texture.width;

            return texture.map[i * texture.height + j];
        }

        return material.color;
    }
};

