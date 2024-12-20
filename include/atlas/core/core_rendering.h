/*
* core_rendering.h
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Core rendering functionality for atlas
* Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_CORE_RENDERING_H
#define ATLAS_CORE_RENDERING_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <functional>

#include "atlas/graphics.h"

struct CoreVertex {
    glm::vec3 position;
    glm::vec4 color;
};

struct CoreRenderingPackage {
    GLuint program;
    GLuint vao;
    GLuint vbo;
    std::vector<CoreVertex> vertices;
    std::function<void()> renderFunction;
};

class RenderInstance {
public:
    GLuint getProgramFromLocal(const char* vertexShader, const char* fragmentShader);
    GLuint getProgramFromShader(AtlasShader shader);

    static glm::mat4 model;
    static glm::mat4 view;
    static glm::mat4 projection;

    void renderToScreen(std::vector<CoreVertex> vertices, GLuint program, int count, GLenum mode);

    RenderInstance() : packages({}) {
    }

private:
    std::vector<CoreRenderingPackage> packages;
};

#endif //ATLAS_CORE_RENDERING_H
