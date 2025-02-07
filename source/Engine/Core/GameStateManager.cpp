#include "GameStateManager.hpp"

#include <fstream>
#include <string>
#include <vector>

#include "Libs/json.hpp"

#include "HelperStandard.hpp"

#include "StringComponentClassMap.hpp"

#include "TransformComponent.hpp"

using JSON = nlohmann::json;

void GameStateManager::ChangeScene(GameScene* scene){
    print("Delete old scene...");
    if(currentScene != nullptr){
        currentScene->Exit();
        delete currentScene;
    }
    print("Start makin anew");
    currentScene = scene;
    currentScene->Start();
}

void GameStateManager::EndCurrentSceneScene(){
    if(currentScene == nullptr) {return;}

    currentScene->Exit();
    delete currentScene;
}

namespace SceneLoader{

    GameObjectComponent* buildComponent(GameObject* object, JSON* jsonData){
        std::string className = jsonData->operator[]("Class");
        print(className);
        GameObjectComponent* component = StringToComponentClassMap.at(className)(object->scene, jsonData);
        object->AddComponent(component);

        return component;
    }

    GameObject* buildObject(GameScene* scene, JSON* jsonData){
        GameObject* object = scene->CreateGameobject();
        object->name = jsonData->operator[]("Name");

        TransformComponent* transformComp = object->GetComponent<TransformComponent>();
        if(jsonData->contains("Position")){
            transformComp->position = Vector2(jsonData->operator[]("Position"));
        }
        if(jsonData->contains("Size")){
            transformComp->size = Vector2(jsonData->operator[]("Size"));
        }

        std::vector<JSON> componentListings = jsonData->operator[]("Components");
        for(JSON comp : componentListings){
            buildComponent(object,&comp);
        }

        return object;
    }

    GameScene* LoadSceneFromFile(std::string filepath){
        print("LoadScene");
        std::ifstream f("romfs:/" + filepath);
        JSON data = JSON::parse(f);

        GameScene* scene = new GameScene();

        std::vector<JSON> objectListings = data["Objects"];
        for(JSON obj : objectListings){
            buildObject(scene,&obj);
        }
        f.close();

        return scene;
    }
}

void GameStateManager::LoadSceneFromFile(std::string filepath){
    GameStateManager::ChangeScene(SceneLoader::LoadSceneFromFile(filepath));
}

GameScene* GameStateManager::currentScene = nullptr;