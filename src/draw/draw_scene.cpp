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
        TourneHautDroite, 
        TourneHautGauche, 
        TourneBasDroite, 
        TourneBasGauche, 
        Erreur
    };

    struct position{
        int x;
        int y;
    };
    
    Direction curveOrStraight(std::vector<std::vector<float>>* path, int index){
        int nombreElement=(int)path->size(); //nombre d'éléments de path
        int previousIndex{};
        int currentIndex{};
        int nextIndex{};
        if(index==0){
            previousIndex=nombreElement-1;
            currentIndex=index;
            nextIndex=1;
        }else if(index==nombreElement-1){
            previousIndex=index-1;
            currentIndex=index;
            nextIndex=0;
        }else{
            previousIndex=index-1;
            currentIndex=index;
            nextIndex=index+1;
        }

        // Vérifie si ca tourne
        if((*path)[nextIndex][0]!=(*path)[previousIndex][0] && (*path)[nextIndex][1]!=(*path)[previousIndex][1]){
            // On sait que ca tourne maintenant on cherche à savoir dans quel sens
            position pBefore;
            position pAfter;
            // tu récupère la différence (= de combien t'as bougé) depuis 
            // celui d'avant à maintenant
            pBefore.x=(*path)[currentIndex][0]-(*path)[previousIndex][0];
            pBefore.y=(*path)[currentIndex][1]-(*path)[previousIndex][1];
            // celui de maintenant à après
            pAfter.x=(*path)[nextIndex][0]-(*path)[currentIndex][0];
            pAfter.y=(*path)[nextIndex][1]-(*path)[currentIndex][1];

            if((pAfter.x-pBefore.x==-1) && (pAfter.y-pBefore.y==-1)){
                
                return Direction::TourneHautDroite;
            }else if((pAfter.x-pBefore.x==1) && (pAfter.y-pBefore.y==-1)){
                
                return Direction::TourneHautGauche;
            }else if((pAfter.x-pBefore.x==1) && (pAfter.y-pBefore.y==1)){
                
                return Direction::TourneBasGauche;
            }else if((pAfter.x-pBefore.x==-1) && (pAfter.y-pBefore.y==1)){
                
                return Direction::TourneBasDroite;
            }
        }else if((*path)[currentIndex][0]==(*path)[previousIndex][0] && (*path)[currentIndex][0]==(*path)[nextIndex][0]){ // Vérifie si c'est Vertical en x 
            return Direction::Horizontal;
        }else if((*path)[currentIndex][1]==(*path)[previousIndex][1] && (*path)[currentIndex][1]==(*path)[nextIndex][1]){
            return Direction::Vertical;
        }

        return Direction::Erreur;
    }
    void drawTrainAndPath(std::vector<std::vector<float>>* path,float time) {
        //TODO: place the rails according to the path
        STP3D::Vector3D axeRotationY(0,1,0);
        STP3D::Vector3D axeRotationX(1,0,0);
        for (size_t i{0};i<path->size();i++) {
            int index=static_cast<int>(i);

            Direction dir = curveOrStraight(path, index);

            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin((*path)[index][0]*cell_size, 0, (*path)[index][1]*cell_size);

                if(dir==Direction::Horizontal){
                    if(index==0){
                        myEngine.mvMatrixStack.pushMatrix();
                            moveOrigin((cell_size-rails_out_l)/2, (rr*2) + sr, 0);
                            myEngine.mvMatrixStack.addRotation(90, axeRotationY); // ←→ donc 90°
                            drawTrain(time);
                        myEngine.mvMatrixStack.popMatrix();
                    }
                    drawRailStraight(180);
                }
                else if(dir==Direction::Vertical){
                    if(index==0){
                        myEngine.mvMatrixStack.pushMatrix();
                            moveOrigin((cell_size-rails_out_l)/2, (rr*2) + sr, 0);
                            myEngine.mvMatrixStack.addRotation(0, axeRotationY); // ↑↓ donc 0°
                            drawTrain(time);
                        myEngine.mvMatrixStack.popMatrix();
                    }
                    drawRailStraight(90);
                }
                else if(dir==Direction::TourneHautDroite || dir==Direction::TourneHautGauche || dir==Direction::TourneBasDroite || dir==Direction::TourneBasGauche){

                    float angle = 0;

                    if (dir==Direction::TourneHautDroite) {
                        angle = 0;
                    } 
                    else if (dir==Direction::TourneHautGauche) {
                        angle = 270;
                    } 
                    else if (dir==Direction::TourneBasDroite) {
                        // I<-
                        angle = 90;
                    }
                    else if (dir==Direction::TourneBasGauche) {

                        angle = 180;
                    }
                    drawRailCurve(angle);
                }
            myEngine.mvMatrixStack.popMatrix();
            
        }
        //TODO: at the start of the path draw the train, unlike now
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