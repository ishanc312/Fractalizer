#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <thread>
#include <mutex>

#include "glm/glm.hpp"
#include "hittable.h"
using namespace glm;

const vec3 camera(0, 0, 0);
const float focal_length = 1.0;

const float LOWER_BOUND = 0.001;
const float UPPER_BOUND = 1000;

float ASPECT_RATIO = 16.0/9.0;
const int IMG_WIDTH = 1280;
const int IMG_HEIGHT = IMG_WIDTH/ASPECT_RATIO;

const float V_WIDTH = 2.0;
const float V_HEIGHT = V_WIDTH/((float)IMG_WIDTH/IMG_HEIGHT);
const vec3 viewport_u(V_WIDTH/IMG_WIDTH, 0, 0);
const vec3 viewport_v(0, -V_HEIGHT/IMG_HEIGHT, 0);
const vec3 viewport_left_corner(-V_WIDTH/2.0, V_HEIGHT/2.0, focal_length);
const vec3 pixels_top_left = viewport_left_corner + viewport_u*0.5f + viewport_v*0.5f;

std::vector<std::shared_ptr<hittable>> scene = {
    std::make_shared<sphere>(vec3(0,0,3), 0.5),
    std::make_shared<sphere>(vec3(-1,0,2), 0.1)
};

vec3 ray_march(const vec3& pos, const vec3& pixel, const vec3& direction) {
    float dist = minSDF(scene, pos);
    if (dist < LOWER_BOUND) {
        return vec3(1, 0, 0);
    } else if (dist > UPPER_BOUND) {
        return vec3(0, 0, 0);
    }
    return ray_march(pos + direction*dist, pixel, direction);
}

vec3 write_color(int i, int j) {
    vec3 pixel = pixels_top_left + viewport_u*(float)j + viewport_v*(float)i;
    vec3 direction = (pixel-camera)/distance(pixel, camera);
    vec3 color = ray_march(camera, pixel, direction);
    return vec3((int)255.999*color.x, (int)255.999*color.y, (int)255.999*color.z);
}

void render_image(vec3** pixels) {
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            pixels[i][j] = write_color(i,j);
        }
    }
    std::clog << "Rendering complete." << '\n';
}

int main() {
    vec3** pixels = new vec3*[IMG_HEIGHT];
    for (int i = 0; i < IMG_HEIGHT; i++) {
        pixels[i] = new vec3[IMG_WIDTH];
    }
    render_image(pixels);
    std::cout << "P3\n" << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            std::cout << pixels[i][j].x << ' ' << pixels[i][j].y << ' ' << pixels[i][j].z << "\n";
        }
    }
    return 0;
}