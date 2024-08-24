#ifndef HITTABLE_H
#define HITTABLE_H

#include <iostream>
#include <vector>
#include "glm/glm.hpp"

using namespace glm;

class Hittable {
public:
    virtual vec3 getNormal(const vec3& pos) const = 0;
    virtual float SDF(const vec3& pos) const = 0;  
};

class Sphere : public Hittable {
public:
    Sphere(vec3 c, float r): sphere_center(c), sphere_radius(r) {}

    float SDF(const vec3& pos) const override {
        return distance(sphere_center, pos) - sphere_radius;
    }
    vec3 getNormal(const vec3& pos) const override {
        return normalize(pos-sphere_center);
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
    // vec3 getNormal(const vec3& pos) const override {
    // }
private:
    float width;
    vec3 corner;
    vec3 b;
};

std::shared_ptr<Hittable> closestObj(const vec3& pos, const std::vector<std::shared_ptr<Hittable>>& test) {
    std::shared_ptr<Hittable> obj = test[0];
    for (int k = 1; k < test.size(); k++) {
        if (test[k]->SDF(pos) < obj->SDF(pos)) obj = test[k];
    }
    return obj;
}

#endif