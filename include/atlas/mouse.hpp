/*
 mouse.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Mouse utilities for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_MOUSE_HPP
#define ATLAS_MOUSE_HPP

#include "atlas/event.hpp"
#include "atlas/opengl/glew.h"
#include "atlas/opengl/glfw3.h"
#include "atlas/unit.hpp"
namespace atlas
{

class Mouse
{
public:
    static void onMove(std::function<void()> callback);
    static void onRightButtonClicked(std::function<void()> callback);
    static void onLeftButtonClicked(std::function<void()> callback);
    static void onMiddleButtonClicked(std::function<void()> callback); 
    static void onScroll(std::function<void()> callback);
    static void compute();
    static void set_cursor_position(Position position);
    static void lock_cursor();
    static void free_cursor();
    static void hide_cursor(); 
    static void show_cursor();
    static Position get_cursor_position();
    static bool is_cursor_locked;
    static void cursor_move_fallback(GLFWwindow * window, double x, double y);
    static void cursor_button_fallback(GLFWwindow * window, int button, int action, int mods);
    static void cursor_scroll_fallback(GLFWwindow * window, double xoffset, double yoffset);
    static Event move_event;
    static Event right_button_event;
    static Event left_button_event;
    static Event middle_button_event;
    static Event scroll_event;

    using ScrollOffset = Position; 
    static ScrollOffset get_scroll_offset();
    static ScrollOffset scroll_offset;
};

}

#endif // ATLAS_MOUSE_HPP
