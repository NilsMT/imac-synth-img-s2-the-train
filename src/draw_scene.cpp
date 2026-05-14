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
    }

    void drawTrainAndPath(JsonData* json_data,float time) {
        //TODO: place the rails according to the path
        
        //TODO: at the start of the path draw the train, unlike now
        drawTrain(time);
    }

    void drawScene(float time, JsonData* json_data, bool isGridShown) {
        glPointSize(10.0);

        //the origin
        drawFrame();

        //ground grid
        if (isGridShown) {
            drawGrid((*json_data).size_grid);
        }

        //ground according to railways size
        drawGround((*json_data).size_grid);

        //draw path and train
        myEngine.mvMatrixStack.pushMatrix();
            drawTrainAndPath(json_data,time);
            myEngine.mvMatrixStack.popMatrix();

        //place the train station
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(
                json_data->origin[0]*cell_size,
                0,
                json_data->origin[1]*cell_size
            );
            drawTrainStation();
            myEngine.mvMatrixStack.popMatrix();
    }
}