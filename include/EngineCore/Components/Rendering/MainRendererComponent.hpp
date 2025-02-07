#pragma once

#include "GameObject.hpp"

#include <vector>

#include "Camera2D.hpp"

#include "camTablet.hpp"

class MainRendererComponent : public GameObjectComponent{

    private:
    GX2RBuffer positionBuffer = { GX2R_RESOURCE_BIND_NONE };
    GX2RBuffer colourBuffer = { GX2R_RESOURCE_BIND_NONE };
    WHBGfxShaderGroup group = { GX2_FETCH_SHADER_TESSELLATION_NONE };

    GX2RBuffer s_positionBuffer = {};
    GX2RBuffer s_texCoordBuffer = {};


    public:
    RENDER_PRIORITY renderPriority = RENDER_PRIORITY_SETUP;
    DRAW_SCREEN_TYPE drawScreenType = DRAW_SCREEN_TV;

    Camera2DComponent* camera = nullptr;

    void Start();
    void Draw(DRAW_SCREEN_TYPE drawScreenType);

    void SetImageToDraw(GX2Texture* texture, GX2Sampler* sampler);
    void SetBlendModeBasic();
    
    MainRendererComponent();
};