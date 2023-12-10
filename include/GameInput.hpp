#pragma once

#include <vector>
#include <map>

#include "vpad/input.h"

#include "datatypes.hpp"


namespace Input{
    

enum ButtonType{
    ButtonB = 0,
    ButtonA = 1,
    ButtonX = 2,
    ButtonY = 3,
    ButtonStart = 4,
    ButtonSelect = 5,
    ButtonOne = 6,
    ButtonTwo = 7,
    ButtonL = 10,
    ButtonR = 20,
    ButtonZL = 11,
    ButtonZR = 21,
};

const std::map<ButtonType,VPADButtons> ButtonTypeToVPAD = {
    {ButtonA, VPAD_BUTTON_A},
    {ButtonB, VPAD_BUTTON_B},
    {ButtonX, VPAD_BUTTON_X},
    {ButtonY, VPAD_BUTTON_Y},
    {ButtonStart, VPAD_BUTTON_PLUS},
    {ButtonSelect, VPAD_BUTTON_MINUS},
    {ButtonL,VPAD_BUTTON_L},
    {ButtonR,VPAD_BUTTON_R},
    {ButtonZL,VPAD_BUTTON_ZL},
    {ButtonZR,VPAD_BUTTON_ZR},
};


struct Button{
    public:
    ButtonType buttonType;
    bool isPressed;
    bool wasPressedLastFrame;

    Button(ButtonType type){
        buttonType = type;
    }

    bool wasJustPressed(){
        return (isPressed && !wasPressedLastFrame);
    }
};

enum AxisInputType{
    AxisLeftStick = 0,
    AxisRightStick = 1,
    AxisDPAD = 2,
};

struct AxisInput2D{
    AxisInputType axisType;
    Vector2 value;
    Vector2 change;

    AxisInput2D(AxisInputType type){
        axisType = type;
    }
};

class Controller{ // Base class for all controller types.
    public:

        Controller() = default;
        
        std::map<ButtonType,Button> buttons;
        std::map<AxisInputType,AxisInput2D> axes;


        virtual void processInput() {};
};



class WiiUGamepad : public Controller{ // Wii U Gamepad controller.
    public:

        std::map<ButtonType,Button> buttons = {
            {ButtonA, Button(ButtonA)},
            {ButtonB, Button(ButtonB)},
            {ButtonX, Button(ButtonX)},
            {ButtonY, Button(ButtonY)},
            {ButtonL, Button(ButtonL)},
            {ButtonR, Button(ButtonR)},
            {ButtonZL, Button(ButtonZL)},
            {ButtonZR, Button(ButtonZR)},
            {ButtonSelect,Button(ButtonSelect)},
            {ButtonStart,Button(ButtonStart)},
        };
        std::map<AxisInputType,AxisInput2D> axes = {
            {AxisLeftStick,AxisInput2D(AxisLeftStick)},
            {AxisRightStick,AxisInput2D(AxisRightStick)},
            {AxisDPAD,AxisInput2D(AxisDPAD)},
        };

        void processInput() override;

};

}