/*
* core_rendering.cpp
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Core rendering functionalities for Atlas
* Copyright (c) 2024 Maxims Enterprise
*/

#include <atlas/core/core_rendering.h>
#include <atlas/data.hpp>
#include "atlas/application.h"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 RenderInstance::model = glm::mat4(1.0f);
glm::mat4 RenderInstance::view = glm::mat4(1.0f);
glm::mat4 RenderInstance::projection = glm::mat4(1.0f);

GLuint RenderInstance::getProgramFromLocal(const char* vertexShader, const char* fragmentShader) {
    std::ifstream vertexFile(vertexShader);
    std::ifstream fragmentFile(fragmentShader);

    if (!vertexFile || !fragmentFile) {
        std::cerr << "Failed to open shader files" << std::endl;
        return 0;
    }

    std::string vertexSource((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
    std::string fragmentSource((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());

    const char* vertexSourceC = vertexSource.c_str();
    const char* fragmentSourceC = fragmentSource.c_str();

    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexSourceC, nullptr);
    glCompileShader(vertexShaderID);

    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentSourceC, nullptr);
    glCompileShader(fragmentShaderID);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderID);
    glAttachShader(shaderProgram, fragmentShaderID);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return shaderProgram;
}

GLuint RenderInstance::getProgramFromShader(AtlasShader shader) {
    switch (shader) {
    case AtlasShader::Default:
        std::string vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPosition;
        layout(location = 1) in vec4 aColor;
        out vec4 vertexColor;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main() {
            gl_Position = projection * view * model * vec4(aPosition, 1.0);
            vertexColor = aColor;
        })";

        std::string fragmentShaderSource = R"(
        #version 330 core
        in vec4 vertexColor;
        out vec4 FragColor;
        void main() {
            FragColor = vertexColor;
        })";

        const char* vertexSourceC = vertexShaderSource.c_str();
        const char* fragmentSourceC = fragmentShaderSource.c_str();

        GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderID, 1, &vertexSourceC, nullptr);
        glCompileShader(vertexShaderID);

        GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderID, 1, &fragmentSourceC, nullptr);
        glCompileShader(fragmentShaderID);

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShaderID);
        glAttachShader(shaderProgram, fragmentShaderID);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        return shaderProgram;
    }
}

void RenderInstance::renderToScreen(std::vector<CoreVertex> vertices, GLuint program, int count, GLenum mode) {
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CoreVertex), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CoreVertex), (void*)0); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CoreVertex), (void*)offsetof(CoreVertex, color)); // Color
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::function<void()> renderFunction = [program, VAO, count, mode, this]()
    {
        glUseProgram(program);

        GLint modelLoc = glGetUniformLocation(program, "model");
        GLint viewLoc = glGetUniformLocation(program, "view");
        GLint projectionLoc = glGetUniformLocation(program, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawArrays(mode, 0, count);
        glBindVertexArray(0);
    };

    Application::renderFunctions.add_function(renderFunction);
}

