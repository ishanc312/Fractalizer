#ifndef HITTABLE_H
#define HITTABLE_H

#include <iostream>
#include <vector>
#include "glm/glm.hpp"

using namespace glm;

class hittable {
public:
    // What other members? Figure out was we go on; for now, a SDF should be common to every primitive 
    virtual float SDF(const vec3& pos) const = 0;  
};

class sphere : public hittable {
public:
    sphere(vec3 c, float r): sphere_center(c), sphere_radius(r) {}
    float SDF(const vec3& pos) const override {
        return distance(sphere_center, pos) - sphere_radius;
    }
private:
    vec3 sphere_center;
    float sphere_radius;
};

float minSDF(const std::vector<std::shared_ptr<hittable>>& test, const vec3& pos) {
    float minDistance = test[0]->SDF(pos);
    for (int k = 1; k < test.size(); k++) {
        float dist = test[k]->SDF(pos);
        if (dist < minDistance) minDistance = dist;
    }
    return minDistance;
}

#endif