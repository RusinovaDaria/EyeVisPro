#pragma once

class PerlinNoise {
private:
    int p[512];

    double fade(double) const;
    double lerp(double, double, double) const;
    double grad(int, double, double, double) const;

public:
    PerlinNoise();
    double noise(double, double, double) const;
};