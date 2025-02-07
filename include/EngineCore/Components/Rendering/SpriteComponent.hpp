#pragma once

#include "Scene.hpp"
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
        static SpriteComponent* SpriteComponentFromJSON(GameScene* scene, JSON* jsonData);

        ~SpriteComponent();

        alignas(0x100) uint32_t sPositionUniformBlock[8] = {};
        MainRendererComponent* linkedRenderer = nullptr;

        bool visible = true;
        uint8_t alpha = 255;

        void Draw(DRAW_SCREEN_TYPE drawScreenType);


        static GameObjectComponent* CreateFromString(std::string data);
};