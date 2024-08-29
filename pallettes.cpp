// A C++ File to include all color pallettes we create
// Provide the user with pre-defined pallettes to play around with 

#include "glm/glm.hpp"
#include <iostream>
using namespace glm;

const float PI = 3.14;

vec3 a(0.5f, 0.5f, 0.5f);
vec3 b(0.5f, 0.5f, 0.5f);
vec3 c(1.0f, 0.7f, 0.4f);
vec3 d(0.0f, 0.15f, 0.20f);

vec3 pallette(float t) {
    return a+b*cos(2*PI*(c*t + d));
}

vec3 testPallette(float dist, float dampener) {
    vec3 color = pallette(dist*dampener);
    return vec3((int)255.999*color.x, (int)255.999*color.y, (int)255.999*color.z);
}