#include "rails.hpp"

namespace Draw {
    // Le "rail droit" est défini avec 5 balasts et 2 rails
    // Les 5 balasts sont répartis uniformément le long du rail
    void initRail(){

        // PAVE COORD
        std::vector<float> paveCoord1{
            // x,y,z
            // vu du dessus
        // --- FACE 1 ---
            // Triangle 1
            -sr/2,0,0,
            -sr/2,0,10,
            sr/2,0,0,
            // Triangle 2
            sr/2,0,10,
            -sr/2,0,10,
            sr/2,0,0,
        // --- COTE FACE 2 ---
            // Triangle 1
            -sr/2,sr,0,
            -sr/2,sr,10,
            -sr/2,0,0,
            // Triangle 2
            -sr/2,0,10,
            -sr/2,sr,10,
            -sr/2,0,0,
            
        // --- COTE FACE 1 ---
            // Triangle 1
            sr/2,sr,0,
            sr/2,sr,10,
            sr/2,0,0,
            // Triangle 2
            sr/2,0,10,
            sr/2,sr,10,
            sr/2,0,0,

        // --- FACE 2 ---
            // Triangle 1
            -sr/2,sr,0,
            -sr/2,sr,10,
            sr/2,sr,0,
            // Triangle 2
            sr/2,sr,10,
            -sr/2,sr,10,
            sr/2,sr,0,
        };
        pave.changeNature(GL_TRIANGLES);
        pave.initShape(paveCoord1);

    }

    void drawTroncon(){
        // TRONCON DE BOIS
        float angle{};
        angle=90.;
        // Conversion Radian
        float angleRadiant{};
        angleRadiant=M_PI*angle/180;
        // Taille du troncon de bois
        float troncon_height = 6;
        // *2 car de base c'est 0.5
        float troncon_width = rr*2;
        // push	
        myEngine.mvMatrixStack.pushMatrix();
        // Vector3D translationRail3{POS_X_RAIL1,10,0};
        // myEngine.mvMatrixStack.addTranslation(translationRail3);
            // rotation
            Vector3D rotationTroncon(0.,angleRadiant,0.);
            myEngine.mvMatrixStack.addRotation(M_PI/2,rotationTroncon);
                // update
                myEngine.updateMvMatrix();
                scaleOrigin(troncon_width, troncon_width, troncon_height);
                drawShapeWithColor(cylinderCover, 70, 30, 0);
        // pop
        myEngine.mvMatrixStack.popMatrix();
        // update
        myEngine.updateMvMatrix();
    }

    void drawRailStraight(float orientation) {
        float angleRadiant{};
        angleRadiant=M_PI*orientation/180;
        myEngine.setFlatColor(.41f,.41f,.41f);

        myEngine.mvMatrixStack.pushMatrix();
            // on se place au centre de la grille pour la rotation
            myEngine.mvMatrixStack.addTranslation({5,0,5});
            Vector3D railOrientation(0.,angleRadiant,0.);
            myEngine.mvMatrixStack.addRotation(M_PI/2,railOrientation);
            myEngine.mvMatrixStack.addTranslation({-5,0,-5});
        // update
        myEngine.updateMvMatrix();

        // Premier PAVE
        // push	
        myEngine.mvMatrixStack.pushMatrix();
        Vector3D translationRail1{POS_X_RAIL1,10+rr,0};
        myEngine.mvMatrixStack.addTranslation(translationRail1);
        // update
        myEngine.updateMvMatrix();
        pave.drawShape();
        // pop
        myEngine.mvMatrixStack.popMatrix();
        // update
        myEngine.updateMvMatrix();

        // Deuxieme PAVE
        // push	
        myEngine.mvMatrixStack.pushMatrix();
        Vector3D translationRail2{POS_X_RAIL2,10+rr,0};
        myEngine.mvMatrixStack.addTranslation(translationRail2);
        // update
        myEngine.updateMvMatrix();
        pave.drawShape();
        // pop
        myEngine.mvMatrixStack.popMatrix();
        // update
        myEngine.updateMvMatrix();

        // TRONCON
        // push	
        myEngine.mvMatrixStack.pushMatrix();
            Vector3D translationTroncon1{2,10,sx+rr};
            myEngine.mvMatrixStack.addTranslation(translationTroncon1);
        // update
        myEngine.updateMvMatrix();
        drawTroncon();
        // pop
        myEngine.mvMatrixStack.popMatrix();
        // update
        myEngine.updateMvMatrix();
        float old_z{sx+rr};
        for(int i{0};i<4;i++){
            old_z=old_z+rr+2*sx+rr;
            // push	
            myEngine.mvMatrixStack.pushMatrix();
                Vector3D translationTroncon2{2,10,old_z};
                myEngine.mvMatrixStack.addTranslation(translationTroncon2);
            // update
            myEngine.updateMvMatrix();
            drawTroncon();
            // pop
            myEngine.mvMatrixStack.popMatrix();
            // update
            myEngine.updateMvMatrix();
        }
        // pop
        myEngine.mvMatrixStack.popMatrix();
        // update
        myEngine.updateMvMatrix();
    }

    void drawRailCurve(float orientation) {
        // TODO: orientate accordingly
    }
    
}