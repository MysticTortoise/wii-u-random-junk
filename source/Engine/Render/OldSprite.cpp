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
    texture = *TGA_LoadTexture((uint8_t *)data.data(), data.size());

    GX2InitSampler(&sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_LINEAR);
}

void Sprite::Draw(CamTabletRender *renderer)
{

}