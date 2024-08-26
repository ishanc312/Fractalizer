#include "glm/glm.hpp"
#include "camera.h"
#include "hittable.h"
using namespace glm;

int main() {
    std::vector<std::shared_ptr<Hittable>> scene = {
        std::make_shared<Cube>(vec3(-1,1,4), 1),
    };

    Camera cam(vec3(0, 0, 0), 1.0);
    cam.turnCamera(-20.0f, 20.0f);
    cam.renderImage(scene);
    cam.outputImage();

    return 0;
}