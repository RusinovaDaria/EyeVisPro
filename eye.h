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
    float cos_87 = cos(0.872665);
    float bord;

public:

    Cornea(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m), bord(c.x - r * cos_87) {};
    bool inBorders(Vec3f& point) const
    {
        return (point.x <= bord);
    }
};

// склера
class Sclera : public Sphere
{
    float cos_65 = cos(0.645772);
    float bord; 
public:

    Sclera(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m), bord(c.x - r * cos_65) {};
    Sclera(const Vec3f& c, const float r, const Material& m, const Texture& t) : Sphere(c, r, m, t, NormalMap(0.08, 0.1)), bord(c.x - r * cos_65) {};
    bool inBorders(Vec3f& point) const
    {
        return (point.x >= bord);
    }
};

// радужка + зрачок 
class Iris : public Sphere
{
    float cos_40 = cos(0.418879);
    float cos_15 = cos(0.15);

    float bord_1;
    float bord_2; 
public:

    Iris(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m), bord_1(c.x - r * cos_15), bord_2(c.x - r * cos_40) {};
    Iris(const Vec3f& c, const float r, const Material& m, const Texture& t) : Sphere(c, r, m, t), bord_1(c.x - r * cos_15), bord_2(c.x - r * cos_40) {};
    Iris(const Vec3f& c, const float r, const Material& m, const Texture& t, const NormalMap& nm) : Sphere(c, r, m, t, nm), bord_1(c.x - r * cos_15), bord_2(c.x - r * cos_40) {};
    bool inBorders(Vec3f& point) const
    {
        return (point.x >= bord_1) && (point.x <= bord_2);
    }

    // override for iris, cause it's not sphere map
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

        return material.color;
    }
};

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
    std::vector<Solid*> components;

    // выпуклая оболочка
    Sphere border;

    // rotation over center
    // models are stored as their 
    // formulas -> to rotate smth
    // formulas variables shoulb be changed
    Rotation rot;

    Eye() = default;
    Eye(const Vec3f& c, float r) : center(c), radius(r), border(c, 1.25 * r)
    {
        // default eye materials
        Material const  cryst_glass(1.0, Vec4f(0.0, 0.1, 0.2, 0.7), Vec3f(0.6, 0.7, 0.8), 125.);
        Material const  cornea_glass(1.0, Vec4f(0.0, 0.1, 0.2, 0.7), Vec3f(0.6, 0.7, 0.8), 125.);
        Material const  blue_iris(1.0, Vec4f(0.5, 0.5, 0.0, 0.0), Vec3f(0., 0.2, 0.8), 10.);
        Material const white_glass(1.0, Vec4f(0.5, 0.8, 0.1, 0.1), Vec3f(0.5, 0.5, 0.5), 125.);
        Material const  red_rubber(1.0, Vec4f(0.9, 0.1, 0.0, 0.0), Vec3f(0.09, 0.01, 0.01), 10.);

        components.push_back(new Cornea(c - Vec3f(0.37 * r, 0, 0), 0.9 * r, cornea_glass));
        components.push_back(new Sclera(c, r * 7 / 6, white_glass));
        components.push_back(new Iris(c + Vec3f(0.8 * r, 0, 0), 1.85 * r, blue_iris));
        components.push_back(new Crystalline(c - Vec3f(0.82 * r, 0, 0), 0.7 * r, red_rubber));
        components.push_back(new Sphere(c + Vec3f(0.1 * r, 0, 0), 0.8 * r, red_rubber));
    }

    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const 
    { return false; }

    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, HitPoint& hit, float& dist, bool rotate = false) const
    {
            Vec3f new_orig = rotate ? to_cartesian(get_rotation().getMatrix() * to_homogeneous(orig, 1)) : orig;
            Vec3f new_dir = rotate ? to_cartesian(get_rotation().getMatrix() * to_homogeneous(dir, 0)) : dir;

            float t;

            // если есть пересечение с оболочкой
            if (border.ray_intersect(new_orig, new_dir, t))
            {
                bool is_intersect = false;
                for (int i = 0; i < components.size(); i++)
                {
                    // проверяем пересечение с очередным компонентом
                    if (components[i]->ray_intersect(new_orig, new_dir, hit, dist))
                        is_intersect = true;
                }

                // если точка пересечения найдена и объект нужно повернуть
                if (rotate)
                {
                    hit.point = to_cartesian(get_rotation().getMatrix_inv() * to_homogeneous(hit.point, 1));
                    hit.N = to_cartesian(get_rotation().getMatrix_inv() * to_homogeneous(hit.N, 0));
                }


                return is_intersect && (dist < 1000);
            }

        return false;
    }

    Vec3f findN(Vec3f& hit) const
    {
        return (hit - center).normalize();
    }

    Vec3f modifyN(HitPoint& hit) const
    {
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
    void set_texture(const Texture& txt) {};
    void set_material(const Material& mtr) {};
    void set_normal_map(const NormalMap& nm) {};

    void set_iris_texture(const Texture& txt) { components[2]->set_texture(txt); };
    void set_sclera_texture(const Texture& txt) { components[1]->set_texture(txt); };
    void set_sclera_normal_map(const NormalMap& nm) { components[1]->set_normal_map(nm); };
};

//std::istream& operator>> (std::istream& is, Eye& eye);

