#include "draw_scene.hpp"

namespace Draw {
    void initScene() {

        initRail();

        sphere = basicSphere();
        sphere->createVAO();

        cube = basicCube();
        cube->createVAO();

        wedge = basicWedge();
        wedge->createVAO();

        cylinderCover = basicCylinderWithCovers(1,0.5,16);
        cylinderCover->createVAO();

        rect = basicRect(1.0,1.0);
        rect->createVAO();
    }

    enum class Direction{
        Vertical, // ↑↓
        Horizontal, // ←→
        CourbureDroite, // ↗
        CourbureGauche, // ↘
        Erreur
    };

    
    Direction curveOrStraight(std::vector<std::vector<float>>* path, int index){
        int nombreElement=(int)path->size(); //nombre d'éléments de path
        if (index<=0||index>=nombreElement-1){
            return Direction::Horizontal;
        }

        int previousIndex=index-1;
        int currentIndex=index;
        int nextIndex=index+1;

        // Vérifie si ca tourne
        if((*path)[nextIndex][0]!=(*path)[previousIndex][0] && (*path)[nextIndex][1]!=(*path)[previousIndex][1]){
            // Maintenant ca tourne mais dans quel sens?

            // si ca tourne à gauche alors x est plus petit
            if((*path)[currentIndex][0]==(*path)[nextIndex][0]){
                return Direction::CourbureGauche;
            }

            // si ca tourne à droite alors x est plus grand
            if((*path)[currentIndex][0]==(*path)[previousIndex][0]){
                return Direction::CourbureDroite;
            }

        }else if((*path)[currentIndex][0]==(*path)[previousIndex][0] && (*path)[currentIndex][0]==(*path)[nextIndex][0]){ // Vérifie si c'est Vertical en x 
            return Direction::Vertical;
        }else if((*path)[currentIndex][1]==(*path)[previousIndex][1] && (*path)[currentIndex][1]==(*path)[nextIndex][1])
        {
            return Direction::Horizontal;
        }
        // else if((*path)[currentIndex][1]!=(*path)[previousIndex][1] && (*path)[currentIndex][1]!=(*path)[nextIndex][1]){ // Vérifie si c'est Horizontal en y
        //     return Direction::Horizontal;
        // }



        return Direction::Erreur;
    }

    void drawTrainAndPath(std::vector<std::vector<float>>* path,float time) {
        //TODO: place the rails according to the path

        int previousIndex{0};
        int currentIndex{0};
        int nextIndex{0};
        for (std::vector<float> pos : *path) {
            previousIndex--;
            nextIndex++;
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(pos[0],0,pos[1]);
                myEngine.updateMvMatrix();
                drawRailStraight(0);
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
            currentIndex++;
        }
        //TODO: at the start of the path draw the train, unlike now
        drawTrain(time);
    }

    void drawTrees(std::vector<std::vector<float>>* trees) {
        for (std::vector<float> pos : *trees) {
            drawTree(pos[0],pos[1]);
        }
    }

    void drawScene(float time, JsonData* json_data, bool isGridShown) {
        glPointSize(10.0);

        // // Premier RAIL
        // // push	
        // myEngine.mvMatrixStack.pushMatrix();
        // Vector3D translationRail{POS_X_RAIL1,10,0};
        // myEngine.mvMatrixStack.addTranslation(translationRail);
        // // update
        // myEngine.updateMvMatrix();
        // drawRailStraight(210.);
        // drawRailCurve(0);
        // // pop
        // myEngine.mvMatrixStack.popMatrix();
        // // update
        // myEngine.updateMvMatrix();

        // // Deuxieme RAIL
        // // push	
        // myEngine.mvMatrixStack.pushMatrix();
        // Vector3D translationRail{POS_X_RAIL2,10,0};
        // myEngine.mvMatrixStack.addTranslation(translationRail);
        // // update
        // myEngine.updateMvMatrix();
        // drawRailStraight(10.);
        // // pop
        // myEngine.mvMatrixStack.popMatrix();
        // // update
        // myEngine.updateMvMatrix();
        
        ///////////////
        //base

        //the origin
        drawFrame();

        //ground grid
        if (isGridShown) {
            drawGrid((*json_data).size_grid);
        }
        
        //ground according to railways size
        drawGround((*json_data).size_grid);

        ///////////////
        //draw stuffs

        //draw trees
        drawTrees(&(json_data->trees));

        //draw path and train
        drawTrainAndPath(&(json_data->path),time);

        //place the train station
        drawTrainStation(json_data->origin[0],json_data->origin[1]);
    }
}