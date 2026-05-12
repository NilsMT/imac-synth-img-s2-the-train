#include "shared.hpp"
using namespace glbasimac;

namespace Draw {
    //////////////////////////////////////
    /* Shared variables */
    //////////////////////////////////////

    float sr = 1;
    float sx = 1;
    float rr = 1;

    float cell_size = 10.0; //size of cells on X and Y

    GLBI_Engine myEngine;
    GLBI_Set_Of_Points somePointsFrame(3);
    GLBI_Set_Of_Points somePointsGrid(3);
    GLBI_Convex_2D_Shape ground{3};

    IndexedMesh* sphere;
    IndexedMesh* cube;
    IndexedMesh* cylinder;
    IndexedMesh* wedge;
    IndexedMesh* cylinderCover;
    
    

    //////////////////////////////////////
    /* Functions */
    //////////////////////////////////////



    void moveOrigin(float x, float y, float z) {
        myEngine.mvMatrixStack.addTranslation({x,y,z});
        myEngine.updateMvMatrix();
    }

    void rotateOrigin(float angle, float x, float y, float z) {
        myEngine.mvMatrixStack.addRotation(angle, {x,y,z});
        myEngine.updateMvMatrix();
    }

    void scaleOrigin(float x, float y, float z) {
        myEngine.mvMatrixStack.addHomothety({x,y,z});
        myEngine.updateMvMatrix();
    }

    void drawShapeWithColor(IndexedMesh* shape, float r, float g, float b) {
        myEngine.setFlatColor(r,g,b);
        shape->draw();
    }

    void drawShapeWithColor(GLBI_Convex_2D_Shape shape, float r, float g, float b) {
        myEngine.setFlatColor(r,g,b);
        shape.drawShape();
    }
}