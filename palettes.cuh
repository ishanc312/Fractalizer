#ifndef PALETTE_H
#define PALETTE_H

#include "glm/glm.hpp"
#include <iostream>
using namespace glm;

struct Palette {
public:
    __host__ Palette() {}
    __host__ Palette(vec3 a_, vec3 b_, vec3 c_, vec3 d_, float dampen): a(a_), b(b_), c(c_), d(d_), dampener(dampen) {}
    __device__ vec3 generateColor(float t) {
        return a+b*cos(6.14f*(c*t + d));
    }
    __device__ vec3 generateRGB(float dist) {
        vec3 color = generateColor(dist*dampener);
        return vec3((int)255.999*color.x, (int)255.999*color.y, (int)255.999*color.z);
    }
private:
    vec3 a;
    vec3 b;
    vec3 c;
    vec3 d;
    float dampener;
};

#endif