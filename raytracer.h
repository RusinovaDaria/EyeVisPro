#pragma once

#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "scene.h"
#include "geometry.h"

Vec3f reflect(const Vec3f& I, const Vec3f& N);
Vec3f refract(const Vec3f& I, const Vec3f& N, const float eta_t, const float eta_i = 1.f);

bool scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<std::shared_ptr<Solid>>& solids, HitPoint& hit);
Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, Scene& scene, size_t depth = 0);
void render(System::Drawing::Bitmap^ bmp, Scene& scene);
void render(System::Drawing::Bitmap^ bmp, Scene& scene, const Camera& cam);