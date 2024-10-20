/*
 texture.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Texture headers for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_TEXTURE_HPP
#define ATLAS_TEXTURE_HPP

#include "atlas/opengl/glew.h"

namespace atlas
{

class Texture {
public:
    static Texture fromBMP(const char * path);
    static Texture fromPNG(const char * path);
    static Texture fromDDS(const char * path);
    GLuint representation;
};

}



#endif // ATLAS_TEXTURE_HPP
