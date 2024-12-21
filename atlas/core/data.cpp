/*
* data.cpp
* As part of the Atlas project
* Created by Maxims Enterprise in 2024
* --------------------------------------
* Description: Data capabilities and structures for Atlas
* Copyright (c) 2024 Maxims Enterprise
*/

#include <atlas/units.h>

glm::vec3 Size::toVec3() const {
    return {width, height, depth};
}

glm::vec3 Point::toVec3() const {
    return {x, y, z};
}

glm::vec4 Color::toVec4() const {
    return {(float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)alpha / 255.0f};
}
