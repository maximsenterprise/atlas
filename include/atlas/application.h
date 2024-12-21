/*
* application.h
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Application class for atlas
* Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_APPLICATION_H
#define ATLAS_APPLICATION_H

#include <SDL2/SDL.h>
#include <string>

#include "data.hpp"
#include "core/core_rendering.h"

enum class AtlasBackend {
    OpenGL,
    None,
};

class Application {
public:
    void run();
    void setBackend(AtlasBackend backend);
    void mainLoop();
    void applyPostProcess(PostProcessUnit unit);
    AtlasBackend getBackend() const;
    static int width, height;
    std::string title;

    Application(int width, int height, std::string title);

    static FunctionQueue<void> renderFunctions;
    static FunctionQueue<void> postProcessFunctions;
    static RenderInstance instance;

private:
    SDL_Window* window = nullptr;
    AtlasBackend m_backend = AtlasBackend::None;
    void initOpenGL();
};

#endif //ATLAS_APPLICATION_H
