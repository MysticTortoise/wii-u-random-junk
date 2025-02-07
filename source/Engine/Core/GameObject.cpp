#include "GameObject.hpp"

#include "TransformComponent.hpp"

#include <vector>

GameObject::GameObject(){
    TransformComponent* transform = new TransformComponent();
    AddComponent(transform);
}

GameObject::GameObject(std::vector<GameObjectComponent*> components){
    for(GameObjectComponent* component : components){
        this->components.push_back(component);
    }
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
void GameObject::Exit(){
    for(GameObjectComponent* component : components){
        component->Exit();
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