#ifndef HITTABLE_H
#define HITTABLE_H

#include <vector>
#include "glm/glm.hpp"

using namespace glm;

class Hittable {
public:
    // Later, implement a "bounding volume" member for BVH Optimization
    virtual float SDF(const vec3& pos) const = 0;  
};

class Sphere : public Hittable {
public:
    Sphere(vec3 c, float r): sphere_center(c), sphere_radius(r) {}
    float SDF(const vec3& pos) const override {
        return distance(pos,sphere_center) - sphere_radius;
    }
private:
    vec3 sphere_center;
    float sphere_radius;
};

class fractSphere : public Hittable {
public:
    fractSphere(vec3 c, float r): sphere_center(c), sphere_radius(r) {}
    float SDF(const vec3& pos) const override {
        return distance(mod(pos, 1.0f), sphere_center) - sphere_radius;
    }
private:
    vec3 sphere_center;
    float sphere_radius;
};

class Cube : public Hittable {
public:
    Cube(vec3 c, float w): center(c), width(w) {
        half_width = width/2.0f;
        b = vec3(half_width);
    }
    float SDF(const vec3& pos) const override {
        vec3 q = abs(pos - center) - b;
        return min(max(q.x, max(q.y, q.z)), 0.0f) + length(max(q, 0.0f));
    }
private:
    float width;
    float half_width;
    vec3 center;
    vec3 b;
};

class fractCube : public Hittable {
public:
    fractCube(vec3 c, float w): center(c), width(w) {
        half_width = width/2.0f;
        b = vec3(half_width);
    }
    float SDF(const vec3& pos) const override {
        vec3 q = abs(mod(pos,1.0f)-center) - b;
        return min(max(q.x, max(q.y, q.z)), 0.0f) + length(max(q, 0.0f));
    }
private:
    float width;
    float half_width;
    vec3 center;
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