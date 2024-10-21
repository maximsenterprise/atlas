/*
 unit.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Units and mesures for space
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_UNIT_HPP
#define ATLAS_UNIT_HPP

#include "atlas/opengl/glm/ext/vector_float3.hpp"
#include "atlas/opengl/glm/ext/vector_float4.hpp"
#include <atlas/opengl/glm/vec3.hpp>

namespace atlas {

class Timestamp {
public:
    int year, month, day, hour, minute, second;
    Timestamp(int year, int month, int day, int hour, int minute, int second) : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {};
    void out();
};

class Position {
public:
    float x, y, z;
    Position(float x, float y, float z) : x(x), y(y), z(z) {};
    Position(float x, float y) : x(x), y(y), z(0) {};
    glm::vec3 get();
    void out();
};

class Size {
public:
    float width, height, depth;
    Size(float width, float height, float depth) : width(width / 1000), height(height / 1000), depth(depth / 1000) {};
    Size(float width, float height) : width(width / 1000), height(height / 1000), depth(0) {};
    glm::vec3 get();
};

class Color {
public:
    int r, g, b, a;
    Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {};
    Color(int hex, int alpha) : r((hex >> 16) & 0xFF), g((hex >> 8) & 0xFF), b(hex & 0xFF), a(alpha) {};
    glm::vec4 get();
    Color with_alpha(int alpha);
};

class AtlasPalette {
public:
    static const Color white;
    static const Color black;
    static const Color red;
    static const Color green;
    static const Color blue;
    static const Color yellow;
    static const Color cyan;
    static const Color magenta;
    static const Color orange;
    static const Color purple;
    static const Color pink;
    static const Color brown;
    static const Color grey;
};

}

#endif // ATLAS_UNIT_HPP
