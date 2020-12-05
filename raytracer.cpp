
#include "raytracer.h"
#include "cubemap.h"
#include <ctime>
#include <omp.h>
#include "utils.h"

#define SPECULAR_EXPONENT 250;

Vec3f reflect(const Vec3f& I, const Vec3f& N) 
{
    return I - N * 2.f * (I * N);
}

Vec3f refract(const Vec3f& I, const Vec3f& N, const float eta_t, const float eta_i) 
{
    float cosi = -std::max(-1.f, std::min(1.f, I * N));

    if (cosi < 0) return refract(I, -N, eta_i, eta_t); 
    float eta = eta_i / eta_t;
    float k = 1 - eta * eta * (1 - cosi * cosi);

    return k < 0 ? Vec3f(1, 0, 0) : I * eta + N * (eta * cosi - sqrtf(k)); 
}

bool scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<std::shared_ptr<Solid>>& solids, HitPoint& hit) {
    
    float solids_dist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < solids.size(); i++)
    {
        solids[i]->ray_intersect(orig, dir, hit, solids_dist, true);
    }

    return solids_dist < 1000;
}

Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, Scene& scene, size_t depth) {
    
    HitPoint hit;
    std::vector<std::shared_ptr<Solid>> solids = scene.get_solids();
    std::vector<Light> lights = scene.get_lights();

    bool is_scene_intersect = scene_intersect(orig, dir, solids, hit);

    // наткнулись на внутреннюю сторону непрозрачного тела 
    if (is_scene_intersect && dot(dir, hit.N) > 0 && hit.material.coeffs[3] <= 0.5)
    {
            return Vec3f(0, 0, 0);
    }
    
    if (depth > scene.get_max_depth() || !is_scene_intersect)
    {   
        // цвет фона
        return scene.getBackgroundColor(dir);
    }

    Vec3f reflect_dir = reflect(dir, hit.N).normalize();
    Vec3f refract_dir = refract(dir, hit.N, hit.material.refractive_index).normalize();
    Vec3f reflect_orig = reflect_dir * hit.N < 0 ? hit.point - hit.N * 1e-3 : hit.point + hit.N * 1e-3; 
    Vec3f refract_orig = refract_dir * hit.N < 0 ? hit.point - hit.N * 1e-3 : hit.point + hit.N * 1e-3;
    Vec3f reflect_color = cast_ray(reflect_orig, reflect_dir, scene, depth + 1);
    Vec3f refract_color = cast_ray(refract_orig, refract_dir, scene, depth + 1);

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++) {
        
        Vec3f light_dir = (lights[i].position - hit.point).normalize();
        float light_distance = (lights[i].position - hit.point).norm();

        Vec3f shadow_orig = light_dir * hit.N < 0 ? hit.point - hit.N * 1e-3 : hit.point + hit.N * 1e-3; 
        
        HitPoint shadow_hit;

        // луч из теневой точки пересекает на своем пути какое то тело и оно непрозрачное
        bool is_intersect = scene_intersect(shadow_orig, light_dir, solids, shadow_hit) && (shadow_hit.point - shadow_orig).norm() < light_distance;
        if (is_intersect && shadow_hit.material.coeffs[3] < 0.5)
            continue;
        
        float intensity = lights[i].intensity;
        if (is_intersect)
            intensity *= shadow_hit.material.coeffs[3];

        diffuse_light_intensity += intensity * std::max(0.f, light_dir * hit.N);
        specular_light_intensity += powf(std::max(0.f, -reflect(-light_dir, hit.N) * dir), 250) * lights[i].intensity;
    }

    return hit.color * diffuse_light_intensity * hit.material.coeffs[0] +         // диффузное отражение света
        Vec3f(1., 1., 1.) * specular_light_intensity * hit.material.coeffs[1] +   // зеркальное отражение  света
        reflect_color * hit.material.coeffs[2] +    // зеркальность (отражает другие предметы в себе)
        refract_color * hit.material.coeffs[3];     // прозрачность
}

