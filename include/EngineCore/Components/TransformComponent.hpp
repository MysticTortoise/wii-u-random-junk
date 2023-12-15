#include "GameObject.hpp"

#include "datatypes.hpp"

class TransformComponent : public GameObjectComponent{
    public:
        Vector2 position = Vector2();
        Vector2 size = Vector2();
        float rotation = 0;

    void Translate(const Vector2& moveAmount);
};