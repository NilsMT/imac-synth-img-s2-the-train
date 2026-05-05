#include "draw_scene.hpp"

/// Camera parameters
float camera_angle_x {45.0};      // Angle between x axis and viewpoint
float camera_angle_z {30.0};      // Angle between z axis and viewpoint
float dist_zoom {30.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};

IndexedMesh* sphere;
IndexedMesh* cube;

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
}

void drawGround(int size) {
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
}

void drawRailCurve(float orientation) {
	// TODO: orientate accordingly
}

void drawRailStraight(float orientation) {
	// TODO: orientate accordingly
}

void drawScene(float time,Railways railways) {
	glPointSize(10.0);

    /*the origin*/
    drawFrame();
    somePoints.drawSet();

    /*example : rotating sun thing*/
    myEngine.mvMatrixStack.pushMatrix();
        rotateOrigin(time,0,0,1);
        moveOrigin(4,0,5);
        scaleOrigin(3,3,3);
        drawShapeWithColor(sphere,1,1,0);
        myEngine.mvMatrixStack.popMatrix();

    myEngine.updateMvMatrix();

    /*ground according to railways size */
    drawGround(railways.size_grid);

    /*TODO: draw rails according to railways.path*/

    /*Train*/
    drawTrain(time);
}
