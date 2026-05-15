#include "train.hpp"

namespace Draw {
    //////////////////////////////////////
    /* Train settings */
    //////////////////////////////////////

    //1st layer
    const float wheel_support_l = 3.0; //size of wheel supports
    const float wheel_wedge_l = 0.25; //length of wheel wedges
    const float wheel_guard_l = 0.75; //length of wheel guard
    const float under_wedge_l = 2.5; //length of front under wedge

    //2nd layer
    //accumulated size of stuff used for 1st layer (= length of 2nd layer)
    const float body_l = 
        3 * wheel_guard_l 
        + 4 * wheel_wedge_l 
        + 2 * wheel_support_l
        + under_wedge_l;
    const float body_h = 2.25; //height of 2nd layer
    const float body_mid_h = 0.5; //height of middle part (between two wedge at front)
    const float body_r[2] = {0.7f,0.3f}; //repartition between wedge and main body (%)
    const float body_main_l = body_r[0] * body_l; //length of main body
    const float body_wedge_l = body_r[1] * body_l; //length of front wedge

    //3rd layer
    const float top_h = 0.5; //top height
    const float top_wedge_l = 1; //length of top wedges
    const float top_main_l = 6; //length of top main

    //infos
    const float z_ratio = cell_size/body_l;
    const float rails_l = cell_size - (2*3 + 2*sr); //distance between rails (excluded)
    const float rails_out_l = rails_l + 2*sr; //distance between rails (included)


    //////////////////////////////////////
    /* Functions */
    //////////////////////////////////////



