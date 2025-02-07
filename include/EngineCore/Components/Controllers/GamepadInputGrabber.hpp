#pragma once

#include "GameObject.hpp"
#include "GameInput.hpp"

class GamePadInputGrabberComponent : public GameObjectComponent{
    public:
    Input::WiiUGamepad* gamepad = nullptr;
    GamePadInputGrabberComponent();
    ~GamePadInputGrabberComponent();
    void Update();
};