#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"
#include "raymath.h"



struct Building {
    ::Rectangle r;
};

struct Actor {
    ::Vector2 pos{};
    float radius{14.f};
    float moveMax{180.f};   
    float moveLeft{180.f};  
    bool moving{false};
    ::Vector2 target{};
    float speed{180.f};     
};

#endif