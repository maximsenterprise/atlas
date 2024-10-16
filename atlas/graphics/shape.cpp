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
#include "atlas/core/console.hpp"
#include "atlas/core/shader.hpp"
#include "atlas/opengl/glew.h"
#include "atlas/opengl/glm/gtc/matrix_transform.hpp"
#include "atlas/opengl/glm/gtc/type_ptr.hpp"
#include "atlas/scene.hpp"
#include "atlas/unit.hpp"
#include "atlas/utilities/utils.hpp"
#include <iostream>

namespace atlas {

void Triangle::render() {
    glUseProgram(program); 
    if (model != glm::mat4(1.0f)) { 
        glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, GL_FALSE, &model[0][0]);
    }
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Triangle::set_model(MVPPackage package) { 
    this->model = package.default_mvp;
    this->mvp = package;
}

Position Triangle::get_position() {
    return position;
}

void Triangle::update_position(Position position) {
    Log::add_entry("Position updated", "Atlas:" + name);
    this->position = position;
    glm::mat4 new_mvp = this->mvp.compile();
    new_mvp = glm::translate(new_mvp, position.get());
    this->model = new_mvp;
}

Triangle::Triangle(Scene *scene, Size size, Position position, std::string name)
    : Component(name, "TriangleComponent", position, size) {
    program = compileVertexShader("shaders/triangle/triangle.vert");
    GLuint fragmentShader =
        compileFragmentShader("shaders/triangle/triangle.frag");
    program = linkShaderProgram(program, fragmentShader);
 
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

    GLenum error;
    if ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }

    representation->component = this;
    ComponentTree::components.push_back(representation);
    Log::add_entry("Triangle " + name + " created", "AtlasEngine:" + name);
}
} // namespace atlas
