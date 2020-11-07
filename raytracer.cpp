#include "raytracer.h"

Vec3f reflect(const Vec3f& I, const Vec3f& N) {
    return I - N * 2.f * (I * N);
}

Vec3f refract(const Vec3f& I, const Vec3f& N, const float eta_t, const float eta_i) { // Snell's law
    float cosi = -std::max(-1.f, std::min(1.f, I * N));
    if (cosi < 0) return refract(I, -N, eta_i, eta_t); // if the ray comes from the inside the object, swap the air and the media
    float eta = eta_i / eta_t;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? Vec3f(1, 0, 0) : I * eta + N * (eta * cosi - sqrtf(k)); // k<0 = total reflection, no ray to refract. I refract it anyways, this has no physical meaning
}

bool scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<Solid*>& spheres, Vec3f& hit, Vec3f& N, Material& material) {
    float spheres_dist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < spheres.size(); i++) 
    {       
        spheres[i]->ray_intersect(orig, dir, hit, N, material, spheres_dist, true);
    }

    float checkerboard_dist = std::numeric_limits<float>::max();
    if (fabs(dir.y) > 1e-3) {
        float d = -(orig.y + 4) / dir.y; // the checkerboard plane has equation y = -4
        Vec3f pt = orig + dir * d;
        if (d > 0 && fabs(pt.x) < 10 && pt.z<-10 && pt.z>-30 && d < spheres_dist) {
            checkerboard_dist = d;
            hit = pt;
            N = Vec3f(0, 1, 0);
            material.diffuse_color = (int(.5 * hit.x + 1000) + int(.5 * hit.z)) & 1 ? Vec3f(.3, .3, .3) : Vec3f(.3, .2, .1);
        }
    }
    return std::min(spheres_dist, checkerboard_dist) < 1000;
}

Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, const std::vector<Solid*>& spheres, const std::vector<Light>& lights, size_t depth) {
    Vec3f point, N;
    Material material;
    int indx;

    if (depth > 4 || !scene_intersect(orig, dir, spheres, point, N, material)) {
        return Vec3f(0.2, 0.7, 0.8); // background color
    }

    Vec3f reflect_dir = reflect(dir, N).normalize();
    Vec3f refract_dir = refract(dir, N, material.refractive_index).normalize();
    Vec3f reflect_orig = reflect_dir * N < 0 ? point - N * 1e-3 : point + N * 1e-3; // offset the original point to avoid occlusion by the object itself
    Vec3f refract_orig = refract_dir * N < 0 ? point - N * 1e-3 : point + N * 1e-3;
    Vec3f reflect_color = cast_ray(reflect_orig, reflect_dir, spheres, lights, depth + 1);
    Vec3f refract_color = cast_ray(refract_orig, refract_dir, spheres, lights, depth + 1);

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++) {
        
        Vec3f light_dir = (lights[i].position - point).normalize();
        float light_distance = (lights[i].position - point).norm();

        Vec3f shadow_orig = light_dir * N < 0 ? point - N * 1e-3 : point + N * 1e-3; // checking if the point lies in the shadow of the lights[i]
        Vec3f shadow_pt, shadow_N;
        Material tmpmaterial;

        // луч из теневой точки пересекает на своем пути какое то тело 
        bool is_intersect = scene_intersect(shadow_orig, light_dir, spheres, shadow_pt, shadow_N, tmpmaterial) && (shadow_pt - shadow_orig).norm() < light_distance;
        if (is_intersect && tmpmaterial.albedo[3] < 0.5)
            continue;
        
        float intensity = lights[i].intensity;
        if (is_intersect)
            intensity *= tmpmaterial.albedo[3];

        diffuse_light_intensity += intensity * std::max(0.f, light_dir * N);
        specular_light_intensity += powf(std::max(0.f, -reflect(-light_dir, N) * dir), material.specular_exponent) * lights[i].intensity;
    }

    return material.diffuse_color * diffuse_light_intensity * material.albedo[0] + 
        Vec3f(1., 1., 1.) * specular_light_intensity * material.albedo[1] + 
        reflect_color * material.albedo[2] + 
        refract_color * material.albedo[3];
}

void render(System::Drawing::Bitmap^ bmp, const std::vector<Solid*>& spheres, const std::vector<Light>& lights) {
    const int   width = bmp->Width;
    const int   height = bmp->Height;
    const float fov = M_PI / 3.;
    const float halfpi = M_PI / 2;

    std::vector<Vec3f> framebuffer(width * height);
    Vec3f camera_position(0, 0, 0);

#pragma omp parallel for
    for (size_t j = 0; j < height; j++) { // actual rendering loop
        for (size_t i = 0; i < width; i++) {
            float dir_x = (i + 0.5) - width / 2.;
            float dir_y = -(j + 0.5) + height / 2.;    // this flips the image at the same time
            float dir_z = -height / (2. * tan(fov / 2.));

            Vec3f dir = Vec3f(dir_x, dir_y, dir_z).normalize();
            framebuffer[i + j * width] = cast_ray(camera_position, dir, spheres, lights);
            
            Vec3f& c = framebuffer[i + j * width];
            float max = std::max(c[0], std::max(c[1], c[2]));
            if (max > 1) c = c * (1. / max);
            bmp->SetPixel(i, j, System::Drawing::Color::FromArgb(
                255,
                (255 * std::max(0.f, std::min(1.f, framebuffer[i + j * width][0]))),
                (255 * std::max(0.f, std::min(1.f, framebuffer[i + j * width][1]))),
                (255 * std::max(0.f, std::min(1.f, framebuffer[i + j * width][2])))
            ));
        }
    }
}
