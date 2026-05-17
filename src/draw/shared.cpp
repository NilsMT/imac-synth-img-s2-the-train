#include "shared.hpp"
using namespace glbasimac;

namespace Draw {
    //////////////////////////////////////
    /* Shared variables */
    //////////////////////////////////////

    // --- RAIL DROIT --- 
    
    // PAVE
    GLBI_Convex_2D_Shape pave{3};


    // Chaque rail est centré sur l axe x au position 3 et 7 
    float POS_X_RAIL1=3.;
    float POS_X_RAIL2=7.;
    // Chaque rail est un parallélépidède/rectangle de section sr x sr et de longueur 10. 
    // sr devra être une constante modifiable dans votre code.
    const float sr = .5;
    // Chaque balast est un cylindre
    // rayon dont on choisit la valeur
    const float rr = .3;
    // partant de x=2 à x=8
    // les constantes 2 et 8 pourraient être modifiable
    const float x_start_balast = 2.;
    const float x_end_balast = 8.;
    // hauteur
    float balast_heigth = x_end_balast-x_start_balast;
    //  Le premier est à sx en y puis il y a une distance de 2 ∗ sx entre chaque balast
    float sx = 1-rr;

    // --- RAIL --- 

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