/*
 utils.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: General utilities implementation for the Atlas Engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/utilities/utils.hpp"
#include "atlas/component.hpp"
#include "atlas/opengl/glm/ext/matrix_float3x3.hpp"
#include "atlas/opengl/glm/ext/vector_float3.hpp"
#include "atlas/opengl/glm/ext/vector_float4.hpp"
#include "atlas/unit.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace atlas {

void FunctionQueue::push(std::function<void()> func) {
    general_queue.push(func);
}

void FunctionQueue::execute_all() {
    while (!general_queue.empty()) {
        general_queue.front()();
        general_queue.pop();
    }
}

void FunctionQueue::clear() {
    while (!general_queue.empty()) {
        general_queue.pop();
    }
}

void FunctionQueue::execute() {
    if (!general_queue.empty()) {
        general_queue.front()();
    }
}

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

glm::vec3 Position::get() { return glm::vec3(x, y, z); }

glm::vec3 Size::get() { return glm::vec3(width, height, depth); }

void Position::out() {
    std::cout << "Position: " << x << ", " << y << ", " << z << std::endl;
}

Component::Component(std::string name, std::string type, Position position,
                     Size size)
    : name(name), type(type), position(position), size(size) {
    representation = new ComponentRepresentation();
    representation->name = name;
    representation->type = type;
}

std::vector<std::string> split(const std::string &str,
                               const std::string &delimiter) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delimiter, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delimiter.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

void printMatrix(const glm::mat4 &matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

glm::vec4 Color::get() {
    return glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); 
}

Color Color::with_alpha(int alpha) {
    return Color(r, g, b, alpha);
}

const Color AtlasPalette::white = Color(255, 255, 255, 255);
const Color AtlasPalette::black = Color(0, 0, 0, 255);
const Color AtlasPalette::red = Color(255, 0, 0, 255);
const Color AtlasPalette::green = Color(0, 255, 0, 255);
const Color AtlasPalette::blue = Color(0, 0, 255, 255);
const Color AtlasPalette::yellow = Color(255, 255, 0, 255);
const Color AtlasPalette::cyan = Color(0, 255, 255, 255);
const Color AtlasPalette::magenta = Color(255, 0, 255, 255);
const Color AtlasPalette::orange = Color(255, 165, 0, 255);
const Color AtlasPalette::purple = Color(128, 0, 128, 255);
const Color AtlasPalette::pink = Color(255, 192, 203, 255);
const Color AtlasPalette::brown = Color(165, 42, 42, 255);
const Color AtlasPalette::grey = Color(128, 128, 128, 255);

} // namespace atlas
