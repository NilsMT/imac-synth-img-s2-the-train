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

void resetCamera() {
    camera_dist_zoom = 30.0f;
    yaw = 0.0f;
    pitch = 10.0f;
    camera_target_x = 0.0f;
    camera_target_y = 0.0f;
    camera_target_z = 0.0f;
}