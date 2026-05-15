#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "json_data.hpp"

#include "draw/base.hpp"
#include "draw/rails.hpp"
#include "draw/train.hpp"
#include "draw/train_station.hpp"
#include "draw/tree.hpp"
#include "draw/shared.hpp"

using namespace glbasimac;

namespace Draw {
    void initScene();

    void drawScene(float time, JsonData* json_data, bool isGridShown);
}