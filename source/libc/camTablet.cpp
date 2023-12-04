// excuse the absolute fucking mess, i'm generally an idiot. github pls works

// Header File
#include "camTablet.hpp"
// Standard Libs
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
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

const float s_positionData[8] = {
     -1.0f, -1.0f,
     1.0f, -1.0f,
     1.0f,  1.0f,
     -1.0f,  1.0f,
};
const float s_texCoords[8] = {
     0.0f, 1.0f,
     1.0f, 1.0f,
     1.0f, 0.0f,
     0.0f, 0.0f,
};

WHBGfxShaderGroup* GLSL_CompileShader(const char* vsSrc, const char* psSrc)
{
    char infoLog[1024];
    GX2VertexShader* vs = GLSL_CompileVertexShader(vsSrc, infoLog, sizeof(infoLog), GLSL_COMPILER_FLAG_NONE);
    if(!vs) {
        OSReport("Failed to compile vertex shader. Infolog: %s\n", infoLog);
        return NULL;
    }
    GX2PixelShader* ps = GLSL_CompilePixelShader(psSrc, infoLog, sizeof(infoLog), GLSL_COMPILER_FLAG_NONE);
    if(!ps) {
        OSReport("Failed to compile pixel shader. Infolog: %s\n", infoLog);
        return NULL;
    }
    WHBGfxShaderGroup* shaderGroup = (WHBGfxShaderGroup*)malloc(sizeof(WHBGfxShaderGroup));
    memset(shaderGroup, 0, sizeof(*shaderGroup));
    shaderGroup->vertexShader = vs;
    shaderGroup->pixelShader = ps;
    return shaderGroup;
}


int InitializeGraphics(){
    if(!GLSL_Init()) // Initialize Shader Compiler
    {
        return -1;
    }
    if(!WHBGfxInit()) // Initialize main graphics core.
    {
        return -1;
    }

    return 1;
}

WHBGfxShaderGroup* GLSL_CompileShaderFromFiles(std::string *vertexShaderPath,std::string *fragmentShaderPath){
    std::ifstream vShaderIn("romfs:/" + *vertexShaderPath);
    std::string vShaderContents((std::istreambuf_iterator<char>(vShaderIn)), 
    std::istreambuf_iterator<char>());
    const char* vShader = vShaderContents.c_str();

    std::ifstream fShaderIn("romfs:/" + *fragmentShaderPath);
    std::string fShaderContents((std::istreambuf_iterator<char>(fShaderIn)), 
    std::istreambuf_iterator<char>());
    const char* fShader = fShaderContents.c_str();

    return GLSL_CompileShader(vShader,fShader);
}
WHBGfxShaderGroup* GLSL_CompileShaderFromFiles(const char *vertexShaderPath, const char* fragmentShaderPath){
    std::string vPathString = vertexShaderPath;
    std::string fPathString = fragmentShaderPath;
    return GLSL_CompileShaderFromFiles(&vPathString,&fPathString);
}

CamTabletRender::CamTabletRender(){
    group = *GLSL_CompileShaderFromFiles("vertexShader.vert","fragmentShader.frag");

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
   void *posUploadBuffer = GX2RLockBufferEx(&s_positionBuffer,GX2R_RESOURCE_BIND_NONE);
   memcpy(posUploadBuffer, s_positionData, s_positionBuffer.elemSize * s_positionBuffer.elemCount);
   GX2RUnlockBufferEx(&s_positionBuffer,GX2R_RESOURCE_BIND_NONE);

   // Send Texture Coords
   s_texCoordBuffer.flags = (GX2RResourceFlags)(GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ);
   s_texCoordBuffer.elemSize = 2 * sizeof(float);
   s_texCoordBuffer.elemCount = 4;
   GX2RCreateBuffer(&s_texCoordBuffer);
   void *coordsUploadBuffer = GX2RLockBufferEx(&s_texCoordBuffer,GX2R_RESOURCE_BIND_NONE);
   memcpy(coordsUploadBuffer, s_texCoords, s_texCoordBuffer.elemSize * s_texCoordBuffer.elemCount);
   GX2RUnlockBufferEx(&s_texCoordBuffer,GX2R_RESOURCE_BIND_NONE);
}

CamTabletRender::~CamTabletRender(){
    GX2RDestroyBufferEx(&s_positionBuffer,GX2R_RESOURCE_BIND_NONE);
    GX2RDestroyBufferEx(&s_texCoordBuffer,GX2R_RESOURCE_BIND_NONE);
}

void CamTabletRender::Render(std::vector<Sprite*> sprites){


    OSReport("HEY GUYS \n");
    WHBGfxClearColor(clearColor.r,clearColor.g,clearColor.b,1.0f);

    OSReport("SET SHADERS OR SUMTHN \n");
    GX2SetFetchShader(&(group.fetchShader));
    GX2SetVertexShader(group.vertexShader);
    GX2SetPixelShader(group.pixelShader);
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);
    
    OSReport("SET BUFFERS OR SUMTHN \n");
  
    GX2RSetAttributeBuffer(&s_positionBuffer, 0, s_positionBuffer.elemSize, 0);
    GX2RSetAttributeBuffer(&s_texCoordBuffer, 1, s_texCoordBuffer.elemSize, 0);

    OSReport("DRAW SPRITES OR SUMTHN \n");

    for(Sprite *sprite : sprites){
        sprite->Draw(this);
    }
}




Sprite::Sprite(std::string imageFilePath){
    std::ifstream fs("romfs:/" + imageFilePath, std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    texture = TGA_LoadTexture((uint8_t *) data.data(), data.size());

    GX2InitSampler(sampler, GX2_TEX_CLAMP_MODE_CLAMP, GX2_TEX_XY_FILTER_MODE_LINEAR);
}

void Sprite::Draw(CamTabletRender *renderer){
    OSReport("SET TEXTURE\n");
    GX2SetPixelTexture(texture,renderer->group.pixelShader->samplerVars[0].location);
    OSReport("SET SAMPLER\n");
    GX2SetPixelSampler(sampler,renderer->group.pixelShader->samplerVars[0].location);

    print("Draw shit.");
    GX2DrawEx(GX2_PRIMITIVE_MODE_QUADS, 4, 0, 1);
}