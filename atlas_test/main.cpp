/*
* main.cpp
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Main entry point for atlas testing
* Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/application.h"

int main() {
    Application application(800, 600, "Atlas Test");
    application.setBackend(AtlasBackend::OpenGL);
    application.run();
}
