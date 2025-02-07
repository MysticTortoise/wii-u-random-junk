#pragma once

#include <string>

#include "json.hpp"
using JSON = nlohmann::json;
using string = std::string;

class Color{
    public:
        float r = 0;
        float g = 0;
        float b = 0;
        float a = 1;


        Color(float r = 0, float g = 0, float b = 0,float a = 1);
        Color(JSON jsonData);
        
};

class Vector2{
    public:
        float x = 0;
        float y = 0;

        Vector2(float x = 0, float y = 0);
        Vector2(JSON jsonData);
};