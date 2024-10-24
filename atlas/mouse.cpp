/*
 mouse.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Mouse logic for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/mouse.hpp"
#include "atlas/event.hpp"
#include "atlas/unit.hpp"
#include "atlas/window.hpp"
#include <functional>

namespace atlas
{

bool Mouse::is_cursor_locked = false;
Position Mouse::cursor_position_global = Position(0, 0, 0);

void Mouse::compute()
{
    if (is_cursor_locked) {
        set_cursor_position(Position(Window::current->width / 2.0f, Window::current->height / 2.0f));
    }
}

void Mouse::set_cursor_position(Position position) {
    glfwSetCursorPos(Window::current->window, position.x, position.y);
}

void Mouse::lock_cursor() { 
    is_cursor_locked = true;
}

void Mouse::free_cursor() {
    is_cursor_locked = false;
}

void Mouse::hide_cursor() {
    glfwSetInputMode(Window::current->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Mouse::show_cursor() {
    glfwSetInputMode(Window::current->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Position Mouse::get_cursor_position() {
    double x, y;
    glfwGetCursorPos(Window::current->window, &x, &y);
    return Position(x, y, 0);
}

void Mouse::onMove(std::function<void()> callback) {
    move_event.add(callback);
}

void Mouse::cursor_move_fallback(GLFWwindow * window, double x, double y) {
    cursor_position_global = Position(x, y, 0);
    move_event.trigger();
}

Event Mouse::move_event;
Event Mouse::right_button_event;
Event Mouse::left_button_event;
Event Mouse::middle_button_event;

void Mouse::onRightButtonClicked(std::function<void()> callback) {
    right_button_event.add(callback);
}

void Mouse::onLeftButtonClicked(std::function<void()> callback) {
    left_button_event.add(callback);
}

void Mouse::onMiddleButtonClicked(std::function<void()> callback) {
    middle_button_event.add(callback);
}

void Mouse::cursor_button_fallback(GLFWwindow * window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        right_button_event.trigger();
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        left_button_event.trigger();
    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        middle_button_event.trigger();
    }
}

Event Mouse::scroll_event;
Mouse::ScrollOffset Mouse::scroll_offset = Position(0, 0, 0);

void Mouse::onScroll(std::function<void()> callback) {
    return scroll_event.add(callback);
}

void Mouse::cursor_scroll_fallback(GLFWwindow * window, double xoffset, double yoffset) {
    scroll_offset = Position(xoffset, yoffset, 0);
    scroll_event.trigger();
}

}
