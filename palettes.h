// A C++ File to include all color pallettes we create
// Provide the user with pre-defined pallettes to play around with 

#ifndef PALETTE_H
#define PALETTE_H

#include "glm/glm.hpp"
#include <iostream>
using namespace glm;

struct Palette {
public:
    Palette(vec3 a_, vec3 b_, vec3 c_, vec3 d_, float dampen): a(a_), b(b_), c(c_), d(d_), dampener(dampen) {}
    vec3 generateColor(float t) {
        return a+b*cos(6.14f*(c*t + d));
    }
    vec3 generateRGB(float dist) {
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