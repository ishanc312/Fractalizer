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
        std::make_shared<Sphere>(vec3(-1,0,4), 0.5),
        std::make_shared<Cube>(vec3(0,0,3), 0.2)
    };

    Camera cam(vec3(0, 0, 0), 1.0);
    cam.render_image(scene);
    cam.output_image();

    return 0;
}