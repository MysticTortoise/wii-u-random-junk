#pragma once
#include <string>

#include "Scene.hpp"

class GameStateManager{
    public:
    static GameScene* currentScene;

    static void ChangeScene(GameScene* scene);
    static void EndCurrentSceneScene();

    static void LoadSceneFromFile(std::string scenePath);
};

