#include "MainRendererComponent.hpp"

#include <gx2/mem.h>
#include <gx2r/draw.h>
#include <gx2/registers.h>

#include <vector>

#include "camTablet.hpp"
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

MainRendererComponent::MainRendererComponent(){
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
}
void MainRendererComponent::Start(){
    if(camera == nullptr){
        camera = owner->GetComponent<Camera2DComponent>();
    }
}

void MainRendererComponent::Draw(DRAW_SCREEN_TYPE drawScreenType){
    if(drawScreenType != this->drawScreenType) {return;}
    WHBGfxClearColor(camera->bgColor.r, camera->bgColor.g, camera->bgColor.b, 1.0f);

    GX2SetFetchShader(&(group.fetchShader));
    GX2SetVertexShader(group.vertexShader);
    GX2SetPixelShader(group.pixelShader);
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);

    GX2RSetAttributeBuffer(&s_positionBuffer, 0, s_positionBuffer.elemSize, 0);
    GX2RSetAttributeBuffer(&s_texCoordBuffer, 1, s_texCoordBuffer.elemSize, 0);

    SetBlendModeBasic();
}

void MainRendererComponent::SetBlendModeBasic(){
    return;
    GX2SetAlphaTest(GX2_TRUE, GX2_COMPARE_FUNC_GREATER, 0.0f);
    GX2SetColorControl(GX2_LOGIC_OP_COPY, 0xFF, FALSE, TRUE);
    GX2SetBlendControl(GX2_RENDER_TARGET_0,
            /* RGB = [srcRGB * srcA] + [dstRGB * (1-srcA)] */
            GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA,
            GX2_BLEND_COMBINE_MODE_ADD,
            TRUE,
            /* A = [srcA * 1] + [dstA * (1-srcA)] */
            GX2_BLEND_MODE_ONE, GX2_BLEND_MODE_INV_SRC_ALPHA,
            GX2_BLEND_COMBINE_MODE_ADD);
}

void MainRendererComponent::SetImageToDraw(GX2Texture* texture, GX2Sampler* sampler){

    GX2SetPixelTexture(texture, group.pixelShader->samplerVars[0].location);
    GX2SetPixelSampler(sampler, group.pixelShader->samplerVars[0].location);
}