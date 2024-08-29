#include "glm/glm.hpp"
#include "pallettes.cpp"
#include "camera.h"
#include "hittable.h"
using namespace glm;

int main() {
    std::vector<std::shared_ptr<Hittable>> scene = {
        std::make_shared<fractSphere>(vec3(0.5,0.5,0.5), 0.25),
        std::make_shared<Sphere>(vec3(0,0,2), 1)
    };

    Camera cam(vec3(0, 0, -4), 1.0, &testPallette, 0.03, false);
    cam.renderImage(scene);
    cam.outputImage();
    return 0;
}