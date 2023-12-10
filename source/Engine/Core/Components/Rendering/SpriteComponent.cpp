#include "SpriteComponent.hpp"

#include <fstream>

#include "gx2/mem.h"
#include "gx2/draw.h"

#include "TGAImport.hpp"

#include "TransformComponent.hpp"
#include "HelperStandard.hpp"

SpriteComponent::SpriteComponent(std::string imageFilePath){
    print("time to load sprite");
    std::ifstream fs("romfs:/" + imageFilePath, std::ios::in | std::ios::binary);
    print("file opens good");
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    print("data read fine");
    texture = TGA_LoadTexture((uint8_t *)data.data(), data.size());
    print("texture loaded good. it's the sampelr aint it. fuck you sampler.");

    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_LINEAR);
    print("so wait the sampler worked fine??? what the fuck???");
}


void SpriteComponent::Draw(DRAW_SCREEN_TYPE drawScreenType){
    TransformComponent* transform = (TransformComponent*)owner->GetComponent<TransformComponent>();
    TransformComponent* camTransform = (TransformComponent*)linkedRenderer->camera->owner->GetComponent<TransformComponent>();

    sPositionUniformBlock[0] = _swapF32((transform->position.x - (camTransform->position.x)) / camTransform->size.x); // Position x
    sPositionUniformBlock[1] = _swapF32((transform->position.y - (camTransform->position.y)) / camTransform->size.y); // Position y
    sPositionUniformBlock[2] = _swapF32(transform->rotation - (camTransform->rotation)); // Rotation
    sPositionUniformBlock[3] = _swapF32(transform->size.x/(camTransform->size.x)); // X Scale
    sPositionUniformBlock[4] = _swapF32(transform->size.y/(camTransform->size.y)); // Y Scale

    GX2SetVertexUniformBlock(0, sizeof(sPositionUniformBlock), (void*)sPositionUniformBlock);
    GX2Invalidate((GX2InvalidateMode)(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK), sPositionUniformBlock, sizeof(sPositionUniformBlock));

    linkedRenderer->SetImageToDraw(texture, sampler);

    GX2DrawEx(GX2_PRIMITIVE_MODE_QUADS, 4, 0, 1);

}