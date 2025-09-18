#ifndef ACTIONS_H
#define ACTIONS_H


#include "object.h"

#include <vector>

#include "raylib.h"
#include "raymath.h"

static bool CircleRectCollide(Vector2 center, float radius, Rectangle rec);
//
void UpdateMouvement(Actor& actor,const std::vector<Building>& B,  float df);

#endif
