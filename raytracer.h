#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "geometry.h"
#include "poly.h"
#include "transform.h"

// enviromantal map 
class Texture
{
public:

    // �������
    size_t height;
    size_t width;

    // ������� ������
    std::shared_ptr<Vec3f[]> map;

    Texture() = default;

    // ��������� �������� �� �����
    Texture(System::String^ filepath)
    {
        System::Drawing::Bitmap bmp(filepath);
        height = bmp.Height;
        width = bmp.Width;

        map = std::shared_ptr<Vec3f[]>(new Vec3f[width * height]);
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                System::Drawing::Color c = bmp.GetPixel(i, j);
                map[i * height + j] = Vec3f(c.R / 255., c.G / 255., c.B / 255.);
            }
        }
    }
};

class Light { 
public:

    Light(const Vec3f& p, const float i) : position(p), intensity(i) {}
    Vec3f position;
    float intensity;
};

class Material {
public:
    Material(const float r, const Vec4f& a, const Vec3f& color, const float spec) : refractive_index(r), albedo(a), diffuse_color(color), specular_exponent(spec) {}
    Material() : refractive_index(1), albedo(1, 0, 0, 0), diffuse_color(), specular_exponent() {}
    
    float refractive_index;
    Vec4f albedo;
    Vec3f diffuse_color;
    float specular_exponent;
};

// ����� ������� ����
struct HitPoint
{
    Vec3f color;
    Material material;
    Vec3f N;
    Vec3f point;
};

class Solid 
{
public:

    // ����� ��������� ����� ����������� ���� ��� ����
    virtual bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const = 0;

    // ����� ����� ����������� ���� ��� ����  
    virtual bool ray_intersect(const Vec3f& orig, const Vec3f& dir, HitPoint& hitp, float& dist, bool rotate = false) const = 0;

    virtual Vec3f findN(Vec3f& hit) const = 0;
    virtual bool inBorders(Vec3f& point) const { return true; }
    
    virtual Vec3f get_center() const = 0;
    virtual Material get_material() const = 0;
    virtual Rotation get_rotation() const = 0; 

    virtual void set_rotation(const Vec3f& c, float ax, float ay, float az) = 0;
};

class Sphere : public Solid
{
public:

    Material material;
    Vec3f center;
    float radius;
    Rotation rot;

    Texture texture;
    bool is_texture = false;

    virtual Vec3f get_color(Vec3f point) const
    {
        if (is_texture)
        {

            double teta = asin((point.x - center.x) / radius) / (2.0 * M_PI);
            double gama = atan2((point.y - center.y), (point.z - center.z)) / M_PI;
            
            float U = 0.5 + teta; // *texture.width) % (int)texture.width;
            float V = 0.5 - gama; // (teta / M_PI)* texture.height;

            int i = (int) (U * texture.height) % texture.height;
            int j = (int) (V * texture.width) % texture.width;

            return texture.map[i * texture.height + j];
        }

        return material.diffuse_color;
    }

    Sphere(const Vec3f& c, const float r, const Material& m) : material(m), center(c), radius(r) {}
    Sphere(const Vec3f& c, const float r, const Material& m, const Texture& t) : material(m), center(c), radius(r), texture(t), is_texture(true) {}
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
        if (rotate)
        {
            Vec3f new_orig = to_cartesian(get_rotation().getMatrix() * to_homogeneous(orig, 1));
            Vec3f new_dir = to_cartesian(get_rotation().getMatrix() * to_homogeneous(dir, 0));

            float t0;
            if (ray_intersect(new_orig, new_dir, t0) && t0 < dist)
            {
                hit.point = new_orig + new_dir * t0;
                hit.color = get_color(hit.point);
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
                hit.color = get_color(hit.point);
                hit.N = this->findN(hit.point);

                hit.material = this->material;
                dist = t0;

                return true;

            }
        }

        return false;
    }

    Vec3f findN(Vec3f& hit) const 
    {
        return (hit - center).normalize();
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
};

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
};

