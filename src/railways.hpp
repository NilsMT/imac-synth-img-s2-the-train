#include <vector>

struct Railways {
    int size_grid;
    std::vector<float> origin;
    std::vector<std::vector<float>> path;
    std::vector<float> train_position;
};