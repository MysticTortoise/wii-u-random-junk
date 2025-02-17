#include "SpriteComponent.hpp"

#include <fstream>

#include "gx2/mem.h"
#include "gx2/draw.h"
#include "gx2/clear.h"

#include "TGAImport.hpp"

#include "TransformComponent.hpp"
#include "HelperStandard.hpp"

SpriteComponent::SpriteComponent(std::string imageFilePath){
    sampler = new GX2Sampler();
    std::ifstream fs("romfs:/" + imageFilePath, std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    texture = TGA_LoadTexture((uint8_t *)data.data(), data.size());

    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_LINEAR);
}
SpriteComponent* SpriteComponent::SpriteComponentFromJSON(GameScene* scene, JSON* jsonData){
    SpriteComponent* sprite = new SpriteComponent(jsonData->operator[]("Sprite"));
    sprite->linkedRenderer = scene->FindGameobjectByName(jsonData->operator[]("LinkedRenderer"))->GetComponent<MainRendererComponent>();
    if(jsonData->contains("Alpha"))
        sprite->alpha = jsonData->operator[]("Alpha");

    return sprite;
}


void SpriteComponent::Draw(DRAW_SCREEN_TYPE drawScreenType){
    if(drawScreenType != linkedRenderer->drawScreenType) {return;}
    if(!visible) {return;}
    TransformComponent* transform = (TransformComponent*)owner->GetComponent<TransformComponent>();
    TransformComponent* camTransform = (TransformComponent*)linkedRenderer->camera->owner->GetComponent<TransformComponent>();

    sPositionUniformBlock[0] = _swapF32((transform->position.x - (camTransform->position.x)) / camTransform->size.x); // Position x
    sPositionUniformBlock[1] = _swapF32((transform->position.y - (camTransform->position.y)) / camTransform->size.y); // Position y
    sPositionUniformBlock[2] = _swapF32(transform->rotation - (camTransform->rotation)); // Rotation
    sPositionUniformBlock[3] = _swapF32(transform->size.x/(camTransform->size.x)); // X Scale
    sPositionUniformBlock[4] = _swapF32(transform->size.y/(camTransform->size.y)); // Y Scale
    sPositionUniformBlock[5] = _swapF32(((float)alpha)/255.0f);
    sPositionUniformBlock[6] = _swapF32(0.0f);

    GX2SetVertexUniformBlock(0, sizeof(sPositionUniformBlock), (void*)sPositionUniformBlock);
    GX2Invalidate((GX2InvalidateMode)(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK), sPositionUniformBlock, sizeof(sPositionUniformBlock));

    linkedRenderer->SetImageToDraw(texture, sampler);

    GX2DrawEx(GX2_PRIMITIVE_MODE_QUADS, 4, 0, 1);

}

SpriteComponent::~SpriteComponent(){
    delete sampler;
    delete texture;
}