#include "GameObject.hpp"

#include "datatypes.hpp"

class TransformComponent : public GameObjectComponent{
    public:
        Vector2 position;
        Vector2 size;
        float rotation;

    void Translate(const Vector2& moveAmount);
};