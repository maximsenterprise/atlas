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
#include "atlas/opengl/glm/ext/vector_float4.hpp"
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
    Triangle(Scene* scene, Size size, Position position, Color color, std::string name = "Triangle");
    Triangle(Scene* scene, Size size, Position position, std::string name = "Triangle");
    void render();
    void setup();
    GLuint program;
    void set_model(MVPPackage package);
    Position get_position();
    void update_position(Position position);
    void color(Color color);
    glm::vec4 color_global;

private:
    GLuint VBO = 0;
    GLuint VAO = 0; 
    glm::mat4 model = glm::mat4(1.0f);
    MVPPackage mvp;
    void init_triangle(Size size, Position position, Scene* scene);
 
    float vertices[]; 
};

enum class CubeFace {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

class Cube : public Component
{
public:
    Cube(Scene* scene, Size size, Position position, Color color, std::string name = "Cube");
    Cube(Scene* scene, Size size, Position position, std::string name = "Cube");
    void render();
    void setup();
    GLuint program;
    void set_model(MVPPackage package);
    Position get_position();
    void update_position(Position position);

    // Color each face of the cube separately
    void color(Color color);
    void color_face(Color color, CubeFace cube_face); 

private:
    GLuint VBO = 0;
    GLuint VAO = 0; 
    glm::mat4 model = glm::mat4(1.0f);
    MVPPackage mvp;
    void init_cube(Size size, Position position, Scene* scene);
    bool color_withglobal;
    GLuint colorBuffer;

    glm::vec4 color_global;
    static const GLfloat temp_color_buffer_data[144]; 
   
    GLfloat gl_color_buffer_data[144];
    float vertices[]; 
};

}

#endif // ATLAS_SHAPE_HPP
