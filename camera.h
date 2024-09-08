#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <random>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "hittable.h"
#include "palettes.h"
using namespace glm;

const float LOWER_BOUND = 0.001;
const float UPPER_BOUND = 100;
float ASPECT_RATIO = 16.0/9.0;

const int IMG_WIDTH = 1280;
const int IMG_HEIGHT = IMG_WIDTH/ASPECT_RATIO;

const float V_WIDTH = 2.0;
const float V_HEIGHT = V_WIDTH/((float)IMG_WIDTH/IMG_HEIGHT);

const int PIXEL_SAMPLES = 8;
const float PIXEL_SCALE = 1.0/PIXEL_SAMPLES;

const int NUM_THREADS = 128;
const int BLOCK_HEIGHT = IMG_HEIGHT/NUM_THREADS;

class Camera {
public:
    Camera(vec3 c_p, float f_l, Palette p, bool a_a): 
        camera_pos(c_p), 
        focal_length(f_l), 
        colorPalette(p),
        anti_alias(a_a)
    {
        initializeViewport();
        pixels = new vec3*[IMG_HEIGHT];
        for (int i = 0; i < IMG_HEIGHT; i++) {
            pixels[i] = new vec3[IMG_WIDTH];
        }
    }

    void initializeViewport() {
        // Default initialization; Camera looks straight ahead 
        viewport_top_left = camera_pos + vec3(0,0,focal_length) + vec3(-V_WIDTH/2.0, V_HEIGHT/2.0, 0);
        viewport_u = vec3(V_WIDTH/IMG_WIDTH, 0, 0);
        viewport_v = vec3(0, -V_HEIGHT/IMG_HEIGHT, 0);
        pixels_top_left = viewport_top_left + viewport_u*0.5f + viewport_v*0.5f;
    }

    void toggleAntiAliasing() {
        anti_alias = !anti_alias;
    }

    void turnCamera(float theta, float phi) {
        mat3 rotationH = mat3(rotate(mat4(1.0f), radians(theta), vec3(0.0f, 1.0f, 0.0f)));
        mat3 rotationV = mat3(rotate(mat4(1.0f), radians(phi), rotationH*vec3(-1.0f,0.0f,0.0f)));
        viewport_u = rotationH*viewport_u;
        viewport_v = rotationV*viewport_v;
        viewport_top_left = rotationV*rotationH*viewport_top_left;
        pixels_top_left = rotationV*rotationH*pixels_top_left;
    }

    float randomFloat() {
        return std::rand()/(RAND_MAX+1.0);
    }

    vec3 rayMarch(vec3 current_pos, const vec3& ray_direction, const std::vector<std::shared_ptr<Hittable>>& scene) {
        std::shared_ptr<Hittable> obj = closestObj(current_pos, scene);
        float dist = obj->SDF(current_pos);
        float totalDist = 0;
        // On the first iteration, we make the initial march...
        for (int k = 0; k < 50; k++) {
            current_pos = current_pos + ray_direction*dist;
            totalDist = totalDist + dist;
            // Everytime a march is made, update the totalDist travelled
            obj = closestObj(current_pos, scene);
            dist = obj->SDF(current_pos);
            // Recalculate the closest object in this new position and our minimum distance to it 
            if (dist < LOWER_BOUND || totalDist > UPPER_BOUND) {
                return colorPalette.generateRGB(totalDist);
            }
            // Break condition 
        }
        return colorPalette.generateRGB(totalDist);
    }
    
    vec3 getColor(float i, float j, const std::vector<std::shared_ptr<Hittable>>& scene) {
        vec3 pixel = pixels_top_left + viewport_u*(float)j + viewport_v*(float)i;
        vec3 ray_direction = (pixel-camera_pos)/distance(camera_pos, pixel);
        return rayMarch(camera_pos, ray_direction, scene);
    }

    vec3 writeColor(int i, int j, const std::vector<std::shared_ptr<Hittable>>& scene) {
        vec3 color(0,0,0);
        for (int k = 0; k < PIXEL_SAMPLES; k++) {
            color+=getColor(i+randomFloat(), j+randomFloat(), scene);
        }
        return color*PIXEL_SCALE;
    }

    void renderImage(const std::vector<std::shared_ptr<Hittable>>&  scene) {
        if (anti_alias) {
            for (int i = 0; i < IMG_HEIGHT; i++) {
                for (int j = 0; j < IMG_WIDTH; j++) {
                    // Take samples to average surrounding colors 
                    pixels[i][j] = writeColor(i, j, scene);
                }
            }
        } else {
            for (int i = 0; i < IMG_HEIGHT; i++) {
                for (int j = 0; j < IMG_WIDTH; j++) {
                    // Get the color directly
                    pixels[i][j] = getColor(i, j, scene);
                }
            }
        }
    }

    void outputImage() {
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
    bool anti_alias;

    Palette colorPalette;
};

#endif