/*
 shape.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Shape abstraction layer for the Atlas Engine
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "atlas/opengl/glew.h"
#include "atlas/scene.hpp"

namespace atlas
{

class Triangle
{
public:
    Triangle(Scene* scene);
    void render();
    void setup();

private:
    GLuint program;
    GLuint VBO = 0;
    GLuint VAO = 0;

    static const float vertices[];
};

}

#endif // SHAPE_HPP
