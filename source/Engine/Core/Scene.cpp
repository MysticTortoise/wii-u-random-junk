#include "Scene.hpp"

#include "whb/gfx.h"
#include <gx2/draw.h>
#include <gx2/registers.h>

#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

#include "HelperStandard.hpp"

bool sortComponentsByRenderPriority(GameObjectComponent* a, GameObjectComponent* n){
    return((int)a->renderPriority < (int)a->renderPriority);
}

void GameScene::Start(){
    for(GameObject* object : GameObjects){
        object->Start();
    }
}
void GameScene::Update(){
    for(GameObject* object : GameObjects){
        object->Update();
    }
    SceneTick++;
}
void GameScene::Draw(){

    std::vector<GameObjectComponent*> sortedComponents = {};
    for(GameObject* object : GameObjects){
        for(GameObjectComponent* component : object->components){
            sortedComponents.push_back(component);
        }
    }
    std::sort(sortedComponents.begin(),sortedComponents.end(),sortComponentsByRenderPriority);
    
    WHBGfxBeginRender();

    WHBGfxBeginRenderTV();
    GX2SetAlphaTest(GX2_TRUE, GX2_COMPARE_FUNC_GREATER, 0.0f);
    GX2SetColorControl(GX2_LOGIC_OP_COPY, 0xFF, TRUE, TRUE);
    GX2SetBlendControl(GX2_RENDER_TARGET_0,
            /* RGB = [srcRGB * srcA] + [dstRGB * (1-srcA)] */
            GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA,
            GX2_BLEND_COMBINE_MODE_ADD,
            TRUE,
            /* A = [srcA * 1] + [dstA * (1-srcA)] */
            GX2_BLEND_MODE_INV_SRC_ALPHA, GX2_BLEND_MODE_ONE,
            GX2_BLEND_COMBINE_MODE_ADD);
    for(GameObjectComponent* component : sortedComponents){
        component->Draw(DRAW_SCREEN_TV);
    }
    WHBGfxFinishRenderTV();

    WHBGfxBeginRenderDRC();
    for(GameObjectComponent* component : sortedComponents){
        component->Draw(DRAW_SCREEN_DRC);
    }
    WHBGfxFinishRenderDRC();

    WHBGfxFinishRender();
}
void GameScene::Exit(){
    for(GameObject* object : GameObjects){
        object->Exit();
    }
}

GameObject* GameScene::CreateGameobject(){
    GameObject* object = new GameObject();
    object->scene = this;
    GameObjects.push_back(object);
    return object;
}
GameObject* GameScene::FindGameobjectByName(std::string name){
    for(GameObject* object : GameObjects){
        if(object->name == name){
            return object;
        }
    }
    return nullptr;
}

GameScene::GameScene(){
    // Do nothing.
}

GameScene::GameScene(std::vector<GameObject*> objects){
    for(GameObject* object : objects){
        GameObjects.push_back(object);
    }
}

GameScene::~GameScene(){
    for(GameObject* object : GameObjects){
        delete object;
    }
}


enum GAMESCENE_LOAD_MODE{
    OBJECTS,
};

void GameScene::LoadFromAssetFile(std::string assetPath){
    
}