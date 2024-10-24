/*
 controllers.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Controllers for Games
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/core/exec_error.hpp"
#include "atlas/elements.hpp"
#include "atlas/mouse.hpp"
#include "atlas/opengl/glfw3.h"
#include "atlas/opengl/glm/ext/matrix_clip_space.hpp"
#include "atlas/opengl/glm/ext/matrix_transform.hpp"
#include "atlas/opengl/glm/ext/vector_float3.hpp"
#include "atlas/opengl/glm/geometric.hpp"
#include "atlas/opengl/glm/trigonometric.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "atlas/opengl/glm/gtx/string_cast.hpp"
#include "atlas/shape.hpp"
#include "atlas/utilities/utils.hpp"
#include "atlas/window.hpp"
#include <iostream>

namespace atlas {

float FirstPersonCamera::horizontalAngle = 3.14f;
float FirstPersonCamera::verticalAngle = 0.0f;

void FirstPersonCamera::apply_to(Camera *camera) {
    Window::public_function_repeating_queue.push([this, camera] {
        glm::vec3 pos = camera->position.get(); 
        float initialFoV = camera->fov;
        float speed = 3.0f;
        float mouseSpeed = 0.03f; 

        double xpos, ypos;
        glfwGetCursorPos(Window::current->window, &xpos, &ypos);  
        horizontalAngle += mouseSpeed * Window::delta_time * float(Window::current->width / 2.0f - xpos);
        verticalAngle += mouseSpeed * Window::delta_time * float(Window::current->height / 2.0f - ypos);

        if (verticalAngle > 1.5f) verticalAngle = 1.5f;
        if (verticalAngle < -1.5f) verticalAngle = -1.5f; 

        glm::vec3 direction(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
        );

        glm::vec3 right = glm::vec3(
            sin(horizontalAngle - 3.14f/2.0f),
            0,
            cos(horizontalAngle - 3.14f/2.0f)
        );

        if (glfwGetKey(Window::current->window, GLFW_KEY_W) == GLFW_PRESS) {
            pos += direction * Window::delta_time * speed;  
            camera->position = Position(pos);
        }

        if (glfwGetKey(Window::current->window, GLFW_KEY_S) == GLFW_PRESS) {
            pos -= direction * Window::delta_time * speed;
            camera->position = Position(pos);
        }

        if (glfwGetKey(Window::current->window, GLFW_KEY_D) == GLFW_PRESS) {
            pos += right * Window::delta_time * speed;
            camera->position = Position(pos);
        }

        if (glfwGetKey(Window::current->window, GLFW_KEY_A) == GLFW_PRESS) {
            pos -= right * Window::delta_time * speed;
            camera->position = Position(pos);
        }

        if (glfwGetKey(Window::current->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            pos.y += Window::delta_time * speed;
            camera->position = Position(pos);
        }

        if (glfwGetKey(Window::current->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            pos.y -= Window::delta_time * speed;
            camera->position = Position(pos);
        }

        glm::vec3 up = glm::cross(right, direction);

        camera->fov = initialFoV - 5 * Mouse::scroll_offset.y;
        if (camera->fov < 1.0f) camera->fov = 1.0f;
        if (camera->fov > 45.0f) camera->fov = 45.0f;
        
        glm::mat4 projection = glm::perspective(glm::radians(camera->fov), (float) camera->size.width / (float) camera->size.height, 0.1f, 100.0f); 
        glm::mat4 view = glm::lookAt(
            pos,
            pos + direction,
            up
        );

        camera->package.projection = projection; 
        camera->package.view = view;
        camera->package.default_mvp = camera->package.projection * camera->package.view * camera->package.model;

        if (Cube* cube = dynamic_cast<Cube*>(camera->reference)) {
            camera->package.default_mvp = glm::translate(camera->package.default_mvp, cube->get_position().get());
            cube->set_model(camera->package);
        }
    });
}

} // namespace atlas
