enum CAMERA_MODE {
    ORBITAL,
    TOP,
    FPS,
};

//camera config
int cameraMode = CAMERA_MODE::ORBITAL;
const float Z_NEAR {0.1f}; //the closest you can zoom in
const float Z_FAR {500.f}; //the farthest you can zoom out
float camera_dist_zoom = 30.0; //distance between origin and viewpoint
float yaw = 0.0f; //angle between x axis and viewpoint
float pitch = 10.0f; //angle between y axis and viewpoint
float camera_target_x = 0.0f; //viewed point x position
float camera_target_y = 0.0f; //viewed point y position
float camera_target_z = 0.0f; //viewed point z position

//camera reset
void resetCamera() {
    camera_dist_zoom = 30.0;
    yaw = 0.0f;
    pitch = 10.0f;
    camera_target_x = 0.0f;
    camera_target_y = 0.0f;
    camera_target_z = 0.0f;
}