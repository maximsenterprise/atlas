/*
 scene.hpp
 As part of the Atlas project
 Created by Maxims Enterprise in 2024
 --------------------------------------------------
 Description: Scene abstraction for the Atlas Engine
 Copyright (c) 2024 Maxims Enterprise
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include "atlas/utilities/utils.hpp"
#include <vector>
namespace atlas {

class Scene {
  public:
    virtual void render() = 0;
    virtual void update() {};
    virtual void setup() = 0;
    virtual void destroy() {};
    void addSetupFunction(std::function<void()> func);
    void executeSetupQueue();
    Scene();

    FunctionQueue setup_queue = {};
};

class SceneScope {
  public:
    static std::vector<Scene *> scenes;
    static void addScene(Scene *scene);
    static void setup_all();
};

} // namespace atlas

#endif // SCENE_HPP
