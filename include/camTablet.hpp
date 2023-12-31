#pragma once

#include <whb/gfx.h>
#include <gx2/texture.h>

#include "datatypes.hpp"

#include <string>
#include <vector>
#include <map>

WHBGfxShaderGroup* GLSL_CompileShader(const char* vsSrc, const char* psSrc);

int InitializeGraphics();

WHBGfxShaderGroup* GLSL_CompileShaderFromFiles(std::string* vertexShaderPath, std::string* fragmentShaderPath);
WHBGfxShaderGroup* GLSL_CompileShaderFromFiles(const char *vertexShaderPath, const char* fragmentShaderPath);


enum DRAW_SCREEN_TYPE{
    DRAW_SCREEN_TV = 0,
    DRAW_SCREEN_DRC = 1,
};

class CamTabletRender;
class Sprite;
class Camera2D;


class Camera2D{
    public:
        Vector2 position = Vector2(0,0);
        Vector2 size = Vector2(1,1);
        float rotation;

        Camera2D(float x = 0, float y = 0, float w = 1, float h = 1, float r = 0);
};

class CamTabletRender{
    public:

        CamTabletRender();
        ~CamTabletRender();
        
        void Render(const std::vector<Sprite*>& sprites);

        GX2RBuffer positionBuffer = { GX2R_RESOURCE_BIND_NONE };
        GX2RBuffer colourBuffer = { GX2R_RESOURCE_BIND_NONE };
        WHBGfxShaderGroup group = { GX2_FETCH_SHADER_TESSELLATION_NONE };

        GX2RBuffer s_positionBuffer = {};
        GX2RBuffer s_texCoordBuffer = {};

        Camera2D camera;

        Color clearColor;

        

};

class Sprite{
    private:
        GX2Texture texture;
        GX2Sampler sampler;
    public:
        Sprite(std::string imageFilePath);

        Vector2 position = Vector2();
        Vector2 size = Vector2(1,1);
        float rotation = 0;

        alignas(0x100) uint32_t sPositionUniformBlock[8] = {};
    void Draw(CamTabletRender *renderer);
};
