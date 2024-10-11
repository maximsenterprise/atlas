/*
 window.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Window logic for the Atlas engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/window.hpp"
#include "atlas/core/exec_error.hpp"
#include "atlas/opengl/glew.h"
#include "atlas/opengl/glfw3.h"
#include "atlas/core/console.hpp"
#include "atlas/utilities/utils.hpp"
#include <string>
#include <thread>
#include <vector>

std::vector<atlas::Component> atlas::ComponentTree::components = {};

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void atlas::Window::create_console() {
    start_console = true;
}

void atlas::Window::create() {
    this->should_close = false;
    if (!glfwInit()) {
        ExecutionError error("Failed to initialize GLFW", true);
        error.express();
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, this->resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        ExecutionError error("Failed to create GLFW window", true);
        error.express();
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        ExecutionError error("Failed to initialize GLEW", true);
        error.express();
        return;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
    
    ComponentTree::components.push_back(Component("WindowComponent", title)); 

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window); 

        this->function_queue.execute_all(); 

        if (should_close) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            destroy();
        }
        glfwPollEvents();

        if (start_console) {
            std::thread console_thread(console, this); 
            this->console_thread = &console_thread;
            console_thread.detach();
            start_console = false;
        } 
    }
}

void atlas::Window::destroy() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}
