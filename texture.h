#pragma once

#include "geometry.h"

// color map 
class Texture
{
public:

    // �������
    int height;
    int width;

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
