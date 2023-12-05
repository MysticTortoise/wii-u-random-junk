#include "camTablet.hpp"


Camera2D::Camera2D(float x, float y, float w, float h, float r){
    this->position.x = x;
    this->position.y = y;
    this->size.x = w;
    this->size.y = h;
    this->rotation = r;
}