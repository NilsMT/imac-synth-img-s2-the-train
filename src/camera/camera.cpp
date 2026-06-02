#pragma once

#include "camera.hpp"

int cameraMode = CAMERA_MODE::ORBITAL;
const float Z_NEAR = 0.1f;
const float Z_FAR = 500.f;
float camera_dist_zoom = 30.0f;
float yaw = 0.0f;
float pitch = 10.0f;
float camera_target_x = 0.0f;
float camera_target_y = 0.0f;
float camera_target_z = 0.0f;
float camera_pos_x = 0.0f;
float camera_pos_y = 0.0f;
float camera_pos_z = 0.0f;
float xpos = 0.0f;
float ypos = 0.0f;

//camera data
Vector3D up_vector = {};

void handleOrbitalCamera() {
    //clamp to avoid inversion
    if (pitch < 0.0f) pitch = 0.0f;
    if (pitch > 89.0f) pitch = 89.0f;

    camera_pos_x = camera_dist_zoom * sin(deg2rad(yaw)) * cos(deg2rad(pitch));
    camera_pos_y = camera_dist_zoom * sin(deg2rad(pitch));
    camera_pos_z = -camera_dist_zoom * cos(deg2rad(yaw)) * cos(deg2rad(pitch));

    up_vector = Vector3D(0.0, 1.0, 0.0);  // Y is up
};

void handleTopCamera() {
    camera_pos_x = camera_target_x;
    camera_pos_y = camera_dist_zoom;
    camera_pos_z = camera_target_z;

    up_vector = Vector3D(0.0, 0.0, 1.0);  // Z is up
};

void handleFPSCamera() {
    //compute direction its looking (like orbital camera)
    float dir_x = sin(deg2rad(yaw)) * cos(deg2rad(pitch));
    float dir_y = sin(deg2rad(pitch));
    float dir_z = -cos(deg2rad(yaw)) * cos(deg2rad(pitch));

    //facing 1 unit away from camera
    camera_target_x = camera_pos_x + dir_x;
    camera_target_y = camera_pos_y + dir_y;
    camera_target_z = camera_pos_z + dir_z;

    up_vector = Vector3D(0.0, 1.0, 0.0);  // Y is up
};