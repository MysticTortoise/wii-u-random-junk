#include "Scene.hpp"

#include "whb/gfx.h"
#include <gx2/draw.h>

#include <vector>
#include <algorithm>

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
    for(GameObjectComponent* component : sortedComponents){
        component->Draw(DRAW_SCREEN_TV);
    }
    WHBGfxFinishRenderTV();

    WHBGfxBeginRenderDRC();
    for(GameObjectComponent* component : sortedComponents){
        component->Draw(DRAW_SCREEN_DRC);
    }
    WHBGfxFinishRender();

    WHBGfxFinishRender();
}

GameObject* GameScene::CreateGameobject(){
    GameObject* object = new GameObject();
    GameObjects.push_back(object);
    return object;
}

/*

BIG REMINDER
REFACTOR ENTIRE GODDAMN RENDER ENGINE
HOLY SHIT YOU FUCKED UP BUT U CAN FIX ITS.

*/