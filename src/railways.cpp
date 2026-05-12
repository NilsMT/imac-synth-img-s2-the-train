#pragma once

#include <vector>
#include "nlohmann/json.hpp"

struct Railways {
    int size_grid = 1;
    std::vector<float> origin = {0.f, 0.f};
    std::vector<std::vector<float>> path = {};

    Railways(int sg,std::vector<float> o,std::vector<std::vector<float>> p) {
        size_grid = sg;
        origin = o;
        path = p;
    }
};