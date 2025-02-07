#include "AnimatedSpriteComponent.hpp"

#include <fstream>

#include "gx2/mem.h"
#include "gx2/draw.h"

#include "TGAImport.hpp"

#include "TransformComponent.hpp"
#include "HelperStandard.hpp"

AnimatedSpriteComponent::AnimatedSpriteComponent(){
    sampler = new GX2Sampler();\
    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_LINEAR);
}

AnimatedSpriteComponent* AnimatedSpriteComponent::AnimatedSpriteComponentFromJSON(GameScene* scene, JSON* jsonData){
    AnimatedSpriteComponent* sprite = new AnimatedSpriteComponent();
    sprite->linkedRenderer = scene->FindGameobjectByName(jsonData->operator[]("LinkedRenderer"))->GetComponent<MainRendererComponent>();
    if(jsonData->contains("Alpha"))
        sprite->alpha = jsonData->operator[]("Alpha");


    std::vector<JSON> anims = jsonData->operator[]("Animations");
    for(JSON anim : anims){
        sprite->AddAnimation(anim["Frames"],anim["Name"],anim["Speed"]);
        if(sprite->currentAnimation == nullptr)
            sprite->SetAnimation(anim["Name"]);
    }

    return sprite;
}

AnimatedSpriteComponent::~AnimatedSpriteComponent(){
    for(auto const& [animName, anim] : animations){
        for(GX2Texture* texture : anim.frames){
            delete texture;
        }
    }
    delete sampler;
}

SpriteAnimation* AnimatedSpriteComponent::AddAnimation(const std::vector<std::string> frames, std::string name, float speed){
    SpriteAnimation anim;

    for(std::string framePath : frames){ // Add Textures
        std::ifstream fs("romfs:/" + framePath, std::ios::in | std::ios::binary);
        std::vector<uint8_t> data((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
        texture = TGA_LoadTexture((uint8_t *)data.data(), data.size());

        anim.frames.push_back(texture);
    }

    anim.speed = speed;
    anim.name = name;

    animations.insert({name,anim});
    return &animations[name];
}

SpriteAnimation* AnimatedSpriteComponent::SetAnimation(std::string name){
    if(animations.find(name) == animations.end()){
        return nullptr;
    }
    currentAnimation = &animations[name];
    return currentAnimation;
}


void AnimatedSpriteComponent::Draw(DRAW_SCREEN_TYPE drawScreenType){
    if(drawScreenType != linkedRenderer->drawScreenType) {return;}
    if(!visible) {return;}

    framesSinceLastFrameChange++;
    if(framesSinceLastFrameChange >= (1/currentAnimation->speed)){
        framesSinceLastFrameChange = 0;
        frame++;
        if(frame >= currentAnimation->frames.size()){
            frame = 0;
        }
    }
    
    TransformComponent* transform = (TransformComponent*)owner->GetComponent<TransformComponent>();
    TransformComponent* camTransform = (TransformComponent*)linkedRenderer->camera->owner->GetComponent<TransformComponent>();

    sPositionUniformBlock[0] = _swapF32((transform->position.x - (camTransform->position.x)) / camTransform->size.x); // Position x
    sPositionUniformBlock[1] = _swapF32((transform->position.y - (camTransform->position.y)) / camTransform->size.y); // Position y
    sPositionUniformBlock[2] = _swapF32(transform->rotation - (camTransform->rotation)); // Rotation
    sPositionUniformBlock[3] = _swapF32(transform->size.x/(camTransform->size.x)); // X Scale
    sPositionUniformBlock[4] = _swapF32(transform->size.y/(camTransform->size.y)); // Y Scale
    sPositionUniformBlock[5] = _swapF32(((float)alpha)/255.0f);
    sPositionUniformBlock[6] = _swapF32(-0.5f);

    GX2SetVertexUniformBlock(0, sizeof(sPositionUniformBlock), (void*)sPositionUniformBlock);
    GX2Invalidate((GX2InvalidateMode)(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK), sPositionUniformBlock, sizeof(sPositionUniformBlock));

    linkedRenderer->SetImageToDraw(currentAnimation->frames[frame], sampler);

    GX2DrawEx(GX2_PRIMITIVE_MODE_QUADS, 4, 0, 1);

}