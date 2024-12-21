/*
* shape.cpp
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: 
* Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/shape.h"

#include <iostream>

#include "atlas/application.h"

Triangle::Triangle(const std::string name, Color color, Size size, Position position, Shader shader) : Component(name),
    color(color),
    size(size),
    position(position), shader(shader) {
    CoreVertex v1 = {position.toVec3(), color.toVec4()};
    CoreVertex v2 = {glm::vec3(position.x + size.width, position.y, position.z), color.toVec4()};
    CoreVertex v3 = {glm::vec3(position.x + size.width / 2, position.y + size.height, position.z), color.toVec4()};
    vertices = {v1, v2, v3};
}

void Triangle::render() {
    GLuint program;
    if (shader.isLocal) {
        program = Application::instance.getProgramFromLocal(shader.vertexShader, shader.fragmentShader);
    }
    else {
        program = Application::instance.getProgramFromShader(shader.type);
    }

    std::cout << "Rendering triangle" << std::endl;

    Application::instance.renderToFramebuffer(vertices, program, 3, GL_TRIANGLES);
}

void Triangle::setColorOfPoint(Color color, int point) {
    vertices[point].color = color.toVec4();
}

void Triangle::useVertexSet(std::array<CoreVertex, 3> vertices) {
    std::vector<CoreVertex> newVertices(vertices.begin(), vertices.end());
    this->vertices = newVertices;
}

void Triangle::setShader(Shader shader) {
    this->shader = shader;
}


