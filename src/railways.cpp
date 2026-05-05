#include "railways.hpp"
#include <vector>

struct Railways {
    int size_grid = 0;
    std::vector<float> origin = {0.f, 1.f};
    std::vector<std::vector<float>> path = {};
    std::vector<float> train_position = origin;
};