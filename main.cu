#include "glm/vec3.hpp"
#include "palettes.cuh"
#include "camera.cu"
#include "hittable.cuh"
#include <stdio.h>
using namespace glm;

int main() {
    Sphere h_sphere(vec3(0,0,50), 2);
    Camera h_cam(vec3(0,0,0), 2);
    Palette h_palette(vec3(0.8, 0.5, 0.4), vec3(0.2, 0.4, 0.2), vec3(2.0, 1.0, 1.0), vec3(0.0, 0.25, 0.25), 0.01);
    outputImage(loadScene(h_cam, h_sphere, h_palette));
}