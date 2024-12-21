/*
* application.cpp
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Main application class for atlas
* Copyright (c) 2024 Maxims Enterprise
*/

#include <iostream>
#include <atlas/application.h>
#include <SDL2/SDL.h>

#include "atlas/core/core_rendering.h"
#include <GL/glew.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

FunctionQueue<void> Application::renderFunctions = FunctionQueue<void>();
FunctionQueue<void> Application::postProcessFunctions = FunctionQueue<void>();
RenderInstance Application::instance = RenderInstance();
int Application::width = 0;
int Application::height = 0;

Application::Application(int width, int height, std::string title) : title(title) {
    Application::width = width;
    Application::height = height;
}

AtlasBackend Application::getBackend() const {
    return m_backend;
}

void Application::setBackend(AtlasBackend backend) {
    this->m_backend = backend;
    switch (backend) {
    case AtlasBackend::OpenGL:
        initOpenGL();
        break;
    default:
        std::cout << "Cannot set backend to None or unknown value" << std::endl;
    }
}


void Application::run() {
    mainLoop();
}

void Application::initOpenGL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    if (SDL_GL_MakeCurrent(window, context) < 0) {
        std::cerr << "Failed to make OpenGL context current: " << SDL_GetError() << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_GL_SetSwapInterval(1);

    instance.createFramebuffer(width, height);
}

void Application::mainLoop() {
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        renderFunctions.run();

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::applyPostProcess(PostProcessUnit unit) {
    instance.postProcessUnit = unit;
    if (unit.isLocal && unit.type == AtlasPostProcessing::Blur) {
        instance.createPongBuffers(width, height);
    }
}



