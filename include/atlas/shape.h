/*
* shape.h
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Atlas shape headers
* Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_SHAPE_H
#define ATLAS_SHAPE_H
#include "graphics.h"
#include "units.h"
#include <string>

#include "core/core_rendering.h"

class Triangle : public Component {
public:
    Color color;
    Size size;
    Position position;
    Shader shader;
    std::vector<CoreVertex> vertices;

    Triangle(std::string name, Color color, Size size, Position position, Shader shader = Shader(AtlasShader::Default));
    void setShader(Shader shader);
    void setColorOfPoint(Color color, int point);
    void useVertexSet(std::array<CoreVertex, 3> vertices);
    void render();
};

#endif //ATLAS_SHAPE_H
