#pragma once

#include <unordered_map>

#include "GameObject.hpp"

#include "TestClass.hpp"


typedef void (*voidFunctionType)(void);

constexpr unsigned int hashString(const char *s, int off = 0) {                        
    return !s[off] ? 5381 : (hashString(s, off+1)*33) ^ s[off];                           
}     

namespace Game{
    GameObjectComponent* CreateComponentFromString(std::string name, std::string data){
        switch(hashString(name.c_str())){
            case hashString("Sprite"):
            break;
            default: break;
        }
    }
};
// Figure this out eventually.