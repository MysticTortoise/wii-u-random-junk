#include "GameObject.hpp"

#include "TransformComponent.hpp"

#include <vector>

GameObject::GameObject(){
    TransformComponent* transform = new TransformComponent();
    AddComponent(transform);
}

void GameObject::Start(){
    for(GameObjectComponent* component : components){
        component->Start();
    }
}
void GameObject::Update(){
    for(GameObjectComponent* component : components){
        component->Update();
    }
}

GameObjectComponent* GameObject::AddComponent(GameObjectComponent* componentToAdd){
    components.push_back(componentToAdd);
    componentToAdd->owner = this;
    return componentToAdd;
}

GameObject::~GameObject(){
    for(GameObjectComponent* component : components)
    {
        delete component;
    }
}