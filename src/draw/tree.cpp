#include "tree.hpp"

namespace Draw {
    float trunk_height = 5;
    float trunk_width = 2;
    float leave_size = 3;

    void drawTree(float x, float y) {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(x*cell_size, 0, y*cell_size);
            //trunk
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(cell_size/2, trunk_height, cell_size/2);
                rotateOrigin(deg2rad(90),1,0,0);
                scaleOrigin(trunk_width, trunk_width, trunk_height);
                drawShapeWithColor(cylinderCover, 112, 62, 20);
                myEngine.mvMatrixStack.popMatrix();

            //leaves
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(cell_size/2, trunk_height + (leave_size/2), cell_size/2);
                scaleOrigin(leave_size, leave_size, leave_size);
                drawShapeWithColor(sphere, 11, 168, 6);
                myEngine.mvMatrixStack.popMatrix();
            myEngine.mvMatrixStack.popMatrix();
    };
}