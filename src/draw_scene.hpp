#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "railways.cpp"

#include "draw/base.hpp"
#include "draw/rails.hpp"
#include "draw/train.hpp"
#include "draw/shared.hpp"

using namespace glbasimac;

namespace Draw {
    /* Camera parameters and functions */
    extern const float Z_NEAR; //the closest you can zoom in
    extern const float Z_FAR; //the farthest you can zoom out
    extern float camera_dist_zoom; // Distance between origin and viewpoint
    extern float yaw; // Angle between x axis and viewpoint
    extern float pitch; // Angle between y axis and viewpoint
    extern float camera_sensitivity; // Mouse control sensitivity For the FPS view
    extern float camera_target_x; // Viewed point x position
    extern float camera_target_y; // Viewed point y position
    extern float camera_target_z; // Viewed point z position

    /* main stuffs */

    void initScene();

    void drawScene(float time, Railways* railways, bool isGridShown);
}