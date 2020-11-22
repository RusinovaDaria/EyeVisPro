#pragma once
#include "geometry.h"
#include "hitpoint.h"
#include "material.h"
#include "transform.h"
#include "sphere.h"
#include "ellipsoid.h"

// роговица
class Cornea : public Sphere
{
public:

    Cornea(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m) {};
    bool inBorders(Vec3f& point) const
    {
        return (point.x <= center.x - radius * cos(0.872665));
    }
};

// склера
class Sclera : public Sphere
{
public:

    Sclera(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m) {};
    Sclera(const Vec3f& c, const float r, const Material& m, const Texture& t) : Sphere(c, r, m, t) {};
    Sclera(const Vec3f& c, const float r, const Material& m, const Texture& t, const NormalMap& nm) : Sphere(c, r, m, t, nm) {};
    bool inBorders(Vec3f& point) const
    {
        return (point.x >= center.x - radius * cos(0.645772));
    }

    Vec3f modifyN(HitPoint& hit) const
    {
        //if (is_normal_map && hit.point.x > this->center.x - 0.2 * this->radius)
        //    return nmap.modifyNormal(hit.N, hit.point, 1);

        if (is_normal_map)
        {
            NormalMap map(0.08, 0.1);
            return map.modifyNormal(hit.N, hit.point, 1);
        }

        return hit.N;
    }
};

// радужка + зрачок 
class Iris : public Sphere
{
public:

    Iris(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m) {};
    Iris(const Vec3f& c, const float r, const Material& m, const Texture& t) : Sphere(c, r, m, t) {};
    Iris(const Vec3f& c, const float r, const Material& m, const Texture& t, const NormalMap& nm) : Sphere(c, r, m, t, nm) {};
    bool inBorders(Vec3f& point) const
    {
        return (point.x >= center.x - radius * cos(0.15)) && (point.x <= center.x - radius * cos(0.418879));
    }

    Vec3f modifyN(HitPoint& hit) const
    {
        if (is_normal_map)
        {
            NormalMap map(fabsf(hit.point.x - this->center.x) / this->radius,
                fabsf(hit.point.x - this->center.x) / this->radius);
            return nmap.modifyNormal(hit.N, hit.point);
        }

        return hit.N;
    }

    Vec3f get_color(Vec3f point) const
    {
        if (is_texture)
        {
            Vec3f v = findN(point);
            float U = v.z * 0.5 / 0.418879 + 0.5;
            float V = v.y * 0.5 / 0.418879 + 0.5;

            int i = (int)(U * texture.height) % texture.height;
            int j = (int)(V * texture.width) % texture.width;

            return texture.map[i * texture.height + j];
        }

        return material.diffuse_color;
    }

};

// стекловидное тело 
//class Vitreous : public Sphere
//{
//public:
//
//    Vitreous(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m) { };
//    bool inBorders(Vec3f& point) const
//    {
//        return (point.x <= center.x - radius * cos(0.418879));
//    }
//};

// хрусталик crystalline 
class Crystalline : public Ellipsoid
{
public:

    Crystalline(const Vec3f& c, const float r, const Material& m) : Ellipsoid(c, Vec3f(0.3 * r, r, r), m) {};
};

class Eye : public Solid
{

public:
    Vec3f center;
    float radius;
    Rotation rot;
    std::vector<Solid*> components;
    Sphere border;

    Eye(const Vec3f& c, float r) : center(c), radius(r), border(c, 1.25 * r, Material())
    {
        Material  cryst_glass(1.0, Vec4f(0.0, 0.1, 0.2, 0.7), Vec3f(0.6, 0.7, 0.8), 125.);
        Material  cornea_glass(1.0, Vec4f(0.0, 0.1, 0.2, 0.7), Vec3f(0.6, 0.7, 0.8), 125.);
        Material  blue_iris(1.0, Vec4f(0.5, 0.5, 0.0, 0.0), Vec3f(0., 0.2, 0.8), 10.);
        Material white_glass(1.0, Vec4f(0.5, 0.8, 0.1, 0.1), Vec3f(0.5, 0.5, 0.5), 125.);
        Material  red_rubber(1.0, Vec4f(0.9, 0.1, 0.0, 0.0), Vec3f(0.09, 0.01, 0.01), 10.);

        Texture sclera_texture("1_1.bmp");
        Texture iris_texture("447_3.bmp");
        NormalMap sclera_nmap(0.1, 0.2);
        NormalMap iris_nmap(0.2, 0.5);


        //components.push_back(new Sphere(c, 1.25*r, cornea_glass));
        components.push_back(new Cornea(c - Vec3f(0.37 * r, 0, 0), 0.9 * r, cornea_glass));
        components.push_back(new Sclera(c, r * 7 / 6, white_glass, sclera_texture, sclera_nmap));
        components.push_back(new Iris(c + Vec3f(0.8 * r, 0, 0), 1.85 * r, blue_iris, iris_texture, iris_nmap));
        components.push_back(new Crystalline(c - Vec3f(0.82 * r, 0, 0), 0.7 * r, red_rubber));
        components.push_back(new Sphere(c + Vec3f(0.1 * r, 0, 0), 0.8 * r, red_rubber));
    }

