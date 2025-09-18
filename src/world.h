#ifndef WORLD_H
#define WORLD_H

#include "object.h"

#include "raylib.h"
#include "raymath.h"
#include "json.hpp"

#include <vector>

float ComputePpiToFitBoard(const int& screenW, const int& screenH, const float& boardW_in, const float& boardH_in, const float& margin_px = 40.0f);

void DrawInchGrid(float ppi, int boardW_in, int boardH_in);

World GetWorld();

std::vector<Building> BuildBuildings(const float& ppi);




#endif
