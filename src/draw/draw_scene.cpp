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

    //vector 2 struct because somehow it doesnt exist anywhere
    struct Vector2D {
        float x;
        float y;
    };
    //operator to substract 2 vectors
    Vector2D operator-(Vector2D const& a, Vector2D const& b) {
        return Vector2D{a.x - b.x, a.y - b.y};
    };

    void drawTrainAndPath(std::vector<std::vector<float>>* path,float time) {
        Vector2D from = {0,0};
        Vector2D to = {0,0};
        Vector2D diff = {0,0};

        for (int i = 0; i < path->size() ; i++) {
            myEngine.mvMatrixStack.pushMatrix();
                //move
                moveOrigin(path->at(i)[0] * cell_size, 0, path->at(i)[1] * cell_size);

                //////////////////////////////// compute which to draw

                //compute previous index
                int pi = i - 1;
                if (pi < 0) {
                    pi = path->size() - 1;
                }
                //compute next index
                int ni = i + 1;
                if (ni == path->size()) {
                    ni = 0;
                }

                //get list item
                std::vector<float> previousItem = path->at(pi);
                std::vector<float> currentItem = path->at(i);
                std::vector<float> nextItem = path->at(ni);

                //turn into vec 2
                Vector2D previousVec = {previousItem[0],previousItem[1]};
                Vector2D currentVec = {currentItem[0],currentItem[1]};
                Vector2D nextVec = {nextItem[0],nextItem[1]};

                //get directions
                //math done here : 
                //https://docs.google.com/spreadsheets/d/1QJlc2Z5o94UKLjpInkGRVyG_sochw3V4qGe0CShq4cE/edit?usp=sharing
                from = currentVec - previousVec;
                to = nextVec - currentVec;
                diff = to - from;

                //////////////////////////////// draw

                if (diff.x == 0 && diff.y == 0) { //case we got one direction : rail straight
                    if (to.x !=0) {
                        //std::cout << "═\n";
                        drawRailStraight(90);
                    } else if (to.y !=0) {
                        //std::cout << "║\n";
                        drawRailStraight(0);
                    } else {
                        std::cerr << "Erreur : rail droit infaisable\n";
                        std::cout << " from x: " << from.x << " y: " << from.y << "\n";
                        std::cout << " to x: " << to.x << " y: " << to.y << "\n";
                        std::cout << " diff x: " << diff.x << " y: " << diff.y << "\n";
                        std::cout << "===================\n";
                    };
                } else { //case we got two direction : rail turn
                    if (diff.x == 1 && diff.y == 1) {
                        //std::cout << "╝\n";
                        drawRailCurve(180);
                    } else if (diff.x == 1 && diff.y == -1) {
                        //std::cout << "╗\n";
                        drawRailCurve(270);
                    } else if (diff.x == -1 && diff.y == 1) {
                        //std::cout << "╚\n";
                        drawRailCurve(90);
                    } else if (diff.x == -1 && diff.y == -1) {
                        //std::cout << "╔\n";
                        drawRailCurve(0);
                    } else {
                        std::cerr << "Erreur : rail courbé infaisable\n";
                        std::cout << " from x: " << from.x << " y: " << from.y << "\n";
                        std::cout << " to x: " << to.x << " y: " << to.y << "\n";
                        std::cout << " diff x: " << diff.x << " y: " << diff.y << "\n";
                        std::cout << "===================\n";
                    }
                }
            myEngine.mvMatrixStack.popMatrix();
        }
        
        //move train to start of path

        if (path->size() <= 0) {
            std::cerr << "Erreur : Pas de parcours\n";
        } else {
            myEngine.mvMatrixStack.pushMatrix();
                //move to start of path
                moveOrigin(path->at(0)[0] * cell_size, 0, path->at(0)[1] * cell_size);
                //center train (spawn at x=0, need to move to center of cell)
                moveOrigin((cell_size-rails_out_l)/2, (rr*2) + sr, 0);
                drawTrain(time);
                myEngine.mvMatrixStack.popMatrix();  
        }
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