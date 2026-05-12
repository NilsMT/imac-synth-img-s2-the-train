enum CAMERA_MODE {
    ORBITAL,
    TOP,
    FPS,
};

extern int cameraMode;
extern const float Z_NEAR;
extern const float Z_FAR;
extern float camera_dist_zoom;
extern float yaw;
extern float pitch;
extern float camera_target_x;
extern float camera_target_y;
extern float camera_target_z;

void resetCamera();