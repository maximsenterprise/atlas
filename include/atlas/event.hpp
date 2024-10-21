/*
 event.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Event queues for Atlas
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef ATLAS_EVENT_HPP
#define ATLAS_EVENT_HPP

#include <atomic>
#include <functional>
#include <thread>
namespace atlas
{

class Event {
public:
    using Callback = std::function<void()>;

    void add(Callback callback);
    void remove(Callback callback);
    void trigger();

private:
    std::vector<Callback> callbacks;
};

class PredicateEvent {
public:
    PredicateEvent(std::function<bool()> conditionFunction, Event event);
    ~PredicateEvent();
    
    void addToUpdate(Event::Callback callback); 
private:
    Event event;
    std::thread eventThread;
    std::atomic<bool> running = true;
    std::function<bool()> coniditionFunction;

    void run();
};

}

#endif // ATLAS_EVENT_HPP
