#include "draw_scene.hpp"

/// Camera parameters
float camera_angle_x {45.0};      // Angle between x axis and viewpoint
float camera_angle_z {30.0};      // Angle between z axis and viewpoint
float dist_zoom {30.0};      // Distance between origin and viewpoint

float sr = 1;
float sx = 1;
float rr = 1;

//for train

//1st layer
const float btwn_rails = 10.f - (2*3 + 2*sr);
const float btwn_rails_out = btwn_rails + 2*sr;
const float wheel_support_size = 3.0;
const float wheel_wedge_size = 0.25;
const float wheel_guard_size = 0.75;
const float under_wedge_size = 2.5;

//2nd layer
//accumulate size of stuff used for 1st layer
const float body_size = 
    3 * wheel_guard_size 
    + 4 * wheel_wedge_size 
    + 2 * wheel_support_size
    + under_wedge_size;
const float body_height = 2.25;
const float middle_height = 0.5;
const float body_rep[2] = {0.8f,0.2f}; //repartition between wedge and main body (%)
const float main_body_size = body_rep[0] * body_size;
const float wedge_body_size = body_rep[1] * body_size;

//3rd layer
const float top_height = 0.5;
const float wedge_top_size = 1;
const float main_top_size = 6;


GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};

IndexedMesh* sphere;
IndexedMesh* cube;
IndexedMesh* cylinder;

/* Helper functions to move, scale, rotate the origin */

void moveOrigin(float x, float y, float z) {
    myEngine.mvMatrixStack.addTranslation({x,y,z});
    myEngine.updateMvMatrix();
}

void rotateOrigin(float angle, float x, float y, float z) {
    myEngine.mvMatrixStack.addRotation(angle, {x,y,z});
    myEngine.updateMvMatrix();
}

void scaleOrigin(float x, float y, float z) {
    myEngine.mvMatrixStack.addHomothety({x,y,z});
    myEngine.updateMvMatrix();
}

void drawShapeWithColor(IndexedMesh* shape, float r, float g, float b) {
    myEngine.setFlatColor(r,g,b);
    shape->draw();
}

void drawShapeWithColor(GLBI_Convex_2D_Shape shape, float r, float g, float b) {
    myEngine.setFlatColor(r,g,b);
    shape.drawShape();
}

void initScene() {
    sphere = basicSphere();
    sphere->createVAO();

    cube = basicCube();
    cube->createVAO();

    cylinder = basicCylinder(1.f,0.5f);
    cylinder->createVAO();
}

void drawFrame() {
    std::vector<float> points {
        0.0,0.0,0.0,
        10.0,0.0,0.0,
        
        0.0,0.0,0.0,
        0.0,10.0,0.0,

        0.0,0.0,0.0,
        0.0,0.0,10.0,
    };

    std::vector<float> pointsColor = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };

    somePoints.changeNature(GL_LINES);
    somePoints.initSet(points, pointsColor);

    //NOTE: could've used createRepere() from STP3D
}

void drawGround(int size) {

    size *= 10; // make it so it can house 10x10 tiles of that size

    std::vector<float> groundBase{
        -size/2.f, -size/2.f, 0.0,
        size/2.f, -size/2.f, 0.0,
        size/2.f, size/2.f, 0.0,
        -size/2.f, size/2.f, 0.0
    };
	ground.initShape(groundBase);
	ground.changeNature(GL_TRIANGLE_FAN);
    drawShapeWithColor(ground,0.2,0.0,0.0);
}



//////////////////////////////////////
/* Train */
//////////////////////////////////////



void drawTrainWheelWedge() {
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(wheel_wedge_size/2, btwn_rails_out/2, 0.75);
        scaleOrigin(wheel_wedge_size, btwn_rails_out, 1);
        drawShapeWithColor(cube,1,0,0);
        myEngine.mvMatrixStack.popMatrix();
}

void drawTrainWheelGuard() {
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(wheel_guard_size/2, btwn_rails_out/2, 0.75);
        scaleOrigin(wheel_guard_size, btwn_rails_out, 1);
        drawShapeWithColor(cube,0,1,0);
        myEngine.mvMatrixStack.popMatrix();
}

void drawTrainUnderWedge() {
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(under_wedge_size/2, btwn_rails_out/2, 0.625);
        scaleOrigin(under_wedge_size, btwn_rails_out, 0.75);
        drawShapeWithColor(cube,1,1,1);
        myEngine.mvMatrixStack.popMatrix();
}

void drawTrainMainBody() {
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(main_body_size/2,btwn_rails_out/2,body_height/2);
        scaleOrigin(main_body_size, btwn_rails_out, body_height);
        drawShapeWithColor(cube,1,0.5,0);
        myEngine.mvMatrixStack.popMatrix();
}

void drawTrainMiddleBody() {
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(wedge_body_size/2,btwn_rails_out/2,middle_height/2);
        scaleOrigin(wedge_body_size, btwn_rails_out, middle_height);
        drawShapeWithColor(cube,0.5,0.3,0.2);
        myEngine.mvMatrixStack.popMatrix();
}

