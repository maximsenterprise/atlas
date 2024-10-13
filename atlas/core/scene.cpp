/*
 scene.cpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Scene logic for the Atlas Engine
 Copyright (c) 2024 Maxims Enterprise
*/

#include "atlas/scene.hpp"
#include <iostream>

namespace atlas {
std::vector<Scene *> SceneScope::scenes = {};

Scene::Scene() { 
    SceneScope::addScene(this);
}

void SceneScope::addScene(Scene *scene) {  
    scenes.push_back(scene);
}

void SceneScope::setup_all() {
    for (auto scene : scenes) {
        scene->setup();
    }
}

void Scene::addSetupFunction(std::function<void()> func) {
    setup_queue.push(func);
}

void Scene::executeSetupQueue() { setup_queue.execute_all(); }

} // namespace atlas
