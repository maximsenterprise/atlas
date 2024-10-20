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

#define STB_IMAGE_IMPLEMENTATION
#include "atlas/opengl/stb_image.h"

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
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glGenerateMipmap(GL_TEXTURE_2D);

    t.representation = textureID;
    return t;
}

Texture Texture::fromPNG(const char * path) {
    Texture t;
    
    int with, height, channels;

    unsigned char *data = stbi_load(path, &with, &height, &channels, 0);
    if (!data) {
        ExecutionError error("Could not load image");
        error.express();
    }

    GLuint textureID;
    glGenTextures(1, &textureID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, with, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, with, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        stbi_image_free(data);
        ExecutionError error("Unsupported number of channels");
        error.express();
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    t.representation = textureID;

    return t;
}

Texture Texture::fromDDS(const char *path) {
    Texture t;

    unsigned char header[124];

    FILE *fp;

    fp = fopen(path, "rb");
    if (fp == NULL) {
        ExecutionError error("Could not open file");
        error.express();
    }

    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        ExecutionError error("Not a DDS file");
        error.express();
    }

    fread(&header, 124, 1, fp);

    unsigned int height = *(unsigned int*)&(header[8]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);
    
    unsigned char *buffer;
    unsigned int bufsize;

    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    fclose(fp);
    
    unsigned int components = (fourCC == 0x31545844) ? 3 : 4; 
    unsigned int format; 
    switch (fourCC) {
    case 0x31545844:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case 0x33545844:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case 0x35545844:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        ExecutionError error("Unsupported DDS format");
        error.express();
    }

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;
    }
    free(buffer);

    t.representation = textureID; 
    return t;
}

}
