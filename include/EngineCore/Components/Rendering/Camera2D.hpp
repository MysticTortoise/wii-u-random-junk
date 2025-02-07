#pragma once

#include "GameObject.hpp"
#include "datatypes.hpp"

class Camera2DComponent : public GameObjectComponent{
    public:
    Color bgColor;

    Camera2DComponent();
    Camera2DComponent(JSON* jsonData);
};