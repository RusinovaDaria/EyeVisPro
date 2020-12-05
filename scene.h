#pragma once

#include "geometry.h"
#include "poly.h"
#include "transform.h"
#include "normalmap.h"
#include "texture.h"
#include "material.h"
#include "solid.h"
#include "camera.h"
#include "light.h"
#include "cubemap.h"

// сцена = наблюдатель, тела, источники света
class Scene
{
    int max_depth = 2;

    // камера
    int active_camera;

    // тела сцены: вектор указателей
    std::vector<std::shared_ptr<Solid>> solids;

    // источники света
    std::vector<Light> lights;

    // камеры
    std::vector<Camera> cameras;

    // фон
    Vec3f back_color;
    Cubemap back_map;
    bool is_cubemap = false;

public:

    Scene() = default;

    Scene(const Camera& cam) : active_camera(0), cameras({cam}) {};
    Scene(const Camera& cam, const std::vector<Light>& lgh) : active_camera(0), lights(lgh), cameras({ cam }) {};
    Scene(const Camera& cam, const std::vector<Light>& lgh, const std::vector<std::shared_ptr<Solid>>& sld) : active_camera(0), 
        lights(lgh), solids(sld), cameras({ cam }) {};

    void add_solid(std::shared_ptr<Solid> s) { solids.push_back(s); }
    void add_light(const Light& l) { lights.push_back(l);  }
    void add_camera(const Camera& c) { cameras.push_back(c);  }
    void set_active_camera(int indx) { active_camera = indx; }
    
    void set_back_map(const Cubemap& cm) 
    {
        is_cubemap = true;
        back_map = cm;
    };

    void set_back_color(const Vec3f& c) 
    {
        is_cubemap = false;
        back_color = c;
    };

    Camera& get_camera() { return cameras[active_camera]; };
    int get_camera_indx() { return active_camera; };
    std::vector<std::shared_ptr<Solid>>& get_solids() { return solids; };
    std::vector<Light>& get_lights() { return lights; };
    std::vector<Camera>& get_cameras() { return cameras; };

    Vec3f getBackgroundColor(const Vec3f& direction)
    {
        if (is_cubemap)
            return back_map.getBackgroundColor(direction);
        
        return back_color;
    }

    int get_max_depth() { return max_depth; }
    void set_max_depth(int d) { max_depth = d; }
};
