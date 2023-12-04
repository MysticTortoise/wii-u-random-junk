#pragma once

#include <whb/gfx.h>
#include <gx2/texture.h>

#include "datatypes.hpp"

#include <string>
#include <vector>

WHBGfxShaderGroup* GLSL_CompileShader(const char* vsSrc, const char* psSrc);

int InitializeGraphics();

WHBGfxShaderGroup* GLSL_CompileShaderFromFiles(std::string* vertexShaderPath, std::string* fragmentShaderPath);
WHBGfxShaderGroup* GLSL_CompileShaderFromFiles(const char *vertexShaderPath, const char* fragmentShaderPath);

class CamTabletRender;
class Sprite;


class CamTabletRender{
    public:

        CamTabletRender();
        ~CamTabletRender();
        
        void Render(std::vector<Sprite*> sprites);

        GX2RBuffer positionBuffer = { GX2R_RESOURCE_BIND_NONE };
        GX2RBuffer colourBuffer = { GX2R_RESOURCE_BIND_NONE };
        WHBGfxShaderGroup group = { GX2_FETCH_SHADER_TESSELLATION_NONE };

        GX2RBuffer s_positionBuffer = {};
        GX2RBuffer s_texCoordBuffer = {};

        Color clearColor;

};

class Sprite{
    private:
        GX2Texture* texture;
        GX2Sampler* sampler;
    public:
        Sprite(std::string imageFilePath);

        float x;
        float y;
        float width;
        float height;
    void Draw(CamTabletRender *renderer);
};

