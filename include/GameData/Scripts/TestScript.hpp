#pragma once

#include "GameObject.hpp"

#include "GamepadInputGrabber.hpp"
#include "SpriteComponent.hpp"


class TestScript : public GameObjectComponent{
    public:
    SpriteComponent* sprite = nullptr;
    GamePadInputGrabberComponent* gamepad = nullptr;
    void Update();
};