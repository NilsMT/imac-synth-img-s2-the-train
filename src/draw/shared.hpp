#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "../json_data.hpp"

using namespace glbasimac;

namespace Draw {
    extern float sr;
    extern float sx;
    extern float rr;

    extern float cell_size;

    extern GLBI_Engine myEngine;
    extern GLBI_Set_Of_Points somePointsFrame;
    extern GLBI_Set_Of_Points somePointsGrid;

    extern IndexedMesh* sphere;
    extern IndexedMesh* cube;
    extern IndexedMesh* wedge;
    extern IndexedMesh* cylinderCover;
    extern StandardMesh* rect;

    /* helpers */
    void moveOrigin(float x, float y, float z);

    void rotateOrigin(float angle, float x, float y, float z);

    void scaleOrigin(float x, float y, float z);

    void drawShapeWithColor(IndexedMesh* shape, int r, int g, int b);

    void drawShapeWithColor(StandardMesh* shape, int r, int g, int b);

    void drawShapeWithColor(GLBI_Convex_2D_Shape shape, int r, int g, int b);
}