void render(System::Drawing::Bitmap^ bmp, Scene& scene)
{
    clock_t start = std::clock();

    const int   width = bmp->Width;
    const int   height = bmp->Height;

    const float    half_width = width / 2;
    const float    half_height = height / 2;

    const float tan_fov_2 = 2. * tan(M_PI / 6.);
    const float dir_z = -1 * (height / tan_fov_2);

    const float halfpi = M_PI / 2;

    std::vector<Vec3f> framebuffer(width * height);
    Rotation rot(scene.get_camera().get_location(), scene.get_camera().get_sight());

    omp_lock_t l;
    omp_init_lock(&l);

#pragma omp parallel for
    for (int j = 0; j < height; j++) { 
#pragma omp parallel for
        for (int i = 0; i < width; i++) {

            int indx = i + j * width;

            // это вектор взгляда в системе координат камеры ( в этой системе взгляд в центр холста == 0,0,-1)
            float dir_x = (i + 0.5) - half_width;
            float dir_y = -(j + 0.5) + half_height;
            Vec3f dir = Vec3f(dir_x, dir_y, dir_z).normalize();
            
            // поворачиваем вектор, чтобы получить взгляд камеры
            Vec3f new_dir = to_cartesian(rot.getMatrix() * to_homogeneous(dir, 0));
            framebuffer[indx] = cast_ray(scene.get_camera().get_location(), new_dir, scene);
            
            Vec3f& c = framebuffer[indx];
            float max = std::max(c[0], std::max(c[1], c[2]));
            if (max > 1) c = c * (1. / max);

            omp_set_lock(&l);

            bmp->SetPixel(i, j, System::Drawing::Color::FromArgb(
                255,
                (255 * std::max(0.f, std::min(1.f, framebuffer[indx][0]))),
                (255 * std::max(0.f, std::min(1.f, framebuffer[indx][1]))),
                (255 * std::max(0.f, std::min(1.f, framebuffer[indx][2])))
            ));

            omp_unset_lock(&l);
        }
    }

    clock_t end = std::clock();
    omp_destroy_lock(&l);
}


void render(System::Drawing::Bitmap^ bmp, Scene& scene, const Camera& cam)
{
    const int   width = bmp->Width;
    const int   height = bmp->Height;

    const float    half_width = width / 2;
    const float    half_height = height / 2;

    const float tan_fov_2 = 2. * tan(M_PI / 6.);
    const float dir_z = -1 * (height / tan_fov_2);

    const float halfpi = M_PI / 2;

    std::vector<Vec3f> framebuffer(width * height);
    Rotation rot(cam.get_location(), cam.get_sight());

    omp_lock_t l;
    omp_init_lock(&l);

#pragma omp parallel for
    for (int j = 0; j < height; j++) {
#pragma omp parallel for
        for (int i = 0; i < width; i++) {

            int indx = i + j * width;

            // это вектор взгляда в системе координат камеры ( в этой системе взгляд в центр холста == 0,0,-1)
            float dir_x = (i + 0.5) - half_width;
            float dir_y = -(j + 0.5) + half_height;
            Vec3f dir = Vec3f(dir_x, dir_y, dir_z).normalize();

            // поворачиваем вектор, чтобы получить взгляд камеры
            Vec3f new_dir = to_cartesian(rot.getMatrix() * to_homogeneous(dir, 0));
            framebuffer[indx] = cast_ray(cam.get_location(), new_dir, scene);

            Vec3f& c = framebuffer[indx];
            float max = std::max(c[0], std::max(c[1], c[2]));
            if (max > 1) c = c * (1. / max);

            omp_set_lock(&l);

            bmp->SetPixel(i, j, System::Drawing::Color::FromArgb(
                255,
                (255 * std::max(0.f, std::min(1.f, framebuffer[indx][0]))),
                (255 * std::max(0.f, std::min(1.f, framebuffer[indx][1]))),
                (255 * std::max(0.f, std::min(1.f, framebuffer[indx][2])))
            ));

            omp_unset_lock(&l);
        }
    }
    omp_destroy_lock(&l);
}