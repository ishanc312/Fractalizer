#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "hittable.h"
using namespace glm;

const float LOWER_BOUND = 0.001;
const float UPPER_BOUND = 1000;
float ASPECT_RATIO = 16.0/9.0;

const int IMG_WIDTH = 1280;
const int IMG_HEIGHT = IMG_WIDTH/ASPECT_RATIO;

const float V_WIDTH = 2.0;
const float V_HEIGHT = V_WIDTH/((float)IMG_WIDTH/IMG_HEIGHT);

class Camera {
public:
    Camera(vec3 c_p, float f_l): camera_pos(c_p), focal_length(f_l) {
        viewport_top_left = vec3(-V_WIDTH/2.0, V_HEIGHT/2.0, focal_length);
        viewport_u = vec3(V_WIDTH/IMG_WIDTH, 0, 0);
        viewport_v = vec3(0, -V_HEIGHT/IMG_HEIGHT, 0);

        pixels_top_left = viewport_top_left + viewport_u*0.5f + viewport_v*0.5f;
        pixels = new vec3*[IMG_HEIGHT];
        for (int i = 0; i < IMG_HEIGHT; i++) {
            pixels[i] = new vec3[IMG_WIDTH];
        }
    }
    void zoom(float zoom_factor) {
        focal_length = focal_length*zoom_factor;
    }

    void rotate_camera(mat3x3 matrix) {
        // Placeholder
    }

    vec3 ray_march(vec3 current_pos, const vec3& ray_direction, const std::vector<std::shared_ptr<Hittable>>& scene) {
        float dist = minSDF(current_pos, scene);
        while (dist >= LOWER_BOUND && dist <= UPPER_BOUND) {
            current_pos = current_pos + ray_direction*dist;
            dist = minSDF(current_pos, scene);
        }
        if (dist < LOWER_BOUND) return vec3(1,0,0);
        return vec3(0,0,0);
    }

    vec3 write_color(int i, int j, const std::vector<std::shared_ptr<Hittable>>& scene) {
        vec3 pixel = pixels_top_left + viewport_u*(float)j + viewport_v*(float)i;
        vec3 ray_direction = (pixel-camera_pos)/distance(camera_pos, pixel);
        vec3 n_vec = ray_march(camera_pos, ray_direction, scene);
        return vec3((int)255.999*n_vec.x, (int)255.999*n_vec.y, (int)255.999*n_vec.z);
    }

    void render_image(const std::vector<std::shared_ptr<Hittable>>& scene) {
        for (int i = 0; i < IMG_HEIGHT; i++) {
            for (int j = 0; j < IMG_WIDTH; j++) {
                pixels[i][j] = write_color(i, j, scene);
            }
        }
    }

    void output_image() {
        std::cout << "P3\n" << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";
        for (int i = 0; i < IMG_HEIGHT; i++) {
            for (int j = 0; j < IMG_WIDTH; j++) {
                std::cout << pixels[i][j].x << ' ' << pixels[i][j].y << ' ' << pixels[i][j].z << "\n";
            }
        }
        std::clog << "Rendering Complete." << '\n';
    }

private:
    vec3 camera_pos;
    float focal_length;

    vec3 viewport_top_left;
    vec3 viewport_u;
    vec3 viewport_v;

    vec3 pixels_top_left;
    vec3** pixels;
};

#endif