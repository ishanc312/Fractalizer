#ifndef HITTABLE_H
#define HITTABLE_H

#include <iostream>
#include <vector>
#include "glm/glm.hpp"

using namespace glm;

class Hittable {
public:
    virtual float SDF(const vec3& pos) const = 0;  
};

class Sphere : public Hittable {
public:
    Sphere(vec3 c, float r): sphere_center(c), sphere_radius(r) {}
    float SDF(const vec3& pos) const override {
        return distance(sphere_center, pos) - sphere_radius;
    }
private:
    vec3 sphere_center;
    float sphere_radius;
};

class Cube : public Hittable {
public:
    Cube(vec3 c, float w): corner(c), width(w) {
        b = vec3(width);
    }
    float SDF(const vec3& pos) const override {
        vec3 q = abs(pos - corner) - b;
        return min(max(q.x, max(q.y, q.z)), 0.0f) + length(max(q, 0.0f));
    }
private:
    float width;
    vec3 corner;
    vec3 b;
};

float minSDF(const vec3& pos, const std::vector<std::shared_ptr<Hittable>>& test) {
    float minDist = test[0]->SDF(pos);
    for (int k = 1; k < test.size(); k++) {
        float dist = test[k]->SDF(pos);
        if (dist < minDist) minDist = dist;
    }
    return minDist;
}

#endif