//class Torus : public Solid
//{
//public:
//    Vec3f center;
//    float radius_swept;
//    float radius_tube;
//    Material material;
//
//    Torus(const Vec3f& c, const float r_s, const float r_t, const Material& m) : Solid(m), center(c), radius_swept(r_s), radius_tube(r_t) {};
//
//
//    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const
//    {
//        float ox = orig.x;
//        float oy = orig.y;
//        float oz = orig.z;
//
//        float dx = dir.x;
//        float dy = dir.y;
//        float dz = dir.z;
//
//        // define the coefficients of the quartic equation
//        float sum_d_sqrd = dx * dx + dy * dy + dz * dz;
//        float e = ox * ox + oy * oy + oz * oz -
//            this->radius_swept * this->radius_swept - this->radius_tube * this->radius_tube;
//        float f = ox * dx + oy * dy + oz * dz;
//        float four_a_sqrd = 4.0 * this->radius_swept * this->radius_swept;
//
//        float divider = sum_d_sqrd * sum_d_sqrd;
//
//        float A = float(4.0 * sum_d_sqrd * f) / divider;
//        float B = float(2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * dy * dy) / divider;
//        float C = (float)(4.0 * f * e + 2.0 * four_a_sqrd * oy * dy) / divider;
//        float D = float(e * e - four_a_sqrd * (this->radius_tube * this->radius_tube - oy * oy)) / divider;
//
//        Vec4f coeffs(A, B, C, D);
//        Vec4f x(0,0,0,0);
//
//        int res_n = SolveP4(coeffs, x);
//        if (!res_n)
//            return false;
//
//        t0 = x[0];
//        for (int i = 1; i < res_n; i++)
//            if (t0 < 0 || x[i] < t0)
//                t0 = x[i];
//        
//        if (t0 < 0)
//            return false;
//        
//        return true;
//       
//    }
////    Vec3f findN(Vec3f& hit) {
//
//        float paramSquared = this->radius_swept * this->radius_swept + this->radius_tube * this->radius_tube;
//
//        float x = hit[0];
//        float y = hit[1];
//        float z = hit[2];
//        float sumSquared = x * x + y * y + z * z;
//
//        return Vec3f(
//            4.0 * x * (sumSquared - paramSquared),
//            4.0 * y * (sumSquared - paramSquared + 2.0 * this->radius_swept * this->radius_swept),
//            4.0 * z * (sumSquared - paramSquared)).normalize();
//    }
////};
//
//class SemiSphere : public Sphere
//{
//public:
//
//    SemiSphere(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m) {};
//
//    bool inBorders(Vec3f& point) const
//    {
//        return (point.x <= center.x);
//    }
//};

// ��������
class Cornea : public Sphere
{
public:

    Cornea(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m) {};
    bool inBorders(Vec3f& point) const
    {
        return (point.x <= center.x - radius * cos(0.872665));
    }
};

// ������
class Sclera : public Sphere
{
public:

    Sclera(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m) {};
    Sclera(const Vec3f& c, const float r, const Material& m, const Texture& t) : Sphere(c, r, m, t) {};
    bool inBorders(Vec3f& point) const
    {
        return (point.x >= center.x - radius * cos(0.645772));
    }
};

// ������� + ������ 
class Iris : public Sphere
{
public:

    Iris(const Vec3f& c, const float r, const Material& m) : Sphere(c, r, m) {};
    Iris(const Vec3f& c, const float r, const Material& m, const Texture& t) : Sphere(c, r, m, t) {};
    bool inBorders(Vec3f& point) const
    {        
        return (point.x >= center.x - radius * cos(0.15)) && (point.x <= center.x - radius * cos(0.418879));
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

// ������������ ���� 
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

// ��������� crystalline 
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

    Eye(const Vec3f& c, float r) : center(c), radius(r), border(c, 1.25*r, Material())
    {
        Material  cryst_glass(1.0, Vec4f(0.0, 0.1, 0.2, 0.7), Vec3f(0.6, 0.7, 0.8), 125.);
        Material  cornea_glass(1.0, Vec4f(0.0, 0.1, 0.2, 0.7), Vec3f(0.6, 0.7, 0.8), 125.);
        Material  blue_iris(1.0, Vec4f(0.5, 0.5, 0.0, 0.0), Vec3f(0., 0.2, 0.8), 10.);
        Material white_glass(1.0, Vec4f(0.5, 0.8, 0.1, 0.1), Vec3f(0.5, 0.5, 0.5), 125.);
        Material  red_rubber(1.0, Vec4f(0.9, 0.1, 0.0, 0.0), Vec3f(0.09, 0.01, 0.01), 10.);

        Texture sclera_texture("1_1.bmp");
        Texture iris_texture("447_3.bmp");


        //components.push_back(new Sphere(c, 1.25*r, cornea_glass));
        components.push_back(new Cornea(c - Vec3f(0.37 * r, 0, 0), 0.9 * r, cornea_glass));
        components.push_back(new Sclera(c, r * 7 / 6, white_glass, sclera_texture));
        components.push_back(new Iris(c + Vec3f(0.8 * r, 0, 0), 1.85 * r, red_rubber, iris_texture));
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
                    // ��������� ����������� � ��������� �����������
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
                    // ��������� ����������� � ��������� �����������
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

Vec3f reflect(const Vec3f& I, const Vec3f& N);
Vec3f refract(const Vec3f& I, const Vec3f& N, const float eta_t, const float eta_i = 1.f);

bool scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<Solid*>& spheres, HitPoint& hit);
Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, const std::vector<Solid*>& spheres, const std::vector<Light>& lights, size_t depth = 0);
void render(System::Drawing::Bitmap^ bmp, const std::vector<Solid *>& spheres, const std::vector<Light>& lights);