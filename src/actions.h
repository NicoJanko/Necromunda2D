#ifndef ACTIONS_H
#define ACTIONS_H


#include "object.h"

#include <vector>

#include "raylib.h"
#include "raymath.h"

static bool CircleRectCollide(Vector2 center, float radius, Rectangle rec);
//const std::vector<Building>& B,
void UpdateMouvement(Actor& actor,  float df);

#endif