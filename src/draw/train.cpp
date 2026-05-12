#include "train.hpp"

namespace Draw {
    //////////////////////////////////////
    /* Train settings */
    //////////////////////////////////////

    //1st layer
    const float btwn_rails = cell_size - (2*3 + 2*sr); //distance between rails (excluded)
    const float btwn_rails_out = btwn_rails + 2*sr; //distance between rails (included)
    const float wheel_support_size = 3.0; //size of wheel supports
    const float wheel_wedge_size = 0.25; //length of wheel wedges
    const float wheel_guard_size = 0.75; //length of wheel guard
    const float under_wedge_size = 2.5; //length of front under wedge

    //2nd layer
    //accumulated size of stuff used for 1st layer
    const float body_size = 
        3 * wheel_guard_size 
        + 4 * wheel_wedge_size 
        + 2 * wheel_support_size
        + under_wedge_size;
    const float body_height = 2.25; //height of main body
    const float middle_height = 0.5; //height of middle part (between two wedge at front)
    const float body_rep[2] = {0.7f,0.3f}; //repartition between wedge and main body (%)
    const float main_body_size = body_rep[0] * body_size; //length of main body
    const float wedge_body_size = body_rep[1] * body_size; //length of front wedge

    //3rd layer
    const float top_height = 0.5; //top height
    const float wedge_top_size = 1; //length of top wedges
    const float main_top_size = 6; //length of top main

    //infos
    const float z_ratio = cell_size/body_size;



    //////////////////////////////////////
    /* Functions */
    //////////////////////////////////////



