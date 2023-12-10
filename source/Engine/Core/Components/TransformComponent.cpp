#include "TransformComponent.hpp"


void TransformComponent::Translate(const Vector2& moveAmount){
    position.x += moveAmount.x;
    position.y += moveAmount.y;
}