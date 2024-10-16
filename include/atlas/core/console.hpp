/*
 console.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Console for assisting and editing Atlas applications
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_CONSOLE_HPP
#define ATLAS_CONSOLE_HPP

#include "atlas/unit.hpp"
#include "atlas/window.hpp"
namespace atlas {

void console(Window* window);

class LogEntry {
public:
    std::string message;
    std::string sender;
    int frame = 0;
    Timestamp timestamp;
    LogEntry(std::string message, std::string sender, int frame, Timestamp timestamp) : message(message), frame(frame), timestamp(timestamp), sender(sender) {}
};

class Log {
public:
    static std::vector<LogEntry> entries;
    static void add_entry(std::string message, std::string sender);
};

}

#endif // ATLAS_CONSOLE_HPP
