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

#endif //ATLAS_GRAPHICS_H
