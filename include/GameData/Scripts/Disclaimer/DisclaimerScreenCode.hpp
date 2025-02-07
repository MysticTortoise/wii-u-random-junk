#pragma once

#include "GameObject.hpp"

#include "SpriteComponent.hpp"


class DisclaimerScreenScript : public GameObjectComponent{
    int alphaProgress = 0;
    int progress = 0;
    int waitTimer = 0;
    const int progressSpeed = 2;

    SpriteComponent* sprite;

    public:
    DisclaimerScreenScript();

    void Start();
    void Update();
};