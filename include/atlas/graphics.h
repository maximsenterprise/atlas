/*
* graphics.h
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Graphics function definition
* Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_GRAPHICS_H
#define ATLAS_GRAPHICS_H

#include <string>

enum class AtlasShader {
    Default,
};

struct Shader {
    bool isLocal;
    const char* vertexShader;
    const char* fragmentShader;
    AtlasShader type;

    explicit Shader(AtlasShader type) : type(type), isLocal(false), vertexShader(nullptr), fragmentShader(nullptr) {
    }

    Shader(const char* vertexShader, const char* fragmentShader) : type(AtlasShader::Default), isLocal(true),
                                                                   vertexShader(vertexShader),
                                                                   fragmentShader(fragmentShader) {
    }
};

enum class AtlasPostProcessing {
    None,
    Blur,
    InvertAllColors,
};

struct PostProcessUnit {
    bool isLocal;
    const char* vertexShader;
    const char* fragmentShader;
    AtlasPostProcessing type;

    explicit PostProcessUnit(AtlasPostProcessing type) : type(type), isLocal(false), vertexShader(nullptr),
                                                         fragmentShader(nullptr) {
    }

    PostProcessUnit(const char* vertexShader, const char* fragmentShader) : type(AtlasPostProcessing::None),
                                                                            isLocal(true),
                                                                            vertexShader(vertexShader),
                                                                            fragmentShader(fragmentShader) {
    }
};

class Component {
public:
    std::string name;

    explicit Component(std::string name) : name(std::move(name)) {
    }
};

#endif //ATLAS_GRAPHICS_H
