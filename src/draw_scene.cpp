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

        /*the origin*/
        drawFrame();

        /* ground grid */
        if (isGridShown) {
            drawGrid((*railways).size_grid);
        }

        /*ground according to railways size */
        drawGround((*railways).size_grid);

        /*TODO: draw rails according to railways.path*/

        /*Train*/
        //drawTrain(time);

        /*Train Station*/
        drawTrainStation();
    }
}