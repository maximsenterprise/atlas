/*
 window.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Window class protocol
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "atlas/opengl/glew.h"
#include "atlas/opengl/glfw3.h"
#include "atlas/utilities/utils.hpp"
#include <atomic>
#include <string>
#include <thread>

namespace atlas {

// Represents a window in the atlas context
class Window {
public:
    std::string title;
    int width;
    int height;
    bool resizable;
    std::atomic<bool> should_close;
    FunctionQueue function_queue;

    Window(int width, int height, std::string title, bool resizable = false) : title(title), width(width), height(height), resizable(resizable) {};
    
    void create();
    void destroy();
    void create_console();
private:
    GLFWwindow* window;
    std::thread* console_thread;
    bool start_console = false;
};

}

#endif
