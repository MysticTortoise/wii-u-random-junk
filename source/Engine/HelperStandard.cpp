
#include <string>

#include "coreinit/debug.h"

#include "HelperStandard.hpp"


void print(std::string message){
    OSReport((message + "\n").c_str());
}
void print(const char* message){
    print((std::string)message);
}
void print(float number){
    print(std::to_string(number));
}
void print(bool value){
    if(value)
        print((std::string)"true");
    else
        print((std::string)"false");
}