    // 1st layer
    void drawTrainWheelWedge(float angle = 0.f) {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(rails_out_l / 2, 0.625, wheel_wedge_l / 2);
            rotateOrigin(angle, 0, 1, 0);
            rotateOrigin(deg2rad(180), 0, 0, 1);
            scaleOrigin(rails_out_l, 0.75, wheel_wedge_l);
            drawShapeWithColor(wedge, 255, 0, 0);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainWheelGuard() {

        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(rails_out_l / 2, 0.625, wheel_guard_l / 2);
            scaleOrigin(rails_out_l, 0.75, wheel_guard_l);
            drawShapeWithColor(cube, 0, 255, 0);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainWheels() {
        //wheel Z ratio to be = to 1 (maintain circle shape)
        // x * r = 1, x = ? ==> x = 1/r
        const float z_ratio_wh = 1/z_ratio;
        const float r_h = z_ratio_wh/2;

        myEngine.mvMatrixStack.pushMatrix();

            // wheel 1
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(0, 0.5, r_h);
                scaleOrigin(sr, 1, z_ratio_wh);
                rotateOrigin(deg2rad(90), 0, 1, 0);
                drawShapeWithColor(cylinderCover, 0, 128, 255);
                myEngine.mvMatrixStack.popMatrix();
            
            // wheel 2
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(rails_l + sr, 0.5, r_h);
                scaleOrigin(sr, 1, z_ratio_wh);
                rotateOrigin(deg2rad(90), 0, 1, 0);
                drawShapeWithColor(cylinderCover, 0, 128, 255);
                myEngine.mvMatrixStack.popMatrix();
            
            // wheel 3
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(0, 0.5, wheel_support_l - r_h);
                scaleOrigin(sr, 1, z_ratio_wh);
                rotateOrigin(deg2rad(90), 0, 1 ,0);
                drawShapeWithColor(cylinderCover, 0, 128, 255);
                myEngine.mvMatrixStack.popMatrix();

            // wheel 4
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(rails_l + sr, 0.5, wheel_support_l - r_h);
                scaleOrigin(sr, 1, z_ratio_wh);
                rotateOrigin(deg2rad(90), 0, 1, 0);
                drawShapeWithColor(cylinderCover, 0, 128, 255);
                myEngine.mvMatrixStack.popMatrix();

            // base
            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin((rails_l / 2) + sr, 0.75, wheel_support_l / 2);
                scaleOrigin(rails_l, 1, wheel_support_l);
                drawShapeWithColor(cube, 0, 0, 255);
                myEngine.mvMatrixStack.popMatrix();
            
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainUnderWedge() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(rails_out_l / 2, 0.625, under_wedge_l / 2);
            rotateOrigin(deg2rad(180), 0, 0, 1);
            scaleOrigin(rails_out_l, 0.75, under_wedge_l);
            drawShapeWithColor(wedge, 255, 255, 255);
            myEngine.mvMatrixStack.popMatrix();
    }

    //////////////////////////////////////
    // 2nd layer

    void drawTrainMainBody() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(rails_out_l / 2, body_h / 2, body_main_l / 2);
            scaleOrigin(rails_out_l, body_h, body_main_l);
            drawShapeWithColor(cube, 255, 128, 0);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainMiddleBody() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(rails_out_l / 2, body_mid_h / 2, body_wedge_l / 2);
            scaleOrigin(rails_out_l, body_mid_h, body_wedge_l);
            drawShapeWithColor(cube, 128, 75, 50);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainWedgeBody() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(rails_out_l / 2, (body_h - body_mid_h) / 2, body_wedge_l / 2);
            scaleOrigin(
                rails_out_l, body_h - body_mid_h, body_wedge_l);
            drawShapeWithColor(wedge, 255, 0, 128);
            myEngine.mvMatrixStack.popMatrix();
    }



    //////////////////////////////////////
    // 3rd layer

    void drawTrainWedgeTop(float angle = 0.f) {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(rails_l / 2, top_h / 2, top_wedge_l / 2);
            rotateOrigin(angle, 0, 255, 0);
            scaleOrigin(rails_l, top_h,  top_wedge_l);
            drawShapeWithColor(wedge, 255, 0, 255);
            myEngine.mvMatrixStack.popMatrix();
    }


    void drawTrainMainTop() {
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(rails_l / 2, top_h / 2,  top_main_l / 2);
            scaleOrigin(rails_l, top_h, top_main_l);
            drawShapeWithColor(cube, 255, 255, 0);
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
                moveOrigin(0, 0, wheel_guard_l);

                drawTrainWheelWedge();
                moveOrigin(0, 0, wheel_wedge_l);

                // wheels 1
                drawTrainWheels();
                moveOrigin(0, 0, wheel_support_l);

                // guard 2
                drawTrainWheelWedge(deg2rad(180));
                moveOrigin(0, 0, wheel_wedge_l);

                drawTrainWheelGuard();
                moveOrigin(0, 0, wheel_guard_l);

                drawTrainWheelWedge();
                moveOrigin(0, 0, wheel_wedge_l);

                // wheels 2
                drawTrainWheels();
                moveOrigin(0, 0, wheel_support_l);

                // guard 3
                drawTrainWheelWedge(deg2rad(180));
                moveOrigin(0, 0, wheel_wedge_l);

                drawTrainWheelGuard();
                moveOrigin(0, 0, wheel_guard_l);

                // under wedge
                drawTrainUnderWedge();
                moveOrigin(0, 0, under_wedge_l);

                myEngine.mvMatrixStack.popMatrix();


            //////////////////////////////////
            // 2nd layer
            //////////////////////////////////

            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(0, sr, 0);

                // main body
                drawTrainMainBody();
                moveOrigin(0, 0, body_main_l);

                // middle body
                drawTrainMiddleBody();
                moveOrigin(0, body_mid_h, 0);

                // wedge body
                drawTrainWedgeBody();
                moveOrigin(0, 0, body_wedge_l);

                myEngine.mvMatrixStack.popMatrix();


            //////////////////////////////////
            // 3rd layer
            //////////////////////////////////

            myEngine.mvMatrixStack.pushMatrix();
                moveOrigin(sr, sr + body_h, 0);

                // wedge top
                drawTrainWedgeTop(deg2rad(180));
                moveOrigin(0, 0, top_wedge_l);

                // main top
                drawTrainMainTop();
                moveOrigin(0, 0, top_main_l);

                // wedge top
                drawTrainWedgeTop();
                moveOrigin(0, 0, top_wedge_l);

                myEngine.mvMatrixStack.popMatrix();
            myEngine.mvMatrixStack.popMatrix();
    }
}