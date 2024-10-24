/*
 window.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Window class protocol
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_WINDOW_HPP
#define ATLAS_WINDOW_HPP

#include "atlas/opengl/glew.h"
#include "atlas/opengl/glfw3.h"
#include "atlas/scene.hpp"
#include "atlas/component.hpp"
#include "atlas/utilities/utils.hpp"
#include <atomic>
#include <string>
#include <thread>

namespace atlas {

// Represents a window in the atlas context
class Window : public Component {
public:
    std::string title;
    int width;
    int height;
    bool resizable;
    std::atomic<bool> should_close;
    FunctionQueue function_queue = FunctionQueue();
    FunctionQueue repating_queue = FunctionQueue();
    FunctionQueue transparent_queue = FunctionQueue();
    static FunctionQueue public_function_repeating_queue;
    static float delta_time;
    static float last_frame;

    Window(int width, int height, std::string title, bool resizable = false) : title(title), width(width), height(height), resizable(resizable), Component("Window", "WindowComponent", Position(0, 0, 0), Size(width, height, 0)) {};
    
    void create();
    void destroy();
    void create_console();
    void render_scene(Scene* scene);
    static Window* current;
    GLFWwindow* window;
private:
    std::thread* console_thread;
    bool start_console = false;
    Scene* current_scene = nullptr;
};

}

#endif
