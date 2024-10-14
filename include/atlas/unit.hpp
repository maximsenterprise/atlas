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
#include <atlas/opengl/glm/vec3.hpp>

namespace atlas {

class Position {
public:
    float x, y, z;
    Position(float x, float y, float z) : x(x), y(y), z(z) {};
    glm::vec3 get();
};

class Size {
public:
    float width, height, depth;
    Size(float width, float height, float depth) : width(width / 1000), height(height / 1000), depth(depth / 1000) {};
    glm::vec3 get();
};

}

#endif // ATLAS_UNIT_HPP
