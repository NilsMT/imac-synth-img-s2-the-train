#include "draw_scene.hpp"

/// Camera parameters
float camera_angle_x {45.0};      // Angle between x axis and viewpoint
float camera_angle_z {30.0};      // Angle between z axis and viewpoint
float dist_zoom {30.0};      // Distance between origin and viewpoint

float sr = 1;
float sx = 1;
float rr = 1;

//for train
const float btwn_rails = 10.f - (2*3 + 2*sr);
const float wheel_gap = 2.f;
const float wheel_wedge_gap;

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

void drawTrain(float time) {
    //TODO: draw the train
    //TODO: draw according to time, following path (later)


    //NOTE: wheels

    
    
    myEngine.mvMatrixStack.pushMatrix();
        drawTrainWheels();
        
}

void drawTrainWheels() {
    myEngine.mvMatrixStack.pushMatrix();
        //wh1
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(sr/2, 0, sr/2);
            scaleOrigin(sr, sr, sr);
            drawShapeWithColor(cylinder,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();

        //wh2
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(wheel_gap + sr/2, 0, sr/2);
            scaleOrigin(sr, sr, sr);
            drawShapeWithColor(cylinder,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();

        //wh3
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(sr/2, btwn_rails + sr, sr/2);
            scaleOrigin(sr, sr, sr);
            drawShapeWithColor(cylinder,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();

        //wh4
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(wheel_gap + sr/2, btwn_rails + sr, sr/2);
            scaleOrigin(sr, sr, sr);
            drawShapeWithColor(cylinder,0,0.5,1);
            myEngine.mvMatrixStack.popMatrix();

        //base
        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(0, sr*2, sr*0.75);
            moveOrigin((wheel_gap + sr)/2,0,0);
            scaleOrigin(wheel_gap + sr, btwn_rails, sr);
            drawShapeWithColor(cube,0,0,1);
            myEngine.mvMatrixStack.popMatrix();
        //end
        myEngine.mvMatrixStack.popMatrix();
}

void drawRailCurve(float orientation) {
	// TODO: orientate accordingly
}

void drawRailStraight(float orientation) {
	// TODO: orientate accordingly
}

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
