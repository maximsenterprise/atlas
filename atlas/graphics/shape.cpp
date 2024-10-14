/*
 shape.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Shape code for the Atlas engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/shape.hpp"
#include "atlas/component.hpp"
#include "atlas/core/shader.hpp"
#include "atlas/opengl/glew.h"
#include "atlas/scene.hpp"
#include "atlas/unit.hpp"
#include <iostream>

namespace atlas {

void Triangle::render() {

    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}

Triangle::Triangle(Scene *scene, Size size, Position position, std::string name)
    : Component(name, "TriangleComponent", position, size) {

    program = compileVertexShader("shaders/triangle/triangle.vert");
    GLuint fragmentShader =
        compileFragmentShader("shaders/triangle/triangle.frag");
    program = linkShaderProgram(program, fragmentShader);
    scene->addSetupFunction([this]() { glUseProgram(program); });

    float vertices[] = {-size.width, -size.height, 0.0f,
                        size.width,  -size.height, 0.0f,
                        0.0f,        size.height,  0.0f};

    if (VAO == 0) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void *)0);
        glEnableVertexAttribArray(0);
    }

    if (GLenum error = glGetError() != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}
} // namespace atlas