    Eye(const Vec3f& c, float r, const Rotation& rt) : center(c), rot(rt), radius(r), border(c, 1.25 * r, Material())
    {
        Material  cryst_glass(1.0, Vec4f(0.0, 0.1, 0.2, 0.7), Vec3f(0.6, 0.7, 0.8), 125.);
        Material  cornea_glass(1.0, Vec4f(0.0, 0.1, 0.2, 0.7), Vec3f(0.6, 0.7, 0.8), 125.);
        Material  blue_iris(1.0, Vec4f(0.5, 0.5, 0.0, 0.0), Vec3f(0., 0.2, 0.8), 10.);
        Material white_glass(1.0, Vec4f(0.5, 0.8, 0.1, 0.1), Vec3f(0.5, 0.5, 0.5), 125.);
        Material  red_rubber(1.0, Vec4f(0.9, 0.1, 0.0, 0.0), Vec3f(0.09, 0.01, 0.01), 10.);

        Texture sclera_texture("1_1.bmp");
        Texture iris_texture("447_3.bmp");
        NormalMap sclera_nmap(0.1, 0.2);
        NormalMap iris_nmap(0.2, 0.5);


        //components.push_back(new Sphere(c, 1.25*r, cornea_glass));
        components.push_back(new Cornea(c - Vec3f(0.37 * r, 0, 0), 0.9 * r, cornea_glass));
        components.push_back(new Sclera(c, r * 7 / 6, white_glass, sclera_texture, sclera_nmap));
        components.push_back(new Iris(c + Vec3f(0.8 * r, 0, 0), 1.85 * r, red_rubber, iris_texture, iris_nmap));
        components.push_back(new Crystalline(c - Vec3f(0.82 * r, 0, 0), 0.7 * r, red_rubber));
        components.push_back(new Sphere(c + Vec3f(0.1 * r, 0, 0), 0.8 * r, red_rubber));
    }

    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const { return false; }

    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, HitPoint& hit, float& dist, bool rotate = false) const
    {
        if (rotate)
        {
            Vec3f new_orig = to_cartesian(get_rotation().getMatrix() * to_homogeneous(orig, 1));
            Vec3f new_dir = to_cartesian(get_rotation().getMatrix() * to_homogeneous(dir, 0));

            float t;
            bool is_intersect;
            if (border.ray_intersect(new_orig, new_dir, t))
            {
                for (int i = 0; i < components.size(); i++)
                {
                    // проверяем пересечение с очередным компонентом
                    if (components[i]->ray_intersect(new_orig, new_dir, hit, dist))
                        is_intersect = true;

                }

                hit.point = to_cartesian(get_rotation().getMatrix_inv() * to_homogeneous(hit.point, 1));
                hit.N = to_cartesian(get_rotation().getMatrix_inv() * to_homogeneous(hit.N, 0));

                return is_intersect && (dist < 1000);
            }
        }
        else
        {
            float t;
            bool is_intersect;
            if (border.ray_intersect(orig, dir, t))
            {

                for (int i = 0; i < components.size(); i++)
                {
                    // проверяем пересечение с очередным компонентом
                    if (components[i]->ray_intersect(orig, dir, hit, dist))
                        is_intersect = true;
                }

                return is_intersect && (dist < 1000);
            }
        }

        return false;
    }

    Vec3f findN(Vec3f& hit) const
    {
        return (hit - center).normalize();
    }
    Vec3f modifyN(HitPoint& hit) const
    {
        ////if (is_normal_map && hit.point.x > this->center.x)
        ////    return nmap.modifyNormal(hit.N, hit.point, 1);
        //
        //if (is_normal_map)
        //{
        //    NormalMap map(0.1, 0.1);
        //    return map.modifyNormal(hit.N, hit.point, 1);
        //}

        return hit.N;
    }

    Vec3f get_center() const
    {
        return center;
    }
    Material get_material() const
    {
        return Material();
    }
    Rotation get_rotation() const { return rot; };
    void set_rotation(const Vec3f& c, float ax, float ay, float az) { rot.setParameters(c, Vec3f(ax, ay, az)); };
};

