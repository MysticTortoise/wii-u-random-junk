// excuse the absolute fucking mess, i'm generally an idiot. github pls works

// Header File
#include "camTablet.hpp"
// Standard Libs
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <array>
// Wii U libs
#include <whb/gfx.h>

#include <gx2/draw.h>
#include <gx2/shaders.h>
#include <gx2/mem.h>
#include <gx2/registers.h>
#include <gx2r/draw.h>
#include <gx2r/buffer.h>

#include <coreinit/debug.h>
// Internal Libs
#include "CafeGLSLCompiler.h"
#include "TGAImport.hpp"
#include "numberSwapper.hpp"

#include "HelperStandard.hpp"

const float sprite_PositionData_Base[8] = {
    -1.0f,
    -1.0f,
    1.0f,
    -1.0f,
    1.0f,
    1.0f,
    -1.0f,
    1.0f,
};
const float sprite_TexCoord_Base[8] = {
    0.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
};



CamTabletRender::CamTabletRender()
{
    group = *GLSL_CompileShaderFromFiles("vertexShader.vert", "fragmentShader.frag");

    // Stuff Happens

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, group.vertexShader->program, group.vertexShader->size);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, group.pixelShader->program, group.pixelShader->size);

    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);

    WHBGfxInitShaderAttribute(&group, "aPos", 0, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    WHBGfxInitShaderAttribute(&group, "aTexCoord", 1, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    WHBGfxInitFetchShader(&group);

    // Send vertex positions
    s_positionBuffer.flags = (GX2RResourceFlags)(GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ);
    s_positionBuffer.elemSize = 2 * sizeof(float);
    s_positionBuffer.elemCount = 4;
    GX2RCreateBuffer(&s_positionBuffer);
    void *posUploadBuffer = GX2RLockBufferEx(&s_positionBuffer, GX2R_RESOURCE_BIND_NONE);
    memcpy(posUploadBuffer, sprite_PositionData_Base, s_positionBuffer.elemSize * s_positionBuffer.elemCount);
    GX2RUnlockBufferEx(&s_positionBuffer, GX2R_RESOURCE_BIND_NONE);

    // Send Texture Coords
    s_texCoordBuffer.flags = (GX2RResourceFlags)(GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ);
    s_texCoordBuffer.elemSize = 2 * sizeof(float);
    s_texCoordBuffer.elemCount = 4;
    GX2RCreateBuffer(&s_texCoordBuffer);
    void *coordsUploadBuffer = GX2RLockBufferEx(&s_texCoordBuffer, GX2R_RESOURCE_BIND_NONE);
    memcpy(coordsUploadBuffer, sprite_TexCoord_Base, s_texCoordBuffer.elemSize * s_texCoordBuffer.elemCount);
    GX2RUnlockBufferEx(&s_texCoordBuffer, GX2R_RESOURCE_BIND_NONE);



    camera = Camera2D();
}

CamTabletRender::~CamTabletRender()
{
    GX2RDestroyBufferEx(&s_positionBuffer, GX2R_RESOURCE_BIND_NONE);
    GX2RDestroyBufferEx(&s_texCoordBuffer, GX2R_RESOURCE_BIND_NONE);
}

void CamTabletRender::Render(const std::vector<Sprite> &sprites)
{

    WHBGfxClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);

    GX2SetFetchShader(&(group.fetchShader));
    GX2SetVertexShader(group.vertexShader);
    GX2SetPixelShader(group.pixelShader);
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);

    GX2RSetAttributeBuffer(&s_positionBuffer, 0, s_positionBuffer.elemSize, 0);
    GX2RSetAttributeBuffer(&s_texCoordBuffer, 1, s_texCoordBuffer.elemSize, 0);

    int spriteCount = sprites.size();

    for (Sprite const sprite : sprites)
    {
        sprite.Draw(this);
    }
}

