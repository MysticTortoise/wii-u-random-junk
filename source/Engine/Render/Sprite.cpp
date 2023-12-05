#include "camTablet.hpp"


#include <coreinit/debug.h>
#include <gx2/draw.h>
#include <gx2/mem.h>

#include "TGAImport.hpp"
#include "HelperStandard.hpp"
#include "numberSwapper.hpp"


Sprite::Sprite(std::string imageFilePath)
{
    std::ifstream fs("romfs:/" + imageFilePath, std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    texture = TGA_LoadTexture((uint8_t *)data.data(), data.size());

    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_LINEAR);
}

void Sprite::Draw(CamTabletRender *renderer) const
{
    renderer->sPositionUniformBlock[0] = _swapF32(position.x - renderer->camera.position.x); // Position x
    renderer->sPositionUniformBlock[1] = _swapF32(position.y - renderer->camera.position.y); // Position y
    renderer->sPositionUniformBlock[2] = _swapF32(rotation - renderer->camera.rotation); // Rotation
    renderer->sPositionUniformBlock[3] = _swapF32(size.x/renderer->camera.size.x); // X Scale
    renderer->sPositionUniformBlock[4] = _swapF32(size.y/renderer->camera.size.y); // Y Scale
    GX2SetVertexUniformBlock(0, sizeof(renderer->sPositionUniformBlock), (void*)renderer->sPositionUniformBlock);
    GX2Invalidate((GX2InvalidateMode)(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK), renderer->sPositionUniformBlock, sizeof(renderer->sPositionUniformBlock));


    GX2SetPixelTexture(texture, renderer->group.pixelShader->samplerVars[0].location);
    GX2SetPixelSampler(sampler, renderer->group.pixelShader->samplerVars[0].location);

    GX2DrawEx(GX2_PRIMITIVE_MODE_QUADS, 4, 0, 1);
}