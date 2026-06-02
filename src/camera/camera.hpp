#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
using namespace glbasimac;
using namespace STP3D;

enum CAMERA_MODE {
    ORBITAL,
    TOP,
    FPS,
};

extern int cameraMode;
extern const float Z_NEAR; //how far can you zoom in
extern const float Z_FAR; //how far can you zoom out
extern float camera_dist_zoom; //how far away are you from the target
extern float yaw; //orientation (X Z)
extern float pitch; //orientation (Y)
extern float camera_target_x; //target x
extern float camera_target_y; //target y
extern float camera_target_z; //target z
extern float camera_pos_x; //camera x
extern float camera_pos_y; //camera y
extern float camera_pos_z; //camera z
extern float xpos; //mouse x
extern float ypos; //mouse y

//camera data
extern Vector3D pos_camera;
extern Vector3D viewed_point;
extern Vector3D up_vector;

void resetCamera();

void handleOrbitalCamera();
void handleTopCamera();
void handleFPSCamera();