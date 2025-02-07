#pragma once

#include <vector>
#include <string>

#include "EngineCoreBaseDefines.hpp"
#include "GameObject.hpp"

class GameScene{
    public:
    std::vector<GameObject*> GameObjects = {}; // All of the GameObjects in the scene.
    uint32_t SceneTick = 0;

    GameScene();
    GameScene(std::vector<GameObject*> objects);

    GameObject* CreateGameobject();
    GameObject* FindGameobjectByName(std::string name);

    void Start(); // Called at the beginning of the Scene.
    void Update(); // Called every frame.
    void Draw(); // Called when the game needs to draw content to the screen.
    void Exit(); // Called when scene is about to exit.

    ~GameScene();

    static void LoadFromAssetFile(std::string assetPath);
};