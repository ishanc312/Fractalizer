#include "glm/glm.hpp"
#include "camera.h"
#include "hittable.h"
using namespace glm;

int main() {
    std::vector<std::shared_ptr<Hittable>> scene = {
        std::make_shared<Sphere>(vec3(0,0,4), 1)
    };

    Camera cam(vec3(0, 0, -2), 1.0, true);
    // cam.turnCamera(-20.0f, 20.0f);
    cam.renderImage(scene);
    cam.outputImage();

    return 0;
}