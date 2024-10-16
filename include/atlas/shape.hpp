/*
 shape.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Shape abstraction layer for the Atlas Engine
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_SHAPE_HPP
#define ATLAS_SHAPE_HPP

#include "atlas/camera.hpp"
#include "atlas/opengl/glew.h"
#include "atlas/opengl/glm/ext/matrix_float3x3.hpp"
#include "atlas/scene.hpp"
#include "atlas/unit.hpp"
#include "atlas/utilities/utils.hpp"
#include "atlas/component.hpp"
#include <string>

namespace atlas
{

class Triangle : public Component
{
public:
    Triangle(Scene* scene, Size size, Position position, std::string name = "Triangle");
    void render();
    void setup();
    GLuint program;
    void set_model(MVPPackage package);
    Position get_position();
    void update_position(Position position);

private:
    GLuint VBO = 0;
    GLuint VAO = 0; 
    glm::mat4 model = glm::mat4(1.0f);
    MVPPackage mvp;
 
    float vertices[]; 
};

}

#endif // ATLAS_SHAPE_HPP
