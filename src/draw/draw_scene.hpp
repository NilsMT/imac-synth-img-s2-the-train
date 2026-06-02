#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "../json_data.hpp"

#include "base.hpp"
#include "rails.hpp"
#include "train.hpp"
#include "train_station.hpp"
#include "tree.hpp"
#include "shared.hpp"

using namespace glbasimac;

namespace Draw {
    void initScene();

    void drawScene(float time, JsonData* json_data, bool isGridShown);
}