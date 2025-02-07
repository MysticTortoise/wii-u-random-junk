#pragma once


#include <map>
#include <string>
#include <functional>

#include "GameObject.hpp"

#include "HelperStandard.hpp"

#include "MainRendererComponent.hpp"
#include "Camera2D.hpp"
#include "SpriteComponent.hpp"
#include "AnimatedSpriteComponent.hpp"

#include "DisclaimerScreenCode.hpp"


const std::map<std::string,std::function<GameObjectComponent*(GameScene* scene, JSON* jsonData)>> StringToComponentClassMap = {
    {"MainRenderComponent", [](GameScene* scene, JSON* jsonData) -> MainRendererComponent* { return new MainRendererComponent; } },
    {"CameraComponent", [](GameScene* scene, JSON* jsonData) -> Camera2DComponent* { return new Camera2DComponent(jsonData); } },
    {"SpriteComponent", [](GameScene* scene, JSON* jsonData) -> SpriteComponent* { return SpriteComponent::SpriteComponentFromJSON(scene,jsonData); } },
    {"AnimatedSpriteComponent", [](GameScene* scene, JSON* jsonData) -> AnimatedSpriteComponent* { return AnimatedSpriteComponent::AnimatedSpriteComponentFromJSON(scene,jsonData); } },
    {"DisclaimerScreenScript", [](GameScene* scene, JSON* jsonData) -> DisclaimerScreenScript* { return new DisclaimerScreenScript(); } },
};