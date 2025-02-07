#include "datatypes.hpp"


Color::Color(float r, float g, float b, float a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(JSON jsonData){
    this->r = jsonData["x"];
    this->g = jsonData["y"];
    this->b = jsonData["z"];
    this->a = jsonData["w"];
}

Vector2::Vector2(float x, float y){
    this->x = x;
    this->y = y;
}

Vector2::Vector2(JSON jsonData){
    this->x = jsonData["x"];
    this->y = jsonData["y"];
}