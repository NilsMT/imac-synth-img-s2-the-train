#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
using namespace glbasimac;
using namespace STP3D;
#include "../draw/shared.hpp"
#include "../json_data.hpp"
using namespace Draw;

//true if lights got initialized
extern bool lightInitialized;

//initialize the main light, aka the sun
void initMainLighting();

//initialize the train light at given coords (calculated to be the front of it)
void initTrainLighting();

//initialize both lights (sun an train) if not already OR do nothing
void initLights();

//move the main light, aka the sun
void handleMainLighting(double time);

//place the train light at given coords (calculated to be the front of it)
void handleTrainLighting(float x, float y,float z);