#pragma once
#include "solid.h"

class Plane : public Solid
{
	int y_dist = 5;
	int x_dist = 5;
	int z_dist = 5;
    int side = 10;

	Material material;

public:
	Plane() = default;
	Plane(int y, int x, int z, int s) : y_dist(y), x_dist(x), z_dist(z), side(s) {};
	Plane(int y, int x, int z, int s, const Material& m) : y_dist(y), x_dist(x), z_dist(z), 
        side(s), material(m) {};

    // поиск параметра точки пересечения если она есть
    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const 
    {
        return false;
    }

    // поиск точки пересечения если она есть  
    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, HitPoint& hitp, float& dist, bool rotate = false) const
    {
        float d = -(orig.y + y_dist) / dir.y;
        Vec3f pt = orig + dir * d;
        if (d > 0 && pt.x < (x_dist + side) && pt.x > (x_dist - side) && pt.z < (z_dist + side) && pt.z > (z_dist - side) && d < dist)
        {
            dist = d;
            hitp.point = pt;
            hitp.N = findN(hitp.point);
            hitp.material = get_material();
            hitp.color = hitp.material.color;

            return true;
        }

        return false;
    
    }

    void set_distance(const Vec3f& dist) { x_dist = dist.x; y_dist = dist.y, z_dist = dist.z; }
    void set_side(int s) { side = s; }


    Vec3f findN(Vec3f& hit) const { return Vec3f(0, 1, 0); };
    Vec3f modifyN(HitPoint& hit) const { return findN(hit.point);  };

    bool inBorders(Vec3f& point) const { return true; }

    Vec3f get_center()  const { return Vec3f(y_dist, x_dist, y_dist);  };
    Material get_material() const { return material; };
    Rotation get_rotation() const { return Rotation(Vec3f(0, 0, 0), Vec3f(0, 0, 0));  };

    void set_rotation(const Vec3f& c, float ax, float ay, float az) {};
    void set_texture(const Texture& txt) {};
    void set_material(const Material& mtr) { material = mtr; };
    void set_normal_map(const NormalMap& nm) {};
};



//if (show_table)
//{
//    float board_dist = std::numeric_limits<float>::max();
//    if (fabs(dir.y) > 1e-3) {
//        float d = -(orig.y + 4) / dir.y;
//        Vec3f pt = orig + dir * d;
//        if (d > 0 && fabs(pt.x) < 10 && pt.z<-10 && pt.z>-30 && d < solids_dist) {
//            board_dist = d;
//            hit.point = pt;
//            hit.N = Vec3f(0, 1, 0);
//            hit.material.color = Vec3f(.3, .3, .3);
//            hit.color = Vec3f(.3, .3, .3);
//        }
//    }
//}