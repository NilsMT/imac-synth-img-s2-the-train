#include "base.hpp"

namespace Draw
{
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

    void drawGround(int grid_size) {

        float gnd = grid_size * cell_size; // make it so it can house N² tiles of that size

        myEngine.mvMatrixStack.pushMatrix();
            moveOrigin(-gnd/2,0,-gnd/2);
            scaleOrigin(gnd,1.0,gnd);
            startTextureRender("grass");
            drawShapeWithColor(rect, 128, 176, 77);
            endTextureRender("grass");
            myEngine.mvMatrixStack.popMatrix();
    }

    void drawGrid(int grid_size) {
        myEngine.mvMatrixStack.pushMatrix();

        std::vector<float> mainPoints;
        std::vector<float> mainPointsColor;
        std::vector<float> minorPoints;
        std::vector<float> minorPointsColor;

        float off = (grid_size * cell_size) / 2.0f;

        //Main lines (fit cell sizes)
        glLineWidth(3.0f); //wide stroke
        for (int i = 0; i <= grid_size * cell_size; i += cell_size) {
            float inc = (i * 1.0f) - off;

            //Z
            mainPoints.push_back(-off); mainPoints.push_back(0.01); mainPoints.push_back(inc);
            mainPoints.push_back(off); mainPoints.push_back(0.01); mainPoints.push_back(inc);

            //X
            mainPoints.push_back(inc); mainPoints.push_back(0.01); mainPoints.push_back(-off);
            mainPoints.push_back(inc); mainPoints.push_back(0.01); mainPoints.push_back(off);

            //Colors
            for (int c = 0; c < 4; c++) {
                mainPointsColor.push_back(1.0f);
                mainPointsColor.push_back(1.0f);
                mainPointsColor.push_back(1.0f);
            }
        }

        somePointsGrid.changeNature(GL_LINES);
        somePointsGrid.initSet(mainPoints, mainPointsColor);
        somePointsGrid.drawSet();

        //Minor lines (every 1 unit)
        glLineWidth(1.0f); //thin stroke
        for (int i = 0; i <= grid_size * cell_size; i++) {
            if (fmod(i, cell_size) != 0) { //skip main
                float inc = (i * 1.0f) - off;

                //Z
                minorPoints.push_back(-off); minorPoints.push_back(0.01); minorPoints.push_back(inc);
                minorPoints.push_back(off); minorPoints.push_back(0.01); minorPoints.push_back(inc);

                //X
                minorPoints.push_back(inc); minorPoints.push_back(0.01); minorPoints.push_back(-off);
                minorPoints.push_back(inc); minorPoints.push_back(0.01); minorPoints.push_back(off);

                //Colors
                for (int c = 0; c < 4; c++) {
                    minorPointsColor.push_back(0.25f);
                    minorPointsColor.push_back(0.25f);
                    minorPointsColor.push_back(0.25f);
                }
            }
        }

        somePointsGrid.changeNature(GL_LINES);
        somePointsGrid.initSet(minorPoints, minorPointsColor);
        somePointsGrid.drawSet();

        myEngine.mvMatrixStack.popMatrix();
    }
}