void drawTrainWedgeBody() {
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(wedge_body_size/2,btwn_rails_out/2,(body_height-middle_height)/2);
        scaleOrigin(wedge_body_size, btwn_rails_out, (body_height-middle_height));
        drawShapeWithColor(cube,1,0,0.5);
        myEngine.mvMatrixStack.popMatrix();
}

void drawTrainWedgeTop() {
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(wedge_top_size/2,btwn_rails/2,top_height/2);
        scaleOrigin(wedge_top_size, btwn_rails, top_height);
        drawShapeWithColor(cube,1,0,1);
        myEngine.mvMatrixStack.popMatrix();
}

void drawTrainMainTop() {
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(main_top_size/2,btwn_rails/2,top_height/2);
        scaleOrigin(main_top_size, btwn_rails, top_height);
        drawShapeWithColor(cube,1,1,0);
        myEngine.mvMatrixStack.popMatrix();
}

void drawTrainWheels() {
    myEngine.mvMatrixStack.pushMatrix();
        //wh1
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(1.f/2.f, 0, 1.f/2.f);
            scaleOrigin(1, sr, 1);
            drawShapeWithColor(cylinder,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();

        //wh2
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(wheel_support_size - sr/2, 0, 1.f/2.f);
            scaleOrigin(1, sr, 1);
            drawShapeWithColor(cylinder,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();

        //wh3
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(1.f/2.f, btwn_rails + sr, 1.f/2.f);
            scaleOrigin(1, sr, 1);
            drawShapeWithColor(cylinder,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();

        //wh4
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(wheel_support_size - 1.f/2.f, btwn_rails + sr, 1.f/2.f);
            scaleOrigin(1, sr, 1);
            drawShapeWithColor(cylinder,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();

        //base
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(wheel_support_size/2,(btwn_rails/2) + sr,0.75);
            scaleOrigin(wheel_support_size, btwn_rails, 1);
            drawShapeWithColor(cube,0,0,1);
            myEngine.mvMatrixStack.popMatrix();
        //end
        myEngine.mvMatrixStack.popMatrix();
}

void drawTrain(float time) {
    //TODO: draw the train
    //TODO: draw according to time, following path (later)
    //NOTE: use triangles instead of cubes (have to create it in basic_mesh.hpp)
    
    //1st layer
    myEngine.mvMatrixStack.pushMatrix();
        //guard 1
        drawTrainWheelGuard();
        moveOrigin(wheel_guard_size,0,0);

        drawTrainWheelWedge();
        moveOrigin(wheel_wedge_size,0,0);

        //wheels 1
        drawTrainWheels();
        moveOrigin(wheel_support_size,0,0);
        
        //guard 2
        drawTrainWheelWedge();
        moveOrigin(wheel_wedge_size,0,0);

        drawTrainWheelGuard();
        moveOrigin(wheel_guard_size,0,0);

        drawTrainWheelWedge();
        moveOrigin(wheel_wedge_size,0,0);

        //wheels 2
        drawTrainWheels();
        moveOrigin(wheel_support_size,0,0);

        //guard 3
        drawTrainWheelWedge();
        moveOrigin(wheel_wedge_size,0,0);

        drawTrainWheelGuard();
        moveOrigin(wheel_guard_size,0,0);

        //under wedge
        drawTrainUnderWedge();
        moveOrigin(under_wedge_size,0,0);

        myEngine.mvMatrixStack.popMatrix();

    //2nd layer
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(0,0,sr);

        //main body
        drawTrainMainBody();
        moveOrigin(main_body_size,0,0);

        //
        drawTrainMiddleBody();
        moveOrigin(0,0,middle_height);

        //wedge body
        drawTrainWedgeBody();
        moveOrigin(wedge_body_size,0,0);

        myEngine.mvMatrixStack.popMatrix();
    
    //3rd layer
    myEngine.mvMatrixStack.pushMatrix();
        moveOrigin(0,sr,sr + body_height);

        //wedge top
        drawTrainWedgeTop();
        moveOrigin(wedge_top_size,0,0);

        //main top
        drawTrainMainTop();
        moveOrigin(main_top_size,0,0);

        //wedge top
        drawTrainWedgeTop();
        moveOrigin(wedge_top_size,0,0);

        myEngine.mvMatrixStack.popMatrix();
}


//////////////////////////////////////
/* Rails */
//////////////////////////////////////



void drawRailCurve(float orientation) {
	// TODO: orientate accordingly
}

void drawRailStraight(float orientation) {
	// TODO: orientate accordingly
}


//////////////////////////////////////
/* Scene drawing */
//////////////////////////////////////



void drawScene(float time, Railways* railways) {
	glPointSize(10.0);

    /*the origin*/
    drawFrame();
    somePoints.drawSet();

    /*ground according to railways size */
    drawGround((*railways).size_grid);

    /*TODO: draw rails according to railways.path*/

    /*Train*/
    drawTrain(time);
}
