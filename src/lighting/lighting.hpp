#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
using namespace glbasimac;
using namespace STP3D;
#include "../draw/shared.hpp"
#include "../json_data.hpp"
using namespace Draw;

void handleMainLighting(double time);
void handleTrainLighting(float x, float y,float z);