/*
 window.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Window logic for the Atlas engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/window.hpp"
#include "atlas/component.hpp"
#include "atlas/core/console.hpp"
#include "atlas/core/exec_error.hpp"
#include "atlas/opengl/glew.h"
#include "atlas/opengl/glfw3.h"
#include "atlas/scene.hpp"
#include "atlas/utilities/utils.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <vector>

std::vector<atlas::ComponentRepresentation*> atlas::ComponentTree::components = {};

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void atlas::Window::create_console() { start_console = true; }

void atlas::Window::render_scene(Scene *scene) {
    Log::add_entry("Begin rendering scene", "AtlasEngine:WindowComponent");
    this->repating_queue.clear();
    this->current_scene = scene;
    current_scene->setup_queue.push([this] { this->current_scene->setup(); });

    this->function_queue.push([this] { this->current_scene->render(); });
    this->repating_queue.push([this] { this->current_scene->update(); });
}

void atlas::Window::create() {
    this->should_close = false;
    representation->component = this;
    ComponentTree::components.push_back(representation);

    if (!glfwInit()) {
        ExecutionError error("Failed to initialize GLFW", true);
        error.express();
        return;
    }

    if (this->current_scene == nullptr) {
        ExecutionError error("No scene to render", true);
        error.express();
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, this->resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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

    current_scene->executeSetupQueue();

    glClearColor(0.2f, 0.3f, 0.3f, 0.1f); 
    Log::add_entry("Window Created Successfully", "AtlasEngine:WindowComponent");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->function_queue.execute_all();
        this->repating_queue.execute();

        if (should_close) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            destroy();
        }
        glfwSwapBuffers(window);

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
    Log::add_entry("Window destroyed", "AtlasEngine:WindowComponent");
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}
