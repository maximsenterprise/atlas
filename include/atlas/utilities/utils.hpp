/*
 utils.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: General utilities for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <functional>
#include <queue>
#include <string>
#include <vector>
namespace atlas {

class FunctionQueue {
public:
    std::queue<std::function<void()>> general_queue = std::queue<std::function<void()>>();
    void push(std::function<void()> func);
    void execute_all();
};

class Component {
public:
    std::string name;
    std::string type;

    Component(std::string name, std::string type) : name(name), type(type) {};
};

class ComponentTree {
public:
    static std::vector<Component> components;
};

std::string trim(const std::string& str);

};

#endif // UTILS_HPP
