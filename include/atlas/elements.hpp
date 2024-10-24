/*
 elements.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Altas Elements
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_ELEMENTS_HPP
#define ATLAS_ELEMENTS_HPP

#include "atlas/camera.hpp"
#include "atlas/component.hpp"

namespace atlas
{

class Element {};

class FirstPersonCamera : public Element
{
public:
    void apply_to(Camera* camera);
    bool first_mouse = true;
    float yaw = -90.f;
    float pitch;
    float lastX, lastY;
    float X, Y;
    static float horizontalAngle;
    static float verticalAngle;
};

}

#endif // ATLAS_ELEMENTS_HPP
