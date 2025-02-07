#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <typeindex>
#include <tuple>
#include <stdint.h>

#include "datatypes.hpp"

#include "camTablet.hpp"
#include "RenderHelper.hpp"

#include "EngineCoreBaseDefines.hpp"

#include "Libs/json.hpp"
using JSON = nlohmann::json;

class GameObject;
class GameObjectComponent;

class GameObjectComponent{
    public:
    GameObject* owner = nullptr; // A pointer to the Component's GameObject.
    RENDER_PRIORITY renderPriority = RENDER_PRIORITY_STANDARD;

    virtual void Start() {}; // Called at the beginning of a scene.
    virtual void Update() {}; // Called every frame.
    virtual void Draw(DRAW_SCREEN_TYPE drawScreenType) {}; // Called when the object has to be drawn.
    virtual void Exit() {}; // Called when the object is being destroyed or deloading.

    static GameObjectComponent* CreateFromString(std::string data) { return new GameObjectComponent();};

    virtual ~GameObjectComponent() {};
};

class GameObject{
    public:
    std::string name = ""; // The name of the GameObject
    uint64_t id = 0; // The GameObject's unique ID.
    GameScene* scene = nullptr;

    std::vector<GameObjectComponent*> components = {}; // A list of pointers to the GameObject's components.

    GameObject();
    GameObject(std::vector<GameObjectComponent*> components);

    template <class T>
    T* AddComponent(){ // Add a specified component to the GameObject.
        static_assert(std::is_base_of<GameObjectComponent, T>::value, "Attempt to call AddComponent on a GameObject, but the provided type is not a GameObjectComponent.");

        GameObjectComponent* component = new T();
        component->owner = this;
        components.push_back(component);

        return (T*)component;
    }; // Unfortunately due to Template shenanigans, this has to be defined here. :(

    GameObjectComponent* AddComponent(GameObjectComponent* componentToAdd);


    template <class T>
    T* GetComponent(){
        static_assert(std::is_base_of<GameObjectComponent, T>::value, "Attempt to call GetComponent on a GameObject, but the provided type is not a GameObjectComponent.");

        for(GameObjectComponent* component : components){
            if(typeid(*component) == typeid(T)){
                return (T*)component;
            }
        }

        return nullptr;
    }

    void Start(); // Called when the object is loaded into a scene.
    void Update(); // Called every frame
    void Exit(); // Called when the object is being removed.

    ~GameObject(); // Destructor.
};