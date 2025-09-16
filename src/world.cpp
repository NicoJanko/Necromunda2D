#include "world.h"
#include "object.h"

#include "raylib.h"
#include "raymath.h"
#include "json.hpp"

#include <vector>
#include <fstream>
#include <sstream>

std::vector<Building> BuildBuildings() {
    //load building layout
    std::ifstream f("resource/maps/map1.json");
    nlohmann::json J;
    std::stringstream buffer;
    buffer << f.rdbuf();
    J = nlohmann::json::parse(buffer.str());

    std::vector<Building> buildings;
    if (J.contains("buildings") && J["buildings"].is_array()) {
        for (auto& b : J["buildingd"]) {
            Building B{};
            B.r.x = b.value("x",0.0f);
            B.r.y = b.value("y",0.0f);
            B.r.width = b.value("width",0.0f);
            B.r.height = b.value("h",0.0f);
            buildings.push_back(B);
        }
    }
    return buildings;

};