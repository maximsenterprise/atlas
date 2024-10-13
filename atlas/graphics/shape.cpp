/*
 shape.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Shape code for the Atlas engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/shape.hpp"
#include "atlas/opengl/glew.h"
#include "atlas/core/shader.hpp"
#include "atlas/scene.hpp"
#include <iostream>

namespace atlas
{

const float Triangle::vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

void Triangle::render() {

    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}

Triangle::Triangle(Scene* scene) {
    program = compileVertexShader("shaders/triangle/triangle.vert");
    GLuint fragmentShader = compileFragmentShader("shaders/triangle/triangle.frag");
    program = linkShaderProgram(program, fragmentShader);
    scene->addSetupFunction([this](){ glUseProgram(program); }); 


    if (VAO == 0) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    if (GLenum error = glGetError() != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}

}
