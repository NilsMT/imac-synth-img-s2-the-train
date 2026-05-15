#pragma once

#include <vector>
#include "nlohmann/json.hpp"

struct JsonData {
    int size_grid = 1;
    std::vector<float> origin = {0.f, 0.f};
    std::vector<std::vector<float>> path = {};
    std::vector<std::vector<float>> trees = {};
};