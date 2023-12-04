
#include <string>

#include "coreinit/debug.h"

#include "HelperStandard.hpp"


void print(std::string message){
    OSReport((message + "\n").c_str());
}