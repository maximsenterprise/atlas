/*
 texture.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Texture contents for the Atlas Engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/texture.hpp"
#include "atlas/core/exec_error.hpp"
#include "atlas/opengl/glfw3.h"
#include "atlas/opengl/glew.h"
#include "atlas/shape.hpp"
#include <cstdio>

namespace atlas
{

Texture Texture::fromBMP(const char * path) {
    Texture t;

    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    
    // RGB data
    unsigned char *data;

    FILE *file = fopen(path, "rb");
    if (!file) {
        ExecutionError error("Could not open file");
        error.express();
    }

    if (fread(header, 1, 54, file) != 54) {
        ExecutionError error("Not a correct BMP file");
        error.express();
    }
    if (header[0] != 'B' || header[1] != 'M') {
        ExecutionError error("Not a correct BMP file");
        error.express();
    }

    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;

    data = new unsigned char [imageSize];
    fread(data, 1, imageSize, file);
    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 


    delete[] data;

    t.representation = textureID;
    return t;
}

}