    // 1st layer
    void drawTrainWheelWedge(float angle = 0.f) {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails_out / 2, 0.625, wheel_wedge_size / 2);
            rotateOrigin(angle,0,1,0);
            rotateOrigin(deg2rad(180),0,0,1);
            scaleOrigin(btwn_rails_out, 0.75, wheel_wedge_size);
            drawShapeWithColor(wedge,1,0,0);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainWheelGuard() {

        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails_out / 2, 0.625, wheel_guard_size / 2);
            scaleOrigin(btwn_rails_out, 0.75, wheel_guard_size);
            drawShapeWithColor(cube,0,1,0);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainWheels() {
        //wheel Z ratio to be = to 1 (maintain circle shape)
        // x * r = 1, x = ? ==> x = 1/r
        const float z_ratio_wh = 1/z_ratio;

        myEngine.mvMatrixStack.pushMatrix();

            // wheel 1
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(0, 0.5, 0.5);
                scaleOrigin(sr, 1, z_ratio_wh);
                rotateOrigin(deg2rad(90),0,1,0);
                drawShapeWithColor(cylinderCover,0,0.5,1);
                myEngine.mvMatrixStack.popMatrix();
            
            // wheel 2
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(btwn_rails + sr, 0.5, 0.5);
                scaleOrigin(sr, 1, z_ratio_wh);
                rotateOrigin(deg2rad(90),0,1,0);
                drawShapeWithColor(cylinderCover,0,0.5,1);
                myEngine.mvMatrixStack.popMatrix();
            
            // wheel 3
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(0, 0.5, wheel_support_size - 0.5);
                scaleOrigin(sr, 1, z_ratio_wh);
                rotateOrigin(deg2rad(90),0,1,0);
                drawShapeWithColor(cylinderCover,0,0.5,1);
                myEngine.mvMatrixStack.popMatrix();

            // wheel 4
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(btwn_rails + sr, 0.5, wheel_support_size - 0.5);
                scaleOrigin(sr, 1, z_ratio_wh);
                rotateOrigin(deg2rad(90),0,1,0);
                drawShapeWithColor(cylinderCover,0,0.5,1);
                myEngine.mvMatrixStack.popMatrix();

            // base
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin((btwn_rails / 2) + sr, 0.75, wheel_support_size / 2);
                scaleOrigin(btwn_rails, 1, wheel_support_size);
                drawShapeWithColor(cube,0,0,1);
                myEngine.mvMatrixStack.popMatrix();
            
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainUnderWedge() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails_out / 2, 0.625, under_wedge_size / 2);
            rotateOrigin(deg2rad(180),0,0,1);
            scaleOrigin(btwn_rails_out, 0.75, under_wedge_size);
            drawShapeWithColor(wedge,1,1,1);
            myEngine.mvMatrixStack.popMatrix();
    }

    //////////////////////////////////////
    // 2nd layer

    void drawTrainMainBody() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails_out / 2, body_height / 2, main_body_size / 2);
            scaleOrigin(btwn_rails_out, body_height, main_body_size);
            drawShapeWithColor(cube,1,0.5,0);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainMiddleBody() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails_out / 2, middle_height / 2, wedge_body_size / 2);
            scaleOrigin(btwn_rails_out, middle_height, wedge_body_size);
            drawShapeWithColor(cube,0.5,0.3,0.2);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainWedgeBody() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails_out / 2, (body_height - middle_height) / 2, wedge_body_size / 2);
            scaleOrigin(
                btwn_rails_out, body_height - middle_height, wedge_body_size);
            drawShapeWithColor(wedge,1,0,0.5);
            myEngine.mvMatrixStack.popMatrix();
    }



    //////////////////////////////////////
    // 3rd layer

    void drawTrainWedgeTop(float angle = 0.f) {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails / 2, top_height / 2, wedge_top_size / 2);
            rotateOrigin(angle,0,1,0);
            scaleOrigin(btwn_rails, top_height,  wedge_top_size);
            drawShapeWithColor(wedge,1,0,1);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainMainTop() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails / 2, top_height / 2,  main_top_size / 2);
            scaleOrigin(btwn_rails, top_height, main_top_size);
            drawShapeWithColor(cube,1,1,0);
            myEngine.mvMatrixStack.popMatrix();
    }



    //////////////////////////////////////
    // Full Train

    void drawTrain(float time) {
        myEngine.mvMatrixStack.pushMatrix();
            scaleOrigin(1, 1, z_ratio); //size Z so it fit grid cell size
             
            //////////////////////////////////
            // 1st layer
            //////////////////////////////////

            myEngine.mvMatrixStack.pushMatrix();
                // guard 1
                drawTrainWheelGuard();
                moveOrigin(0,0,wheel_guard_size);

                drawTrainWheelWedge();
                moveOrigin(0,0,wheel_wedge_size);

                // wheels 1
                drawTrainWheels();
                moveOrigin(0,0,wheel_support_size);

                // guard 2
                drawTrainWheelWedge(deg2rad(180));
                moveOrigin(0,0,wheel_wedge_size);

                drawTrainWheelGuard();
                moveOrigin(0,0,wheel_guard_size);

                drawTrainWheelWedge();
                moveOrigin(0,0,wheel_wedge_size);

                // wheels 2
                drawTrainWheels();
                moveOrigin(0,0,wheel_support_size);

                // guard 3
                drawTrainWheelWedge(deg2rad(180));
                moveOrigin(0,0,wheel_wedge_size);

                drawTrainWheelGuard();
                moveOrigin(0,0,wheel_guard_size);

                // under wedge
                drawTrainUnderWedge();
                moveOrigin(0,0,under_wedge_size);

                myEngine.mvMatrixStack.popMatrix();


            //////////////////////////////////
            // 2nd layer
            //////////////////////////////////

            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(0,sr,0);

                // main body
                drawTrainMainBody();
                moveOrigin(0,0,main_body_size);

                // middle body
                drawTrainMiddleBody();
                moveOrigin(0,middle_height,0);

                // wedge body
                drawTrainWedgeBody();
                moveOrigin(0,0,wedge_body_size);

                myEngine.mvMatrixStack.popMatrix();


            //////////////////////////////////
            // 3rd layer
            //////////////////////////////////

            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(sr, sr + body_height, 0);

                // wedge top
                drawTrainWedgeTop(deg2rad(180));
                moveOrigin(0,0,wedge_top_size);

                // main top
                drawTrainMainTop();
                moveOrigin(0,0,main_top_size);

                // wedge top
                drawTrainWedgeTop();
                moveOrigin(0,0,wedge_top_size);

                myEngine.mvMatrixStack.popMatrix();
            myEngine.mvMatrixStack.popMatrix();
    }
}