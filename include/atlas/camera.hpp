/*
 camera.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Header for the Camera class
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_CAMERA_HPP
#define ATLAS_CAMERA_HPP

#include "atlas/opengl/glm/ext/matrix_float4x4.hpp"
#include "atlas/unit.hpp"
#include "atlas/utilities/utils.hpp"
#include <string>

namespace atlas {

class Camera : public Component {
  public:
    void look_at(Component* component);
    void set_position(Position position);
    Position position;
    Size size;
    int rotation;
    Component* reference = nullptr;
    Camera(std::string name, Position position, Size size, int rotation);
    Camera(std::string name, Position position, Size size, int rotation, Component* reference);
  private:
    glm::mat4 projection;
    glm::mat4 view;
};

} // namespace atlas

#endif // ATLAS_CAMERA_HPP
