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

    void drawScene(float time, Railways* railways, bool isGridShown) {
        glPointSize(10.0);

        //the origin
        drawFrame();

        //ground grid
        if (isGridShown) {
            drawGrid((*railways).size_grid);
        }

        //ground according to railways size
        drawGround((*railways).size_grid);

        //TODO: draw rails and train according to railways.path
        myEngine.mvMatrixStack.pushMatrix();
            drawTrainAndPath(railways,time);
            myEngine.mvMatrixStack.popMatrix();

        //place the train station
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(
                railways->origin[0]*cell_size,
                0,
                railways->origin[1]*cell_size
            );
            drawTrainStation();
            myEngine.mvMatrixStack.popMatrix();
    }

    void drawTrainAndPath(Railways* railways,float time) {
        //TODO: place the rails according to the path
        
        //TODO: at the start of the path draw the train, unlike now
        drawTrain(time);
    }
}