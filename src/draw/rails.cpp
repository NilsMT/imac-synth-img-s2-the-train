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
        Vector3D axeRotation(0.,1,0.);
        myEngine.mvMatrixStack.addRotation(angleRadiant,axeRotation);
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
    
    void drawCubeRail(){
        float section_size = sr;
        // push	
        myEngine.mvMatrixStack.pushMatrix();
        // Vector3D translationRail3{POS_X_RAIL1,10,0};
        // myEngine.mvMatrixStack.addTranslation(translationRail3);
            // rotation
                // update
                scaleOrigin(section_size, section_size, section_size);
                myEngine.setFlatColor(.41f,.41f,.41f);
                myEngine.updateMvMatrix();
                cube->draw();
        // pop
        myEngine.mvMatrixStack.popMatrix();
        // update
        myEngine.updateMvMatrix();
    }
    
    void drawLittleRail(float orientation) {
        // TODO: orientate accordingly
        float angleRadiant{};
        angleRadiant=deg2rad(orientation);
        myEngine.setFlatColor(.41f,.41f,.41f);

        myEngine.mvMatrixStack.pushMatrix();
            // on se place au centre de la grille pour la rotation
            myEngine.mvMatrixStack.addTranslation({5,0,5});
            Vector3D axeRotation(0.,1,0.);
            myEngine.mvMatrixStack.addRotation(angleRadiant,axeRotation);
            myEngine.mvMatrixStack.addTranslation({-5,0,-5});
            // update
            myEngine.updateMvMatrix();

        // Premier PAVE
        // push	
        myEngine.mvMatrixStack.pushMatrix();
            Vector3D translationRail1{POS_X_RAIL1,10+rr+(sr/2),sx+rr};
            myEngine.mvMatrixStack.addTranslation(translationRail1);
            // update
            myEngine.updateMvMatrix();
            drawCubeRail();
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

        // Troncon
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

    }

    void drawRailCurve(float orientation) {
        // TODO: orientate accordingly
        float angleRadiant{};
        angleRadiant=deg2rad(orientation);
        myEngine.setFlatColor(.41f,.41f,.41f);

        myEngine.mvMatrixStack.pushMatrix();
            // on se place au centre de la grille pour la rotation
            myEngine.mvMatrixStack.addTranslation({5,0,5});
            Vector3D axeRotation(0.,1,0.);
            myEngine.mvMatrixStack.addRotation(angleRadiant,axeRotation);
            myEngine.mvMatrixStack.addTranslation({-5,0,-5});
            // update
            myEngine.updateMvMatrix();
        
        // ---------------------------------------- arc de cercle rail
        float rayon=3.;
        // Précision du cercle, plus ou moins lisse
        int precision=50;
        for (int i = 0; i < precision ; i++)
        {
            float angle=M_PI/2*i/precision;
            myEngine.mvMatrixStack.pushMatrix();
                STP3D::Vector3D CercleCoordTrans(
                    rayon * cos(angle),
                    0,
                    rayon * sin(angle)
                );
                myEngine.mvMatrixStack.addTranslation(CercleCoordTrans);
                myEngine.updateMvMatrix();
                drawCubeRail();
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }
        float rayon2=7.;
        // Précision du cercle, plus ou moins lisse
        int precision2=150;
        for (int i = 0; i < precision2 ; i++)
        {
            float angle=M_PI/2*i/precision2;
            myEngine.mvMatrixStack.pushMatrix();
                STP3D::Vector3D CercleCoordTrans(
                    rayon2 * cos(angle),
                    0,
                    rayon2 * sin(angle)
                );
                myEngine.mvMatrixStack.addTranslation(CercleCoordTrans);
                myEngine.updateMvMatrix();
                drawCubeRail();
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }
        // ---------------------------------------- troncon
        float rayonTroncon=2.;
        // Précision du cercle, plus ou moins lisse
        int precisionTroncon=3;
        Vector3D rotation2(0.,1.,0.);
        myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addRotation((-M_PI/12),rotation2);
            myEngine.updateMvMatrix();
            for (int i = 0; i < precisionTroncon ; i++)
            {
                float angle=M_PI/2*i/precisionTroncon;
                myEngine.mvMatrixStack.pushMatrix();
                    // BorderRadiusCoord.push_back(rayon * cos(angle));
                    // BorderRadiusCoord.push_back(rayon * sin(angle));
                    STP3D::Vector3D TronconCoordTrans(
                        rayonTroncon * cos(angle),
                        1,
                        rayonTroncon * sin(angle)
                    );
                    myEngine.mvMatrixStack.addTranslation(TronconCoordTrans);
                    Vector3D rotation(0.,1.,0.);
                    myEngine.mvMatrixStack.addRotation(i*(-M_PI/6),rotation);
                    myEngine.updateMvMatrix();
                    drawTroncon();
                myEngine.mvMatrixStack.popMatrix();
            }
        myEngine.mvMatrixStack.popMatrix();

        // pop
        myEngine.mvMatrixStack.popMatrix();
        // update
        myEngine.updateMvMatrix();
    }
}