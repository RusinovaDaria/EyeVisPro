#include "cubemap.h"

Cubemap::Cubemap() {}

Cubemap::Cubemap(std::vector<const char*> faces)
{
    if (faces.size() != 6) return;
    for (int i = 0; i < faces.size(); i++) 
    {
        System::String^ path_i = gcnew System::String(faces[i]);

        System::Drawing::Bitmap bmp(path_i);
        int height = bmp.Height;
        int width = bmp.Width;

        // posx, posy, poz, negx, negy, negz 
        map.push_back(std::shared_ptr<Vec3f[]>(new Vec3f[width * height]));
        sizes.push_back(Vec2i(width, height));
        for (int k = 0; k < width; k++)
        {
            for (int l = 0; l < height; l++)
            {
                System::Drawing::Color c = bmp.GetPixel(k, l);
                map[i][k * height + l] = Vec3f(c.R / 255., c.G / 255., c.B / 255.);
            }
        }
    }
}

int Cubemap::set_faces(std::vector<const char*> faces)
{
    if (faces.size() != 6) return -1;

    map.clear();
    sizes.clear();

    for (int i = 0; i < 6; i++)
    {
        System::String^ path_i = gcnew System::String(faces[i]);

        System::Drawing::Bitmap bmp(path_i);
        int height = bmp.Height;
        int width = bmp.Width;

        // posx, posy, poz, negx, negy, negz 
        map.push_back(std::shared_ptr<Vec3f[]>(new Vec3f[width * height]));
        sizes.push_back(Vec2i(width, height));
        for (int k = 0; k < width; k++)
        {
            for (int l = 0; l < height; l++)
            {
                System::Drawing::Color c = bmp.GetPixel(k, l);
                map[i][k * height + l] = Vec3f(c.R / 255., c.G / 255., c.B / 255.);
            }
        }
    }

    return 0;
}

int Cubemap::set_faces(std::vector<std::string> faces)
{
    if (faces.size() != 6) return -1;
    std::vector<const char*> char_faces(6);

    for (int i = 0; i < 6; i++)
        char_faces[i] = faces[i].c_str();

    set_faces(char_faces);

    return 0;
}

Vec3f Cubemap::getBackgroundColor(const Vec3f& direction) 
{
    float u, v;
    int faceIndex;

    vectorToUV(direction[0], -direction[1], direction[2], &faceIndex, &u, &v);

    int s_fi_1 = sizes[faceIndex][1];
    int s_fi_0 = sizes[faceIndex][0];

    size_t i = size_t(u * s_fi_1) % s_fi_1;
    size_t j = size_t(v * s_fi_0) % s_fi_0;

    return map[faceIndex][i * s_fi_1 + j];
}

void Cubemap::vectorToUV(float x, float y, float z,
    int* index, float* u, float* v) {
    
    // как убрать модули
    float absX = fabs(x);
    float absY = fabs(y);
    float absZ = fabs(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    float maxAxis, uc, vc;

    // POSITIVE X
    if (isXPositive && absX >= absY && absX >= absZ) {

        maxAxis = absX;
        uc = -z;
        vc = y;
        *index = 0;
    }
    // NEGATIVE X
    if (!isXPositive && absX >= absY && absX >= absZ) {

        maxAxis = absX;
        uc = z;
        vc = y;
        *index = 3;
    }
    // POSITIVE Y
    if (isYPositive && absY >= absX && absY >= absZ) {

        maxAxis = absY;
        uc = x;
        vc = -z;
        *index = 1;
    }
    // NEGATIVE Y
    if (!isYPositive && absY >= absX && absY >= absZ) {

        maxAxis = absY;
        uc = x;
        vc = z;
        *index = 4;
    }
    // POSITIVE Z
    if (isZPositive && absZ >= absX && absZ >= absY) {

        maxAxis = absZ;
        uc = x;
        vc = y;
        *index = 2;
    }
    // NEGATIVE Z
    if (!isZPositive && absZ >= absX && absZ >= absY) {

        maxAxis = absZ;
        uc = -x;
        vc = y;
        *index = 5;
    }

    *u = 0.5f * (uc / maxAxis + 1.0f);
    *v = 0.5f * (vc / maxAxis + 1.0f);
}