#include "glm/vec3.hpp"
#include "pallettes.cpp"
#include "camera.cu"
#include "hittable.cuh"
#include <stdio.h>
using namespace glm;

int main() {
    Sphere h_sphere(vec3(0,0,5), 1);
    Camera h_cam(vec3(0,0,0), 2);
    outputImage(loadScene(h_cam, h_sphere));
}