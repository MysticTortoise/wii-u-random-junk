#include "SceneList.hpp"

#include "MainRendererComponent.hpp"
#include "Camera2D.hpp"

#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"

/*GameScene* GameScenes::TitleScreen(){
    // Boilerplate scene setup
    GameScene* scene = new GameScene();

    GameObject* mainRenderObject = scene->CreateGameobject();
    mainRenderObject->AddComponent<MainRendererComponent>();
    mainRenderObject->AddComponent<Camera2DComponent>();
    TransformComponent* cameraTransform = mainRenderObject->GetComponent<TransformComponent>();
    cameraTransform->size = Vector2(1280,720);
    cameraTransform->position = Vector2(640,360);
    // End of setup

    // BACKGROUND
    GameObject* freddyBG = scene->CreateGameobject();
    SpriteComponent* freddyBGSprite = new SpriteComponent("TitleScreen/FreddyBG/freddy1.tga");
    freddyBG->AddComponent(freddyBGSprite);
    freddyBG->GetComponent<SpriteComponent>()->linkedRenderer = mainRenderObject->GetComponent<MainRendererComponent>();
    TransformComponent* freddyBGTransform = freddyBG->GetComponent<TransformComponent>();
    freddyBGTransform->position = Vector2(640,360);
    freddyBGTransform->size = Vector2(1280,720);



    return scene;
}*/