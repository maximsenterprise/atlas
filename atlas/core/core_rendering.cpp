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
        std::string home = std::getenv("HOME");
        std::ifstream atlasShaderPath(home + "/.atlas");
        if (!atlasShaderPath) {
            throw std::runtime_error("Failed to open ~/.atlas");
        }

        std::string atlasShaderSource;
        std::getline(atlasShaderPath, atlasShaderSource);

        std::string fragmentRoute = atlasShaderSource + "shaders/normal/normal.frag";
        std::string vertexRoute = atlasShaderSource + "shaders/normal/normal.vert";

        return getProgramFromLocal(vertexRoute.c_str(), fragmentRoute.c_str());
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void RenderInstance::createFramebuffer(int width, int height) {
    glGenFramebuffers(1, &framebuffers[0]);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[0]);

    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[0], 0);

    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer creation failed!" << std::endl;
        GLuint error = glGetError();
        std::cerr << "OpenGL Error: " << error << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderInstance::renderToFramebuffer(std::vector<CoreVertex> vertices, GLuint program, int count, GLenum mode) {
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
        std::cout << "Framebuffer 0: " << framebuffers[0] << std::endl;
        std::cout << "Framebuffer 1: " << framebuffers[1] << std::endl;

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[0]);

        glViewport(0, 0, Application::width, Application::height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        applyAnyFramebufferEffect(textures[0]);
    };

    Application::renderFunctions.add_function(renderFunction);
}

void RenderInstance::applyAnyFramebufferEffect(GLuint texture) {
    GLuint program;
    if (postProcessUnit.isLocal) {
    }
    else {
        switch (postProcessUnit.type) {
        case AtlasPostProcessing::None:
        {
            std::string home = std::getenv("HOME");
            std::ifstream atlasShaderPath(home + "/.atlas");
            if (!atlasShaderPath) {
                throw std::runtime_error("Failed to open ~/.atlas");
            }

            std::string atlasShaderSource;
            std::getline(atlasShaderPath, atlasShaderSource);

            std::string fragmentRoute = atlasShaderSource + "post_processing/none/none.frag";
            std::string vertexRoute = atlasShaderSource + "post_processing/none/none.vert";

            program = getProgramFromLocal(vertexRoute.c_str(), fragmentRoute.c_str());
            break;
        }
        case AtlasPostProcessing::Blur:
            applyBlurEffect(texture);
            return;
        default:
            break;
        }
    }

    GLuint texLoc = glGetUniformLocation(program, "screenTexture");
    if (texLoc != -1) {
        glUniform1i(texLoc, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    if (quadVAO == 0) {
        std::cout << "Creating quad" << std::endl;
        float quadVertices[] = {
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        };
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

        // Position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        // Texture coordinate attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    }

    glUseProgram(program);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void RenderInstance::createPongBuffers(int width, int height) {
    glDeleteFramebuffers(2, framebuffers);
    glDeleteTextures(2, textures);

    glGenFramebuffers(1, &framebuffers[0]);
    glGenFramebuffers(1, &framebuffers[1]);
    glGenTextures(1, &textures[0]);
    glGenTextures(1, &textures[1]);

    for (unsigned int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[i], 0);
    }
}

void RenderInstance::applyBlurEffect(GLuint texture) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }
    std::string home = std::getenv("HOME");
    std::ifstream atlasShaderPath(home + "/.atlas");
    if (!atlasShaderPath) {
        throw std::runtime_error("Failed to open ~/.atlas");
    }

    std::string atlasShaderSource;
    std::getline(atlasShaderPath, atlasShaderSource);

    std::string fragmentRoute = atlasShaderSource + "post_processing/blur/blur.frag";
    std::string vertexRoute = atlasShaderSource + "post_processing/blur/blur.vert";

    GLuint program = getProgramFromLocal(vertexRoute.c_str(), fragmentRoute.c_str());

    glUseProgram(program);

    GLint texLoc = glGetUniformLocation(program, "screenTexture");
    glUniform1i(texLoc, 0);

    GLint horizontalLoc = glGetUniformLocation(program, "horizontal");

    bool horizontal = true, first_iteration = true;
    for (unsigned int i = 0; i < 10; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[horizontal]);
        glViewport(0, 0, Application::width, Application::height);
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform1i(horizontalLoc, horizontal);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, first_iteration ? texture : textures[!horizontal]);

        // Render quad
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        horizontal = !horizontal;
        if (first_iteration)
            first_iteration = false;
    }

    // Copy result back to screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Application::width, Application::height);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[!horizontal]);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
