#include "raytracer.h"
#include <ctime>

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

bool scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<std::shared_ptr<Solid>>& solids, HitPoint& hit) {
    float spheres_dist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < solids.size(); i++) 
    {       
        solids[i]->ray_intersect(orig, dir, hit, spheres_dist, true);
    }

    float board_dist = std::numeric_limits<float>::max();
    if (fabs(dir.y) > 1e-3) {
        float d = -(orig.y + 4) / dir.y; 
        Vec3f pt = orig + dir * d;
        if (d > 0 && fabs(pt.x) < 10 && pt.z<-10 && pt.z>-30 && d < spheres_dist) {
            board_dist = d;
            hit.point = pt;
            hit.N = Vec3f(0, 1, 0);
            hit.material.diffuse_color = Vec3f(.3, .3, .3);
            hit.color = Vec3f(.3, .3, .3);
        }
    }
    return std::min(spheres_dist, board_dist) < 1000;
}

void convert_xyz_to_cube_uv(float x, float y, float z, float* u, float* v)
{
    float absX = fabs(x);
    float absY = fabs(y);
    float absZ = fabs(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    float maxAxis, uc, vc;

    // POSITIVE X
    if (isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from +z to -z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = -z;
        vc = y;
    }
    // NEGATIVE X
    if (!isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from -z to +z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = z;
        vc = y;
    }
    // POSITIVE Y
    if (isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from +z to -z
        maxAxis = absY;
        uc = x;
        vc = -z;
    }
    // NEGATIVE Y
    if (!isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -z to +z
        maxAxis = absY;
        uc = x;
        vc = z;
    }
    // POSITIVE Z
    if (isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = x;
        vc = y;
    }
    // NEGATIVE Z
    if (!isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from +x to -x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = -x;
        vc = y;
    }

    // Convert range from -1 to 1 to 0 to 1
    *u = 0.5f * (uc / maxAxis + 1.0f);
    *v = 0.5f * (vc / maxAxis + 1.0f);
}

Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, const std::vector<std::shared_ptr<Solid>>& solids, const std::vector<Light>& lights, size_t depth) {
    
    HitPoint hit;

    if (depth > 4 || !scene_intersect(orig, dir, solids, hit)) {
        
        // цвет фона
        static Texture back("surgery.bmp");
        
        double teta = asin(dir.x) / (M_PI);
        double gama = atan2(dir.z, dir.y) / (2.0 * M_PI);

        float U = 0.5 + teta; // *texture.width) % (int)texture.width;
        float V = 0.5 - gama; // (teta / M_PI)* texture.height;

        int i = (int)(U * back.height) % back.height;
        int j = (int)(V * back.width) % back.width;
        
     
        return back.map[i * back.height + j];
    }

    Vec3f reflect_dir = reflect(dir, hit.N).normalize();
    Vec3f refract_dir = refract(dir, hit.N, hit.material.refractive_index).normalize();
    Vec3f reflect_orig = reflect_dir * hit.N < 0 ? hit.point - hit.N * 1e-3 : hit.point + hit.N * 1e-3; 
    Vec3f refract_orig = refract_dir * hit.N < 0 ? hit.point - hit.N * 1e-3 : hit.point + hit.N * 1e-3;
    Vec3f reflect_color = cast_ray(reflect_orig, reflect_dir, solids, lights, depth + 1);
    Vec3f refract_color = cast_ray(refract_orig, refract_dir, solids, lights, depth + 1);

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); i++) {
        
        Vec3f light_dir = (lights[i].position - hit.point).normalize();
        float light_distance = (lights[i].position - hit.point).norm();

        Vec3f shadow_orig = light_dir * hit.N < 0 ? hit.point - hit.N * 1e-3 : hit.point + hit.N * 1e-3; 
        
        HitPoint shadow_hit;

        // луч из теневой точки пересекает на своем пути какое то тело и оно непрозрачное
        bool is_intersect = scene_intersect(shadow_orig, light_dir, solids, shadow_hit) && (shadow_hit.point - shadow_orig).norm() < light_distance;
        if (is_intersect && shadow_hit.material.albedo[3] < 0.5)
            continue;
        
        float intensity = lights[i].intensity;
        if (is_intersect)
            intensity *= shadow_hit.material.albedo[3];

        diffuse_light_intensity += intensity * std::max(0.f, light_dir * hit.N);
        specular_light_intensity += powf(std::max(0.f, -reflect(-light_dir, hit.N) * dir), hit.material.specular_exponent) * lights[i].intensity;
    }

    return hit.color * diffuse_light_intensity * hit.material.albedo[0] + 
        Vec3f(1., 1., 1.) * specular_light_intensity * hit.material.albedo[1] +
        reflect_color * hit.material.albedo[2] + 
        refract_color * hit.material.albedo[3];
}

void render(System::Drawing::Bitmap^ bmp, Scene& scene)
{
    const int   width = bmp->Width;
    const int   height = bmp->Height;
    const float fov = M_PI / 3.;
    const float halfpi = M_PI / 2;

    std::vector<Vec3f> framebuffer(width * height);

    Rotation rot(scene.get_camera().get_location(), scene.get_camera().get_sight());

    clock_t start = std::clock();

//#pragma omp parallel for shared(bmp, framebuffer)
    for (int j = 0; j < height; j++) { 
        for (int i = 0; i < width; i++) {

            // это вектор взгляда в системе координат камеры ( в этой системе взгляд в центр холста == 0,0,-1)
            float dir_x =  0 + (i + 0.5) - width / 2.;
            float dir_y =  0 - (j + 0.5) + height / 2.;    
            float dir_z = -1 * (height / (2. * tan(fov / 2.)));
            Vec3f dir = Vec3f(dir_x, dir_y, dir_z).normalize();

            // поворачиваем вектор, чтобы получить взгляд камеры
            Vec3f new_dir = to_cartesian(rot.getMatrix() * to_homogeneous(dir, 0));
            framebuffer[i + j * width] = cast_ray(scene.get_camera().get_location(), new_dir, scene.get_solids(), scene.get_lights());

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

    clock_t end = std::clock();

    FILE* f;
    f = fopen("log.txt", "w");
    fprintf(f, "linear time: %ld\n", end - start);
    fclose(f);
}