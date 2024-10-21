/*
 event.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Events for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/event.hpp"
#include <iostream>

namespace atlas {

void Event::add(Callback callback) {
    callbacks.push_back(callback);
}

void Event::trigger() {
    for (auto &callback : callbacks) {
        callback();
    }
}

PredicateEvent::PredicateEvent(std::function<bool()> conditionFunction, Event event) : coniditionFunction(conditionFunction), running(true) {
    this->event = event;
    eventThread = std::thread(&PredicateEvent::run, this); 
}

PredicateEvent::~PredicateEvent() {
    running = false;
    if (eventThread.joinable()) {
        eventThread.join();
    }
}

void PredicateEvent::addToUpdate(Event::Callback callback) {
    event.add(callback);
}

void PredicateEvent::run() {
    while (true) {
        if (coniditionFunction()) {
            event.trigger();
            break; 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}
}
