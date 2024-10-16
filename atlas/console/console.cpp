/*
 console.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Console implementation for the Atlas engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/core/console.hpp"
#include "atlas/component.hpp"
#include "atlas/core/exec_error.hpp"
#include "atlas/shape.hpp"
#include "atlas/utilities/style.hpp"
#include "atlas/utilities/utils.hpp"

#include <cstdlib>
#include <cxxabi.h>
#include <iostream>
#include <string>
#include <vector>

void atlas::console(Window *window) {
    Log::add_entry("Console started", "AtlasEngine");
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
            for (ComponentRepresentation *component :
                 ComponentTree::components) {
                std::cout << component->type << " <- " << component->name
                          << std::endl;
            }
        } else if (command.starts_with("comp")) {
            std::string name = command.substr(5, command.length());
            std::cout << "Components for " << name << ":" << std::endl;
            for (ComponentRepresentation *component :
                 ComponentTree::components) {
                if (component->name == trim(name)) {
                    std::cout << component->type << " <- " << component->name
                              << std::endl;
                }
            }
        } else if (command == "log") {
            for (LogEntry entry : Log::entries) {
                 std::cout << ITALIC << GREEN << entry.sender << RESET << GREEN << "<" << entry.frame << "> at " << entry.timestamp.hour << ":" << entry.timestamp.minute << ":" << entry.timestamp.second << " -> " << entry.message << RESET << std::endl;  
            } 
        } else if (command.starts_with("[")) {
            std::vector<std::string> parts = split(command, " ");
            if (parts.size() != 3) {
                atlas::ExecutionError error(
                    "Invalid syntax for component methods");
                error.express();
                continue;
            }
            atlas::Component *component;
            std::string name = parts[0].substr(1, parts[0].length() - 2);
            for (ComponentRepresentation *comp : ComponentTree::components) {
                if (comp->name == name) {
                    component = comp->component;
                    break;
                }
            }

            if (!component) {
                atlas::ExecutionError error("Component not found");
                error.express();
                continue;
            }

            if (Triangle *triangle = dynamic_cast<Triangle *>(component)) {
                if (parts[1] == "updatex") {
                    Position current_position = triangle->get_position();
                    current_position.x = std::stoi(parts[2]);
                    window->function_queue.push([triangle, current_position] {
                        triangle->update_position(current_position);
                    });
                } else if (parts[1] == "updatey") {
                    Position current_position = triangle->get_position();
                    current_position.y = std::stoi(parts[2]);
                    window->function_queue.push([triangle, current_position] {
                        triangle->update_position(current_position);
                    });
                } else if (parts[1] == "updatez") {
                    Position current_position = triangle->get_position();
                    current_position.z = std::stoi(parts[2]);
                    window->function_queue.push([triangle, current_position] {
                        triangle->update_position(current_position);
                    });
                } else {
                    atlas::ExecutionError error("Method not recognized");
                    error.express();
                }
            } else {
                atlas::ExecutionError error(
                    "Invalid component type. Cannot be edited");
                error.express();
            }
        } else if (command == "") {
            continue;
        } else {
            atlas::ExecutionError error("Command not recognized");
            error.express();
        }
    }
}

void atlas::Log::add_entry(std::string message, std::string sender) {
    LogEntry entry(message, sender, 0, Timestamp(2024, 1, 1, 0, 0, 0));
    entries.push_back(entry);
}

std::vector<atlas::LogEntry> atlas::Log::entries = {};
