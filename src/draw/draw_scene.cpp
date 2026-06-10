#include "draw_scene.hpp"

namespace Draw {
    void initScene() {
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
        CourbureDroite1, 
        CourbureGauche1, 
        CourbureDroite2, 
        CourbureGauche2, 
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

            // // si ca tourne à gauche alors x est plus petit
            // if((*path)[currentIndex][0]==(*path)[nextIndex][0]){
            //     return Direction::CourbureGauche;
            // }

            // // si ca tourne à droite alors x est plus grand
            // if((*path)[currentIndex][0]==(*path)[previousIndex][0]){
            //     return Direction::CourbureDroite;
            // }
            // si ca tourne à droite alors x est plus grand

            if((*path)[currentIndex][0]>(*path)[nextIndex][0]){
                return Direction::CourbureGauche1;
            }
            if((*path)[currentIndex][0]<(*path)[nextIndex][0]){
                return Direction::CourbureDroite1;
            }
            if((*path)[currentIndex][1]>(*path)[nextIndex][1]){
                return Direction::CourbureGauche2;
            }
            if((*path)[currentIndex][1]<(*path)[nextIndex][1]){
                return Direction::CourbureDroite2;
            }

        }else if((*path)[currentIndex][0]==(*path)[previousIndex][0] && (*path)[currentIndex][0]==(*path)[nextIndex][0]){ // Vérifie si c'est Vertical en x 
            return Direction::Horizontal;
        }else if((*path)[currentIndex][1]==(*path)[previousIndex][1] && (*path)[currentIndex][1]==(*path)[nextIndex][1]){
            return Direction::Vertical;
        }



        return Direction::Erreur;
    }
    // *********************** EXEMPLE ********************************
    // void drawTree(float x, float y) {
    //     myEngine.mvMatrixStack.pushMatrix();
    //         moveOrigin(x*cell_size, 0, y*cell_size);
    //         //trunk
    //         myEngine.mvMatrixStack.pushMatrix();
    //             moveOrigin(cell_size/2, trunk_height, cell_size/2);
    //             rotateOrigin(deg2rad(90),1,0,0);
    //             scaleOrigin(trunk_width, trunk_width, trunk_height);
    //             drawShapeWithColor(cylinderCover, 112, 62, 20);
    //             myEngine.mvMatrixStack.popMatrix();

    //         //leaves
    //         myEngine.mvMatrixStack.pushMatrix();
    //             moveOrigin(cell_size/2, trunk_height + (leave_size/2), cell_size/2);
    //             scaleOrigin(leave_size, leave_size, leave_size);
    //             drawShapeWithColor(sphere, 11, 168, 6);
    //             myEngine.mvMatrixStack.popMatrix();
    //         myEngine.mvMatrixStack.popMatrix();
    // };
    // *********************** EXEMPLE ********************************
    void drawTrainAndPath(std::vector<std::vector<float>>* path,float time) {
        //TODO: place the rails according to the path
        for (size_t i{0};i<path->size();i++) {
            int index=static_cast<int>(i);

            Direction dir = curveOrStraight(path, index);

            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin((*path)[index][0]*cell_size, 0, (*path)[index][1]*cell_size);

                if(dir==Direction::Horizontal){
                        drawRailStraight(180);
                }
                else if(dir==Direction::Vertical){
                        drawRailStraight(90);
                }
                else if(dir==Direction::CourbureDroite1 || dir==Direction::CourbureGauche1 || dir==Direction::CourbureDroite2 || dir==Direction::CourbureGauche2){
                    // ternaire, valeur de previous index est index-1 si négatif alors previous index =0
                    int previousIndex=(index>0)?index-1:0;
                    
                    bool vientDeGauche=((*path)[index][0]>(*path)[previousIndex][0]);
                    bool vientDeDroite=((*path)[index][0]<(*path)[previousIndex][0]);
                    bool vientDeHaut=((*path)[index][1]>(*path)[previousIndex][1]);
                    bool vientDeBas=((*path)[index][1]<(*path)[previousIndex][1]);

                    float angle = 0;

                    if (dir==Direction::CourbureDroite1) {
                        if (vientDeGauche)angle=180;
                        else if (vientDeHaut)angle=270;
                        else if (vientDeDroite)angle=0;
                        else if (vientDeBas)angle=90;
                    } 
                    if (dir==Direction::CourbureDroite2) {
                        if (vientDeGauche)angle=180;
                        else if (vientDeHaut)angle=270;
                        else if (vientDeDroite)angle=0;
                        else if (vientDeBas)angle=90;
                    } 
                    else if (dir==Direction::CourbureGauche1) {
                        if (vientDeGauche)angle=90;
                        else if (vientDeHaut)angle=180;
                        else if (vientDeDroite)angle=270;
                        else if (vientDeBas)angle=0;
                    }else if (dir==Direction::CourbureGauche2) {
                        if (vientDeGauche)angle=90;
                        else if (vientDeHaut)angle=180;
                        else if (vientDeDroite)angle=270;
                        else if (vientDeBas)angle=0;
                    }


                    drawRailCurve(angle);
                    
                }
            myEngine.mvMatrixStack.popMatrix();
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