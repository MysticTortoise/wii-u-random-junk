#include "DisclaimerScreenCode.hpp"

#include "HelperStandard.hpp"
#include "GameStateManager.hpp"
#include "SceneList.hpp"

#include <algorithm>

DisclaimerScreenScript::DisclaimerScreenScript() {
    print("PLS BRO");
}

void DisclaimerScreenScript::Start(){
    sprite = owner->GetComponent<SpriteComponent>();
    sprite->alpha = 0;
}

void DisclaimerScreenScript::Update(){
    switch (progress)
    {
    case 0:
        alphaProgress += progressSpeed;
        if(alphaProgress >= 255){
            progress = 1;
            alphaProgress = 255;
        }
        break;
    case 1:
        waitTimer++;
        if(waitTimer >= 120){
            progress = 2;
        }
        break;
    case 2:
        alphaProgress -= progressSpeed;
        if(alphaProgress <= 0){
            GameStateManager::LoadSceneFromFile("SceneDefs/testScene.json");
            //GameStateManager::ChangeScene(GameScenes::TitleScreen());
        }
        break;
    default:
        break;
    }
    alphaProgress = std::clamp(alphaProgress,0,255);
    sprite->alpha = alphaProgress;
}