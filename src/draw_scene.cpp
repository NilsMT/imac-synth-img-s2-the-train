#include "draw_scene.hpp"

//////////////////////////////////////
/* Camera settings */
//////////////////////////////////////

float camera_dist_zoom = 30.0;
float yaw = 0.0f; // horizontal rotation (on y)
float pitch = 10.0f; // vertical rotation (on x) 
float camera_sensitivity = 0.1f;
float camera_target_x = 0.0f;
float camera_target_y = 0.0f;
float camera_target_z = 0.0f;

//////////////////////////////////////
/* Grid settings */
//////////////////////////////////////

const float grid_cell_size = 10.0; //number of cells on X and Y

//////////////////////////////////////
/* Global units */
//////////////////////////////////////

float sr = 1;
float sx = 1;
float rr = 1;

//////////////////////////////////////
/* Train settings */
//////////////////////////////////////

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
const float body_rep[2] = {0.7f,0.3f}; //repartition between wedge and main body (%)
const float main_body_size = body_rep[0] * body_size;
const float wedge_body_size = body_rep[1] * body_size;

//3rd layer
const float top_height = 0.5;
const float wedge_top_size = 1;
const float main_top_size = 6;

//////////////////////////////////////
/* Engine stuffs */
//////////////////////////////////////

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePointsFrame(3);
GLBI_Set_Of_Points somePointsGrid(3);
GLBI_Convex_2D_Shape ground{3};

IndexedMesh* sphere;
IndexedMesh* cube;
IndexedMesh* cylinder;
IndexedMesh* wedge;
IndexedMesh* cylinderCover;



//////////////////////////////////////
/* Helpers */
//////////////////////////////////////



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



//////////////////////////////////////
/* Init */
//////////////////////////////////////



void initScene() {
    sphere = basicSphere();
    sphere->createVAO();

    cube = basicCube();
    cube->createVAO();

    cylinder = basicCylinder(1.f,0.5f);
    cylinder->createVAO();

    wedge = basicWedge();
    wedge->createVAO();

    cylinderCover = basicCylinderWithCovers(1,0.5,16);
    cylinderCover->createVAO();
}



//////////////////////////////////////
/* Frame */
//////////////////////////////////////



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

    somePointsFrame.changeNature(GL_LINES);
    somePointsFrame.initSet(points, pointsColor);

    somePointsFrame.drawSet();
}



//////////////////////////////////////
/* Ground */
//////////////////////////////////////



void drawGround(int grid_size) {

    float ground_size = grid_size * grid_cell_size; // make it so it can house N² tiles of that size

    std::vector<float> groundBase{
        -ground_size/2.f, 0.0, -ground_size/2.f,
        -ground_size/2.f, 0.0, ground_size/2.f,
        ground_size/2.f, 0.0, ground_size/2.f,
        ground_size/2.f, 0.0, -ground_size/2.f
    };
	ground.initShape(groundBase);
	ground.changeNature(GL_TRIANGLE_FAN);
    drawShapeWithColor(ground,0.2,0.0,0.0);
}



//////////////////////////////////////
/* Grid */
//////////////////////////////////////



void drawGrid(int grid_size) {
    std::vector<float> points;
    std::vector<float> pointsColor;

    float off = (grid_size * grid_cell_size) / 2.0f; //offset

    for (int i = 0; i <= grid_size * grid_cell_size; i++) {
        float inc = (i * 1.0f) - off;  //step by 1

        //= is a main grid line (every grid_cell_size units)
        bool isMainLine = (fmod(i,grid_cell_size) == 0); //fmod because gird_cell_size is float, regular mod won't work

        //line Z (front to back)
        points.push_back(-off); points.push_back(0.0); points.push_back(inc);
        points.push_back(off); points.push_back(0.0); points.push_back(inc);

        //line X (left to right)
        points.push_back(inc); points.push_back(0.0); points.push_back(-off);
        points.push_back(inc); points.push_back(0.0); points.push_back(off);

        //color
        float color = isMainLine ? 1.0f : 0.25f;
        for(int c = 0; c < 4; c++) {
            pointsColor.push_back(color);
            pointsColor.push_back(color);
            pointsColor.push_back(color);
        }
    }

    somePointsGrid.changeNature(GL_LINES);
    somePointsGrid.initSet(points, pointsColor);

    somePointsGrid.drawSet();
}


//////////////////////////////////////
/* Train */
//////////////////////////////////////



//////////////////////////////////////
/* Train - NEW COORD SYSTEM */
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
    myEngine.mvMatrixStack.pushMatrix();

        // wheel 1
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(0, 0.5, 0.5);
            scaleOrigin(sr, 1, 1);
            rotateOrigin(deg2rad(90),0,1,0);
            drawShapeWithColor(cylinderCover,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();
        
        // wheel 2
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails + sr, 0.5, 0.5);
            scaleOrigin(sr, 1, 1);
            rotateOrigin(deg2rad(90),0,1,0);
            drawShapeWithColor(cylinderCover,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();
        
        // wheel 3
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(0, 0.5, wheel_support_size - 0.5);
            scaleOrigin(sr, 1, 1);
            rotateOrigin(deg2rad(90),0,1,0);
            drawShapeWithColor(cylinderCover,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();

        // wheel 4
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(btwn_rails + sr, 0.5, wheel_support_size - 0.5);
            scaleOrigin(sr, 1, 1);
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
//////////////////////////////////////

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
//////////////////////////////////////

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
// FULL TRAIN
//////////////////////////////////////

void drawTrain(float time) {

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
    drawTrain(time);

    /*Primitive test*/
    // myEngine.mvMatrixStack.pushMatrix();
    //     moveOrigin(0,1,1);
    //     drawShapeWithColor(wedge,1,1,1);
    //     moveOrigin(0,0,2);
    //     drawShapeWithColor(cylinderCover,1,1,1);
    //     moveOrigin(0,0,2);
    //     drawShapeWithColor(cube,1,1,1);
}
