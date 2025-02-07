#include "Camera2D.hpp"

Camera2DComponent::Camera2DComponent(JSON* jsonData){
    this->bgColor = Color(jsonData->operator[]("BGColor"));
}