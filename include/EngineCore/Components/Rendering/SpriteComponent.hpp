#pragma once

#include "GameObject.hpp"
#include "datatypes.hpp"

#include "MainRendererComponent.hpp"

#include <string>

class SpriteComponent : public GameObjectComponent{
    public:
        GX2Texture* texture = nullptr;
        GX2Sampler* sampler = nullptr;
        
        SpriteComponent(std::string imageFilePath);
        SpriteComponent(GX2Texture texture);

        alignas(0x100) uint32_t sPositionUniformBlock[8] = {};

        MainRendererComponent* linkedRenderer = nullptr;

        void Draw(DRAW_SCREEN_TYPE drawScreenType);
};