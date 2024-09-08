#include "glm/glm.hpp"
#include "palettes.h"
#include "camera.h"
#include "hittable.h"
using namespace glm;

// Need to containerize this application so it can run anywhere..

int main() {
    std::vector<std::shared_ptr<Hittable>> scene = {
        std::make_shared<Sphere>(vec3(0,0,50), 2)
    };
    Palette testPalette(vec3(0.8f, 0.5f, 0.4f), vec3(0.2f, 0.4f, 0.2f), vec3(2.0f, 1.0f, 1.0f), vec3(0.0f, 0.25f, 0.25f), 0.01);
    Camera cam(vec3(0, 0, 0), 2.0, testPalette, false);
    cam.renderImage(scene);
    cam.outputImage();
    return 0;
}