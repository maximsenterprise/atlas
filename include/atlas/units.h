/*
* units.h
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Atlas units
* Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_UNITS_H
#define ATLAS_UNITS_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Size {
    float width, height, depth;

    Size(float width, float height) : width(width), height(height), depth(0) {
    }

    Size(float width, float height, float depth) : width(width), height(height), depth(depth) {
    }

    explicit Size(glm::vec3 vec) : width(vec.x), height(vec.y), depth(vec.z) {
    }

    glm::vec3 toVec3() const;
};

struct Point {
    float x, y, z;

    Point(float x, float y) : x(x), y(y), z(0) {
    }

    Point(float x, float y, float z) : x(x), y(y), z(z) {
    }

    explicit Point(glm::vec3 vec) : x(vec.x), y(vec.y), z(vec.z) {
    }

    glm::vec3 toVec3() const;
};

struct Color {
    int r, g, b, alpha;

    Color(int r, int g, int b) : r(r), g(g), b(b), alpha(255) {
    }

    Color(int r, int g, int b, int a) : r(r), g(g), b(b), alpha(a) {
    }

    Color(glm::vec4 vec) : r((int)(vec.r * 255)), g((int)(vec.g * 255)), b((int)(vec.b * 255)),
                           alpha((int)(vec.a * 255)) {
    }

    glm::vec4 toVec4() const;
};

using Position = Point;

#endif //ATLAS_UNITS_H
