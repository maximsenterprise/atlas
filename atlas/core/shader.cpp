/*
 shader.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Shader implementation for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/core/shader.hpp"
#include "atlas/core/exec_error.hpp"
#include <atlas/opengl/glew.h>
#include <fstream>
#include <string>

namespace atlas
{

GLuint compileVertexShader(const char *source) {
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(source, std::ios::in); 
    if (vertexShaderStream.is_open()) {
        std::string Line = "";
        while (getline(vertexShaderStream, Line)) {
            vertexShaderCode += "\n" + Line;
        }
        vertexShaderStream.close();
    } else {
        ExecutionError("Could not open vertex shader file", true).express();
        return 0;
    }

    GLint result = GL_FALSE;
    int InfoLogLength;

    char const *VertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        ExecutionError(&VertexShaderErrorMessage[0], true).express();
    }

    return VertexShaderID;
}

GLuint compileFragmentShader(const char *source) {
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(source, std::ios::in); 
    if (fragmentShaderStream.is_open()) {
        std::string Line = "";
        while (getline(fragmentShaderStream, Line)) {
            fragmentShaderCode += "\n" + Line;
        }
        fragmentShaderStream.close();
    } else {
        ExecutionError("Could not open fragment shader file", true).express();
        return 0;
    }

    GLint result = GL_FALSE;
    int InfoLogLength;

    char const *FragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        ExecutionError(&FragmentShaderErrorMessage[0], true).express();
    }

    return FragmentShaderID;
}

GLuint linkShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vertexShader);
    glAttachShader(ProgramID, fragmentShader);
    glLinkProgram(ProgramID);

    GLint result = GL_FALSE;
    int InfoLogLength;

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        ExecutionError(&ProgramErrorMessage[0], true).express();
    }

    glDetachShader(ProgramID, vertexShader);
    glDetachShader(ProgramID, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return ProgramID;
}

}
