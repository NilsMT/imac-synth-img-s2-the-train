#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "railways.hpp"

using namespace glbasimac;

/* Camera parameters and functions */
static const float Z_NEAR {0.1f};
static const float Z_FAR {500.f};
extern float camera_dist_zoom;      // Distance between origin and viewpoint
extern float yaw;        // Angle between x axis and viewpoint
extern float pitch;        // Angle between y axis and viewpoint
extern float camera_sensitivity;
extern float camera_target_x;       // Viewed point x position
extern float camera_target_y;       // Viewed point y position
extern float camera_target_z;       // Viewed point z position


//CONSTANTS
//for the rails
extern float sr;
extern float sx;
extern float rr;

extern IndexedMesh* sphere;
extern IndexedMesh* cube;

/* OpenGL Engine */
extern GLBI_Engine myEngine;

/* helpers */
void moveOrigin(float x, float y, float z);

void rotateOrigin(float angle, float x, float y, float z);

void scaleOrigin(float x, float y, float z);

void drawShapeWithColor(IndexedMesh* shape, float r, float g, float b);

void drawShapeWithColor(GLBI_Convex_2D_Shape shape, float r, float g, float b);

/* main stuffs */

void initScene();

void drawFrame();

void drawGrid(int grid_size);

void drawGround();

void drawTrain(float time);

void drawRailCurve(float orientation);

void drawRailStraight(float orientation);

void drawScene(float time, Railways* railways, bool isGridShown);

