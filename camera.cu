#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <random>
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "hittable.cuh"
using namespace glm;

float ASPECT_RATIO = 16.0/9.0;

const int IMG_WIDTH = 1280;
const int IMG_HEIGHT = IMG_WIDTH/ASPECT_RATIO;

const float V_WIDTH = 2.0;
const float V_HEIGHT = V_WIDTH/((float)IMG_WIDTH/IMG_HEIGHT);

const int PIXEL_SAMPLES = 8;
const float PIXEL_SCALE = 1.0/PIXEL_SAMPLES;

class Camera {
public:
    __host__ Camera() {}
    __host__ Camera(vec3 c_p, float f_l): camera_pos(c_p), focal_length(f_l) {
        initializeViewport();
    }

    vec3 camera_pos;
    float focal_length;

    vec3 viewport_top_left;
    vec3 viewport_u;
    vec3 viewport_v;
    vec3 pixels_top_left;

    __host__ void initializeViewport() {
        viewport_top_left = camera_pos + vec3(0,0,focal_length) + vec3(-V_WIDTH/2.0, V_HEIGHT/2.0, 0);
        viewport_u = vec3(V_WIDTH/IMG_WIDTH, 0, 0);
        viewport_v = vec3(0, -V_HEIGHT/IMG_HEIGHT, 0);
        pixels_top_left = viewport_top_left + viewport_u*0.5f + viewport_v*0.5f;
    }
};

__constant__ Sphere d_sphere;
__constant__ Camera d_cam;

__device__ vec3 rayMarch(vec3 current_pos, const vec3& ray_direction) {
    float dist = d_sphere.SDF(current_pos);
    for (int k = 0; k < 50; k++) {
        current_pos = current_pos + ray_direction*dist;
        dist = d_sphere.SDF(current_pos);
        if (dist < 0.001) {
            return vec3(255,0,0);
        }
    }
    return vec3(0,0,0);
}

__global__ void testRender(vec3* d_pixels, int HEIGHT, int WIDTH) {
    int i = blockDim.y*blockIdx.y + threadIdx.y;
    int j = blockDim.x*blockIdx.x + threadIdx.x;
    if (i < HEIGHT && j < WIDTH) {
        vec3 pixel = d_cam.pixels_top_left + d_cam.viewport_u*(float)j + d_cam.viewport_v*(float)i;
        vec3 ray_direction = (pixel-d_cam.camera_pos)/distance(pixel, d_cam.camera_pos);
        d_pixels[i*WIDTH + j] = rayMarch(d_cam.camera_pos, ray_direction);
    } 
}

__host__ vec3* loadScene(const Camera& h_cam, const Sphere& h_sphere) {
    cudaMemcpyToSymbol(d_sphere, &h_sphere, sizeof(Sphere));
    cudaMemcpyToSymbol(d_cam, &h_cam, sizeof(Camera));
    
    vec3* h_pixels = new vec3[IMG_HEIGHT*IMG_WIDTH];
    vec3* d_pixels;
    cudaMalloc((void**)&d_pixels, IMG_HEIGHT*IMG_WIDTH*sizeof(vec3));
    cudaMemcpy(d_pixels, h_pixels, IMG_HEIGHT*IMG_WIDTH*sizeof(vec3), cudaMemcpyHostToDevice);

    dim3 blocksPerGrid((IMG_WIDTH+8-1)/8, (IMG_HEIGHT+8-1)/8);
    dim3 threadsPerBlock(8,8);
    testRender<<<blocksPerGrid, threadsPerBlock>>>(d_pixels, IMG_HEIGHT, IMG_WIDTH);
    cudaDeviceSynchronize();
    cudaError_t err = cudaGetLastError();
    std::cerr << cudaGetErrorName(err) << ": " << cudaGetErrorString(err) << '\n';
    cudaMemcpy(h_pixels, d_pixels, IMG_HEIGHT*IMG_WIDTH*sizeof(vec3), cudaMemcpyDeviceToHost);
    cudaFree(d_pixels);
    std::clog << "Rendering Complete." << '\n';
    return h_pixels;
}

__host__ void outputImage(vec3* pixels) {
    std::cout << "P3\n" << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            std::cout << pixels[i*IMG_WIDTH + j].x << ' ' << pixels[i*IMG_WIDTH + j].y << ' ' << pixels[i*IMG_WIDTH + j].z << "\n";
        }
    }
    std::clog << "Image Creation Complete." << '\n';
}

#endif