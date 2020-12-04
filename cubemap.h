#pragma once

#include <vector>
#include "geometry.h"

class Cubemap {
private:

    int width;
    int height; 

    // матрицы цветов
    std::vector<std::shared_ptr<Vec3f[]>> map;
    std::vector<Vec2i> sizes;

    void vectorToUV(float x, float y, float z, int* index, float* u, float* v);

public:
    Cubemap();
    Cubemap(std::vector<const char*> faces);
    int set_faces(std::vector<const char*> faces);
    int set_faces(std::vector<std::string> faces);

    Vec3f getBackgroundColor(const Vec3f& direction);
};