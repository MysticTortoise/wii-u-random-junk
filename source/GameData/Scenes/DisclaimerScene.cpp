#include "SceneList.hpp"

#include "MainRendererComponent.hpp"
#include "Camera2D.hpp"

#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"

#include "DisclaimerScreenCode.hpp"

GameScene* GameScenes::DisclaimerScene(){
    GameScene* scene = new GameScene();

    GameObject* mainRenderObject = scene->CreateGameobject();
    mainRenderObject->AddComponent<MainRendererComponent>();
    mainRenderObject->AddComponent<Camera2DComponent>();

    TransformComponent* cameraTransform = mainRenderObject->GetComponent<TransformComponent>();
    cameraTransform->size = Vector2(1280,720);
    cameraTransform->position = Vector2(640,360);

    GameObject* disclaimerTextObject = scene->CreateGameobject();
    SpriteComponent* disclaimerTexSprite = new SpriteComponent("DisclaimerScreen/disclaimerText.tga");
    disclaimerTexSprite->linkedRenderer = mainRenderObject->GetComponent<MainRendererComponent>();
    disclaimerTextObject->AddComponent(disclaimerTexSprite);
    TransformComponent* disclaimerTextTransform = disclaimerTextObject->GetComponent<TransformComponent>();
    disclaimerTextTransform->position = Vector2(640,360);
    disclaimerTextTransform->size = Vector2(465,124);

    disclaimerTextObject->AddComponent<DisclaimerScreenScript>();

    return scene;
}