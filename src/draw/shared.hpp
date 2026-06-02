#pragma once

#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "../global/global.hpp"

using namespace glbasimac;

namespace Draw {


    // --- RAIL DROIT ---
    extern GLBI_Convex_2D_Shape pave;
    // extern float sr;
    // extern float sx;
    // extern float rr;
    // Chaque rail est centré sur l axe x au position 3 et 7 
    extern float POS_X_RAIL1;
    extern float POS_X_RAIL2;
    // Chaque rail est un parallélépidède/rectangle de section sr x sr et de longueur 10. 
    // sr devra être une constante modifiable dans votre code.
    extern const float sr;
    // Chaque balast est un cylindre
    // rayon dont on choisit la valeur
    extern const float rr;
    // partant de x=2 à x=8
    // les constantes 2 et 8 pourraient être modifiable
    extern const float x_start_balast;
    extern const float x_end_balast;
    // hauteur
    extern float balast_heigth;
    //  Le premier est à sx en y puis il y a une distance de 2 ∗ sx entre chaque balast
    extern float sx;
    // --- RAIL DROIT ---


    extern float cell_size;

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

    void drawShapeWithColor(IndexedMesh* shape, Vector3D color);

    void drawShapeWithColor(StandardMesh* shape, Vector3D color);

    void drawShapeWithColor(GLBI_Convex_2D_Shape shape, Vector3D color);
}