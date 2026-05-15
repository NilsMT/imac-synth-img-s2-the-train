#include "train_station.hpp"

namespace Draw {
    float plateform_height = 1.0f;
    float cross_width = cell_size - 6.0f;
    float cross_lenght = cell_size - 2.0f;
    float cross_height = 3.0f;
    float roof_height = 4.0f;

    const float mid = cell_size/2;
    const float plate = (sr+rr+plateform_height);

    void drawStationBase() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(mid, plate/2, mid);
            scaleOrigin(cell_size, plate, cell_size);
            drawShapeWithColor(cube, 50, 50, 50);
            myEngine.mvMatrixStack.popMatrix();
    }

    void drawStationCross() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(mid, plate, mid);
            moveOrigin(0, cross_height/2, 0);
            //1st cross
            myEngine.mvMatrixStack.pushMatrix();
                scaleOrigin(cross_width, cross_height, cross_lenght);
                drawShapeWithColor(cube, 214, 96, 45);
                myEngine.mvMatrixStack.popMatrix();
            //2nd cross
            myEngine.mvMatrixStack.pushMatrix();
                scaleOrigin(cross_lenght, cross_height, cross_width);
                drawShapeWithColor(cube, 214, 96, 45);
                myEngine.mvMatrixStack.popMatrix();
            myEngine.mvMatrixStack.popMatrix();
    }

    void drawStationRoof() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(mid, plate+cross_height, mid);
            //1st roof
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin((cross_width+2)/4, roof_height/4, 0);
                //1st part
                myEngine.mvMatrixStack.pushMatrix();
                    rotateOrigin(deg2rad(90), 0, 1,0);
                    scaleOrigin(cross_lenght+2, roof_height/2, (cross_width+2)/2);
                    drawShapeWithColor(wedge, 25, 25, 25);
                    myEngine.mvMatrixStack.popMatrix();
                //2nd part
                myEngine.mvMatrixStack.pushMatrix();
                    moveOrigin(-(cross_width+2)/2, 0, 0);
                    rotateOrigin(deg2rad(-90), 0, 1, 0);
                    scaleOrigin(cross_lenght+2, roof_height/2, (cross_width+2)/2);
                    drawShapeWithColor(wedge, 25, 25, 25);
                    myEngine.mvMatrixStack.popMatrix();
                myEngine.mvMatrixStack.popMatrix();
            
            //2nd roof
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(0, roof_height/2, (cross_width+2)/4);
                //1st part
                myEngine.mvMatrixStack.pushMatrix();
                    scaleOrigin(cross_lenght+2, roof_height, (cross_width+2)/2);
                    drawShapeWithColor(wedge, 25, 25, 25);
                    myEngine.mvMatrixStack.popMatrix();
                //2nd part
                myEngine.mvMatrixStack.pushMatrix();
                    moveOrigin(0, 0, -(cross_width+2)/2);
                    rotateOrigin(deg2rad(-180), 0, 1, 0);
                    scaleOrigin(cross_lenght+2, roof_height, (cross_width+2)/2);
                    drawShapeWithColor(wedge, 25, 25, 25);
                    myEngine.mvMatrixStack.popMatrix();
                myEngine.mvMatrixStack.popMatrix();
            myEngine.mvMatrixStack.popMatrix();
    }

    void drawTrainStation(float x, float y) {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(x*cell_size, 0, y*cell_size);
            drawStationBase();
            drawStationCross();
            drawStationRoof();
            myEngine.mvMatrixStack.popMatrix();
    }
}