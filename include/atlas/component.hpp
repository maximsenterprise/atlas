/*
 component.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Component representation
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_COMPONENT_HPP
#define ATLAS_COMPONENT_HPP

#include "atlas/unit.hpp"
#include <string>
namespace atlas {

class Component {
protected:
    std::string name;
    std::string type;
    Position position;
    Size size;

    Component(std::string name, std::string type, Position position, Size size);
    virtual ~Component() = default;
};

class ComponentRepresentation {
public:
    std::string name;
    std::string type;
    Position position;
    Size size;
    ComponentRepresentation(std::string name, std::string type, Position position, Size size) : name(name), type(type), position(position), size(size) {}
};

}

#endif // ATLAS_COMPONENT_HPP

