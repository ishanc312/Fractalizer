#include "glm/glm.hpp"
#include "palettes.h"
#include "camera.h"
#include "hittable.h"
using namespace glm;

// Need to containerize this application so it can run anywhere..

int main() {
    std::vector<std::shared_ptr<Hittable>> scene = {
        std::make_shared<fractSphere>(vec3(0.5,0.5,0.5), 0.25),
        std::make_shared<Sphere>(vec3(0,0,2), 1)
    };
    Palette testPalette(vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 0.7f, 0.4f), vec3(0.0f, 0.15f, 0.20f));
    Camera cam(vec3(0, 0, -4), 1.0, testPalette, 0.03, false);
    cam.renderImage(scene);
    cam.outputImage();
    return 0;
}