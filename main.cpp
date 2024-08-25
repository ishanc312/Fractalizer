#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <thread>
#include <mutex>

#include "glm/glm.hpp"
#include "camera.h"
#include "hittable.h"
using namespace glm;

int main() {
    std::vector<std::shared_ptr<Hittable>> scene = {
        std::make_shared<Cube>(vec3(0,1,3), 0.5),
        std::make_shared<Sphere>(vec3(0,-1,3), 0.5),
    };

    Camera cam(vec3(0, 0, 0), 1.0);
    cam.renderImage(scene);
    cam.outputImage();

    return 0;
}