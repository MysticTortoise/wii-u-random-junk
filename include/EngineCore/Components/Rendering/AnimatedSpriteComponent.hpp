#pragma once

#include <vector>
#include <map>
#include <string>

#include "GameObject.hpp"
#include "SpriteComponent.hpp"

struct SpriteAnimation{
    std::vector<GX2Texture*> frames;
    float speed = 1;
    std::string name;
};

class AnimatedSpriteComponent : public GameObjectComponent{
    private:
        GX2Texture* texture = nullptr;
        float framesSinceLastFrameChange = 0;
    public:
        GX2Sampler* sampler = nullptr;

        alignas(0x100) uint32_t sPositionUniformBlock[8] = {};
        MainRendererComponent* linkedRenderer = nullptr;


        std::map<std::string,SpriteAnimation> animations = {};
        unsigned int frame = 0;
        SpriteAnimation* currentAnimation = nullptr;

        bool visible = true;
        uint8_t alpha = 255;


        AnimatedSpriteComponent();
        SpriteAnimation* AddAnimation(const std::vector<std::string> frames, std::string name, float speed);
        ~AnimatedSpriteComponent();

        static AnimatedSpriteComponent* AnimatedSpriteComponentFromJSON(GameScene* scene, JSON* jsonData);

        SpriteAnimation* SetAnimation(std::string name);

        void Draw(DRAW_SCREEN_TYPE drawScreenType);
};