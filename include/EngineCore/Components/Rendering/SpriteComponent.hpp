#pragma once

#include "GameObject.hpp"
#include "datatypes.hpp"

#include "MainRendererComponent.hpp"

#include <string>

class SpriteComponent : public GameObjectComponent{
    public:
        GX2Texture* texture;
        GX2Sampler* sampler;
        
        SpriteComponent(std::string imageFilePath);
        SpriteComponent(GX2Texture texture);

        alignas(0x100) uint32_t sPositionUniformBlock[8] = {};

        MainRendererComponent* linkedRenderer;

        void Draw(DRAW_SCREEN_TYPE drawScreenType);
};