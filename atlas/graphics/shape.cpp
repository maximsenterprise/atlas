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
#include <algorithm>
#include <iostream>
#include <sys/_types/_wint_t.h>

namespace atlas {

void Triangle::render() {
    // Render the triangle
    glUseProgram(program);
    if (model != glm::mat4(1.0f)) {
        // Set position
        glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, GL_FALSE,
                           &model[0][0]);
    }
    // Set color
    glUniform4fv(glGetUniformLocation(program, "color_in"), 1,
                 glm::value_ptr(color_global));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Triangle::set_model(MVPPackage package) {
    this->model = package.default_mvp;
    this->mvp = package;
}

Position Triangle::get_position() { return position; }

void Triangle::update_position(Position position) {
    Log::add_entry("Position updated", "Atlas:" + name);
    this->position = position;
    glm::mat4 new_mvp = this->mvp.compile();
    new_mvp = glm::translate(new_mvp, position.get());
    this->model = new_mvp;
}

void Triangle::color(Color color) { this->color_global = color.get(); }

void Triangle::init_triangle(Size size, Position position, Scene *scene) {
    // Begin compiling the program
    program = compileVertexShader("shaders/triangle/triangle.vert");
    GLuint fragmentShader =
        compileFragmentShader("shaders/triangle/triangle.frag");
    program = linkShaderProgram(program, fragmentShader);

    // Make the triangle
    float vertices[] = {-size.width, -size.height, 0.0f,
                        size.width,  -size.height, 0.0f,
                        0.0f,        size.height,  0.0f};

    // Building the VAO and the VBO
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

Triangle::Triangle(Scene *scene, Size size, Position position, Color color,
                   std::string name)
    : Component(name, "TriangleComponent", position, size) {
    init_triangle(size, position, scene);
    this->color_global = color.get();
}

Triangle::Triangle(Scene *scene, Size size, Position position, std::string name)
    : Component(name, "TriangleComponent", position, size) {
    init_triangle(size, position, scene);
    this->color_global = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
} // namespace atlas

// Cube implementation
namespace atlas {
Cube::Cube(Scene *scene, Size size, Position position, Color color,
           std::string name)
    : Component(name, "CubeComponent", position, size) {
    init_cube(size, position, scene);
    this->color_global = color.get();
    color_withglobal = true;
}

Cube::Cube(Scene *scene, Size size, Position position, std::string name)
    : Component(name, "CubeComponent", position, size) {
    init_cube(size, position, scene);
    this->color_global = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    color_withglobal = true;
}

void Cube::init_cube(Size size, Position position, Scene *scene) {
    program = compileVertexShader("shaders/triangle/triangle.vert");
    GLuint fragmentShader =
        compileFragmentShader("shaders/triangle/triangle.frag");
    program = linkShaderProgram(program, fragmentShader);

    // Make the Cube
    float vertices[] = {
        // First triangle (front face)
        -size.width, -size.height, -size.depth, // Bottom-left
        -size.width, -size.height, size.depth,  // Bottom-right
        -size.width, size.height, size.depth,   // Top-right

        // Second triangle (left face)
        size.width, size.height, -size.depth,   // Top-right
        -size.width, -size.height, -size.depth, // Bottom-left
        -size.width, size.height, -size.depth,  // Top-left

        // Third triangle (bottom face)
        size.width, -size.height, size.depth,   // Bottom-right
        -size.width, -size.height, -size.depth, // Bottom-left
        size.width, -size.height, -size.depth,  // Bottom-left

        // Fourth triangle (right face)
        size.width, size.height, -size.depth,   // Top-right
        size.width, -size.height, -size.depth,  // Bottom-right
        -size.width, -size.height, -size.depth, // Bottom-left

        // Fifth triangle (front face)
        -size.width, -size.height, -size.depth, // Bottom-left
        -size.width, size.height, size.depth,   // Top-right
        -size.width, size.height, -size.depth,  // Top-left

        // Sixth triangle (back face)
        size.width, -size.height, size.depth,   // Bottom-right
        -size.width, -size.height, size.depth,  // Bottom-left
        -size.width, -size.height, -size.depth, // Bottom-left

        // Seventh triangle (left face)
        -size.width, size.height, size.depth,  // Top-right
        -size.width, -size.height, size.depth, // Bottom-left
        size.width, -size.height, size.depth,  // Bottom-right

        // Eighth triangle (top face)
        size.width, size.height, size.depth,   // Top-right
        size.width, -size.height, -size.depth, // Bottom-right
        size.width, size.height, -size.depth,  // Top-right

        // Ninth triangle (bottom face)
        size.width, -size.height, -size.depth, // Bottom-right
        size.width, size.height, size.depth,   // Top-right
        size.width, -size.height, size.depth,  // Bottom-right

        // Tenth triangle (back face)
        size.width, size.height, size.depth,   // Top-right
        size.width, size.height, -size.depth,  // Top-left
        -size.width, size.height, -size.depth, // Bottom-left

        // Eleventh triangle (front face)
        size.width, size.height, size.depth,   // Top-right
        -size.width, size.height, -size.depth, // Top-left
        -size.width, size.height, size.depth,  // Bottom-right

        // Twelfth triangle (right face)
        size.width, size.height, size.depth,  // Top-right
        -size.width, size.height, size.depth, // Bottom-left
        size.width, -size.height, size.depth  // Bottom-right
    };
    std::copy(std::begin(temp_color_buffer_data), std::end(temp_color_buffer_data), gl_color_buffer_data);

    // Building the VAO and the VBO
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
    Log::add_entry("Cube " + name + " created", "AtlasEngine:" + name);
}

const GLfloat Cube::temp_color_buffer_data[144] = {
        // Triangle 1 (Front face, first triangle)
        0.583f, 0.483f, 0.844f, 1.0f, 0.583f, 0.483f, 0.844f, 1.0f, 0.583f,
        0.483f, 0.844f, 1.0f,

        // Triangle 2 (Front face, second triangle)
        0.822f, 0.569f, 0.201f, 1.0f, 0.822f, 0.569f, 0.201f, 1.0f, 0.822f,
        0.569f, 0.201f, 1.0f,

        // Triangle 3 (Back face, first triangle)
        0.435f, 0.602f, 0.223f, 1.0f, 0.435f, 0.602f, 0.223f, 1.0f, 0.435f,
        0.602f, 0.223f, 1.0f,

        // Triangle 4 (Back face, second triangle)
        0.310f, 0.747f, 0.185f, 1.0f, 0.310f, 0.747f, 0.185f, 1.0f, 0.310f,
        0.747f, 0.185f, 1.0f,

        // Triangle 5 (Left face, first triangle)
        0.597f, 0.770f, 0.761f, 1.0f, 0.597f, 0.770f, 0.761f, 1.0f, 0.597f,
        0.770f, 0.761f, 1.0f,

        // Triangle 6 (Left face, second triangle)
        0.559f, 0.436f, 0.730f, 1.0f, 0.559f, 0.436f, 0.730f, 1.0f, 0.559f,
        0.436f, 0.730f, 1.0f,

        // Triangle 7 (Right face, first triangle)
        0.359f, 0.583f, 0.152f, 1.0f, 0.359f, 0.583f, 0.152f, 1.0f, 0.359f,
        0.583f, 0.152f, 1.0f,

        // Triangle 8 (Right face, second triangle)
        0.483f, 0.596f, 0.789f, 1.0f, 0.483f, 0.596f, 0.789f, 1.0f, 0.483f,
        0.596f, 0.789f, 1.0f,

        // Triangle 9 (Top face, first triangle)
        0.559f, 0.861f, 0.639f, 1.0f, 0.559f, 0.861f, 0.639f, 1.0f, 0.559f,
        0.861f, 0.639f, 1.0f,

        // Triangle 10 (Top face, second triangle)
        0.195f, 0.548f, 0.859f, 1.0f, 0.195f, 0.548f, 0.859f, 1.0f, 0.195f,
        0.548f, 0.859f, 1.0f,

        // Triangle 11 (Bottom face, first triangle)
        0.014f, 0.184f, 0.576f, 1.0f, 0.014f, 0.184f, 0.576f, 1.0f, 0.014f,
        0.184f, 0.576f, 1.0f,

        // Triangle 12 (Bottom face, second triangle)
        0.771f, 0.328f, 0.970f, 1.0f, 0.771f, 0.328f, 0.970f, 1.0f, 0.771f,
        0.328f, 0.970f, 1.0f};


void Cube::color_face(Color color, CubeFace cube_face) {
    bool setup_process = false;
    if (color_withglobal) {
        color_withglobal = false;
        setup_process = true;
    }

    /* To color the cube face, we need to color the vertices of the face
       Note that in an array of vertices, each triangle has 3 vertices, and we
       need two triangles to make a face, thus each face has 3 layers of 4
       values (r, g, b, a):
         0-24 -> Front face 
         24-48 -> Back face 
         48-72 -> Left face 
         72-96 -> Right face
         96-120 -> Top face
         120-144 -> Bottom face
    */
    int offset = 0;
    switch (cube_face) {
    case CubeFace::FRONT:
        offset = 0;
        for (int i = offset; i < 24; i += 4) {
            gl_color_buffer_data[i] = color.r / 255.0f;
            gl_color_buffer_data[i + 1] = color.g / 255.0f;
            gl_color_buffer_data[i + 2] = color.b / 255.0f;
            gl_color_buffer_data[i + 3] = color.a / 255.0f;
        }
        break;
    case CubeFace::BACK:
        offset = 24;
        for (int i = offset; i < 48; i += 4) {
            gl_color_buffer_data[i] = color.r / 255.0f;
            gl_color_buffer_data[i + 1] = color.g / 255.0f;
            gl_color_buffer_data[i + 2] = color.b / 255.0f;
            gl_color_buffer_data[i + 3] = color.a / 255.0f;
        }
        break;
    case CubeFace::LEFT:
        offset = 48;
        for (int i = offset; i < 72; i += 4) {
            gl_color_buffer_data[i] = color.r / 255.0f;
            gl_color_buffer_data[i + 1] = color.g / 255.0f;
            gl_color_buffer_data[i + 2] = color.b / 255.0f;
            gl_color_buffer_data[i + 3] = color.a / 255.0f;
        }
        break;
    case CubeFace::RIGHT:
        offset = 72;
        for (int i = offset; i < 96; i += 4) {
            gl_color_buffer_data[i] = color.r / 255.0f;
            gl_color_buffer_data[i + 1] = color.g / 255.0f;
            gl_color_buffer_data[i + 2] = color.b / 255.0f;
            gl_color_buffer_data[i + 3] = color.a / 255.0f;
        }
        break;
    case CubeFace::TOP:
        offset = 96; 
        for (int i = offset; i < 120; i += 4) {
            gl_color_buffer_data[i] = color.r / 255.0f;
            gl_color_buffer_data[i + 1] = color.g / 255.0f;
            gl_color_buffer_data[i + 2] = color.b / 255.0f;
            gl_color_buffer_data[i + 3] = color.a / 255.0f;
        }
        break;
    case CubeFace::BOTTOM:
        offset = 120;
        for (int i = offset; i < 144; i += 4) {
            gl_color_buffer_data[i] = color.r / 255.0f;
            gl_color_buffer_data[i + 1] = color.g / 255.0f;
            gl_color_buffer_data[i + 2] = color.b / 255.0f;
            gl_color_buffer_data[i + 3] = color.a / 255.0f;
        }
        break;
    }
    if (setup_process) {
        program = compileVertexShader("shaders/cube/cube.vert");
        GLuint fragmentShader = compileFragmentShader("shaders/cube/cube.frag");
        program = linkShaderProgram(program, fragmentShader); 
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gl_color_buffer_data),
                     gl_color_buffer_data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
    }
}

void Cube::render() {
    // Render the cube
    glUseProgram(program);
    if (model != glm::mat4(1.0f)) {
        // Set position
        glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, GL_FALSE,
                           &model[0][0]);
    }
    if (color_withglobal) {
        // Set color
        glUniform4fv(glGetUniformLocation(program, "color_in"), 1,
                     glm::value_ptr(color_global));
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer); 
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
    }
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Cube::set_model(MVPPackage package) {
    this->model = package.default_mvp;
    this->mvp = package;
}

Position Cube::get_position() { return position; }
} // namespace atlas
