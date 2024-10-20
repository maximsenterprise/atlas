/*
 camera.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Camera implementation for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/camera.hpp"
#include "atlas/component.hpp"
#include "atlas/core/console.hpp"
#include "atlas/core/exec_error.hpp"
#include "atlas/shape.hpp"
#include "atlas/unit.hpp"
#include "atlas/opengl/glm/gtc/matrix_transform.hpp"
#include "atlas/utilities/utils.hpp"
#include "atlas/window.hpp"
#include <iostream>
#include <string>

namespace atlas {

Camera::Camera(std::string name, Position position, Size size, int rotation) : Component(name, "CameraComponent", position, size), position(position), rotation(rotation), size(size) { 
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) size.width / (float) size.height, 0.1f, 100.0f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(position.x, position.y, position.z),
        glm::vec3(position.x, position.y, position.z - 1),
        glm::vec3(0, 1, 0)
    );

    this->projection = projection;
    this->view = view;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;

    GLuint mvp_id = glGetUniformLocation(0, "MVP");
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);

    representation->component = this;
    ComponentTree::components.push_back(representation);
}

Camera::Camera(std::string name, Position position, Size size, int rotation, Component* reference) : Component(name, "CameraComponent", position, size), position(position), rotation(rotation), size(size), reference(reference) {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) size.width / (float) size.height, 0.1f, 100.0f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(4,3,3), 
        glm::vec3(0, 0, 0), 
        glm::vec3(0, 1, 0)
    );

    this->projection = projection;
    this->view = view;

    glm::mat4 model = glm::mat4(1.0);
    glm::mat4 mvp = projection * view * model;
    
    if (Triangle* triangle = dynamic_cast<Triangle*> (reference)) {
        mvp = glm::translate(mvp, triangle->get_position().get());
        MVPPackage package = MVPPackage();
        package.model = model;
        package.view = view;
        package.projection = projection; 
        package.default_mvp = mvp;
        triangle->set_model(package);
    } else if (Cube* cube = dynamic_cast<Cube*> (reference)) {
        mvp = glm::translate(mvp, cube->get_position().get());
        MVPPackage package = MVPPackage();
        package.model = model;
        package.view = view;
        package.projection = projection; 
        package.default_mvp = mvp;
        cube->set_model(package);
    } else {
        ExecutionError error = ExecutionError("Invalid reference type for camera");
        error.express(); 
    }

    representation->component = this;
    ComponentTree::components.push_back(representation);
    Log::add_entry("Camera " + name + " created successfully", "AtlasEngine:" + name);
}

glm::mat4 MVPPackage::compile() {
    return projection * view * model;
}

}
