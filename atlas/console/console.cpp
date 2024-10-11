/*
 console.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Console implementation for the Atlas engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/core/console.hpp"
#include "atlas/core/exec_error.hpp"
#include "atlas/utilities/utils.hpp"

#include <cstdlib>
#include <iostream>

void atlas::console(Window* window) {
    std::string command;
    while (true) {
        std::cout << "AtlasEngine console: ";
        std::getline(std::cin, command);
        if (command == "exit" || command == "quit" || command == "end") {
            window->should_close = true; 
            std::exit(0);
            break;
        } else if (command == "clear" || command == "cls") {
            system("clear");  
        } else if (command == "tree") {
            for (Component component : ComponentTree::components) {
                std::cout << component.type << " <- " << component.name << std::endl;
            }
        } else if (command.starts_with("comp")) {
            std::string name = command.substr(5, command.length());
            std::cout << "Components for " << name << ":" << std::endl;
            for (Component component : ComponentTree::components) {
                if (component.name == trim(name)) {
                    std::cout << component.type << " <- " << component.name << std::endl;
                }
            }
        } else if (command == "") {
            continue;
        } else {
            atlas::ExecutionError error("Command not recognized");
            error.express();
        }
    }
}
