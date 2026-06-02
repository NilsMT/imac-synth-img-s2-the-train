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
    }

    void drawTrainAndPath(std::vector<std::vector<float>>* path,float time) {
        //TODO: place the rails according to the path
        
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
        drawRailCurve(0);
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

        //ground according to railways size
        drawGround((*json_data).size_grid);

        //ground grid
        if (isGridShown) {
            drawGrid((*json_data).size_grid);
        }

        ///////////////
        //draw stuffs

        //draw trees
        drawTrees(&(json_data->trees));

        //draw path and train
        // drawTrainAndPath(&(json_data->path),time);

        //place the train station
        // drawTrainStation(json_data->origin[0],json_data->origin[1]);
    }
}