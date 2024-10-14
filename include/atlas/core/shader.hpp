/*
 shader.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Shader management with OpenGL's shader language
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_SHADER_HPP
#define ATLAS_SHADER_HPP

#include <atlas/opengl/glew.h>

namespace atlas
{
    GLuint compileVertexShader(const char* source); 
    GLuint compileFragmentShader(const char* source);
    GLuint linkShaderProgram(GLuint vertexShader, GLuint fragmentShader);
}

#endif // ATLAS_SHADER_HPP
