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
class Camera2D;


class Camera2D{
    public:
        float x;
        float y;
        float width;
        float height;
        float rotation;

        Camera2D(float x = 0, float y = 0, float w = 1, float h = 1, float r = 0);
};

class CamTabletRender{
    public:

        CamTabletRender();
        ~CamTabletRender();
        
        void Render(const std::vector<Sprite>& sprites);

        GX2RBuffer positionBuffer = { GX2R_RESOURCE_BIND_NONE };
        GX2RBuffer colourBuffer = { GX2R_RESOURCE_BIND_NONE };
        WHBGfxShaderGroup group = { GX2_FETCH_SHADER_TESSELLATION_NONE };

        GX2RBuffer s_positionBuffer = {};
        GX2RBuffer s_texCoordBuffer = {};

        Camera2D camera;

        Color clearColor;

        alignas(0x100) uint32_t sPositionUniformBlock[8] = {};

};

class Sprite{
    private:
        GX2Texture* texture;
        GX2Sampler* sampler;
    public:
        Sprite(std::string imageFilePath);

        float x = 0;
        float y = 0;
        float width = 1;
        float height = 1;
        float rotation = 0;
    void Draw(CamTabletRender *renderer) const;
};
