#include "GamepadInputGrabber.hpp"


GamePadInputGrabberComponent::GamePadInputGrabberComponent(){
    gamepad = new Input::WiiUGamepad();
}

GamePadInputGrabberComponent::~GamePadInputGrabberComponent(){
    delete gamepad;
}


void GamePadInputGrabberComponent::Update(){
    gamepad->processInput();
}