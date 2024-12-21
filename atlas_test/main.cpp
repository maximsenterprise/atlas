/*
* main.cpp
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Main entry point for atlas testing
* Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/application.h"
#include "atlas/shape.h"

int main() {
    Application application(800, 600, "Atlas Test");
    application.setBackend(AtlasBackend::OpenGL);

    PostProcessUnit unit(AtlasPostProcessing::Blur);
    application.applyPostProcess(unit);

    Triangle triangle("Triangle", Color(255, 0, 0), Size(2, 2), Position(-1, -1));
    triangle.render();

    application.run();
}
