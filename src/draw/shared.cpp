#include "shared.hpp"
using namespace glbasimac;

namespace Draw {
    //////////////////////////////////////
    /* Shared variables */
    //////////////////////////////////////

    float sr = 1;
    float sx = 1;
    float rr = 1;

    float cell_size = 10; //size of cells on X and Y, min 10 otherwise it break stuffs

    GLBI_Engine myEngine;
    GLBI_Set_Of_Points somePointsFrame(3);
    GLBI_Set_Of_Points somePointsGrid(3);
    GLBI_Convex_2D_Shape ground{3};

    IndexedMesh* sphere;
    IndexedMesh* cube;
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

    void drawShapeWithColor(IndexedMesh* shape, int r, int g, int b) {
        myEngine.setFlatColor(r/255.f,g/255.f,b/255.f);
        shape->draw();
    }

    void drawShapeWithColor(StandardMesh* shape, int r, int g, int b) {
        myEngine.setFlatColor(r/255.f,g/255.f,b/255.f);
        shape->draw();
    }

    void drawShapeWithColor(GLBI_Convex_2D_Shape shape, int r, int g, int b) {
        myEngine.setFlatColor(r/255.f,g/255.f,b/255.f);
        shape.drawShape();
    }
}