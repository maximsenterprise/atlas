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

struct MVPPackage {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 default_mvp;
    glm::mat4 compile();
};

class Camera : public Component {
  public:
    void look_at(Component* component);
    void set_position(Position position);
    Position position;
    int rotation;
    float fov;
    Component* reference = nullptr;
    Camera(std::string name, Position position, float fov, Size size, int rotation);
    Camera(std::string name, Position position, float fov, Size size, int rotation, Component* reference);
    MVPPackage package;
    Size size;
  private:
    glm::mat4 projection; 
    glm::mat4 view;
};

} // namespace atlas

#endif // ATLAS_CAMERA_HPP
