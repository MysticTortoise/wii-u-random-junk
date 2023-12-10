#pragma once

#include <vector>

#include "GameObject.hpp"

class GameScene{
    public:
    std::vector<GameObject*> GameObjects; // All of the GameObjects in the scene.

    GameObject* CreateGameobject();

    void Start(); // Called at the beginning of the Scene.
    void Update(); // Called every frame.
    void Draw(); // Called when the game needs to draw content to the screen.
};