#pragma once


class Color{
    public:
        float r;
        float g;
        float b;
        float a = 0;


        Color(float r = 0, float g = 0, float b = 0,float a = 0);
        
};

class Vector2{
    public:
        float x = 0;
        float y = 0;

        Vector2(float x = 0, float y = 0);
};