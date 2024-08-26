#ifndef HITTABLE_H
#define HITTABLE_H

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
        return distance(pos,sphere_center) - sphere_radius;
    }
    vec3 getNormal(const vec3& pos) const override {
        // return normalize(pos-sphere_center);
        return vec3(255,0,0);
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
    vec3 getNormal(const vec3& pos) const override {
        // Placeholder 
        return vec3(255,0,0);
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
    vec3 getNormal(const vec3& pos) const override {
        // Is there a faster way to calculate the normal? So many if conditions is slow and not the cleanest
        // if (pos.x >= center.x-half_width && pos.x <= center.x+half_width && pos.y >= center.y-half_width && pos.y <= center.y+half_width) {
        //     if (pos.z >= center.z+half_width) return vec3(0,0,1);
        //     if (pos.z <= center.z-half_width) return vec3(0,0,-1);
        // }

        // if (pos.z >= center.z-half_width && pos.z <= center.z+half_width && pos.y >= center.y-half_width && pos.y <= center.y+half_width) {
        //     if (pos.x >= center.x+half_width) return vec3(1,0,0);
        //     if (pos.x <= center.x-half_width) return vec3(-1,0,0);
        // }

        // if (pos.x >= center.x-half_width && pos.x <= center.x+half_width && pos.z >= center.z-half_width && pos.z <= center.z+half_width) {
        //     if (pos.y >= center.y+half_width) return vec3(0,1,0);
        //     if (pos.y <= center.y-half_width) return vec3(0,-1,0);
        // }
        return vec3(255,0,0);
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
    vec3 getNormal(const vec3&) const override {
        return vec3(255,0,0);
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