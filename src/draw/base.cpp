#include "base.hpp"

namespace Draw
{  
    
    

    //////////////////////////////////////
    /* Functions */
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

    void drawGround(int grid_size) {

        float ground_size = grid_size * cell_size; // make it so it can house N² tiles of that size

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

    void drawGrid(int grid_size) {
        std::vector<float> points;
        std::vector<float> pointsColor;

        float off = (grid_size * cell_size) / 2.0f; //offset

        for (int i = 0; i <= grid_size * cell_size; i++) {
            float inc = (i * 1.0f) - off;  //step by 1

            //= is a main grid line (every cell_size units)
            bool isMainLine = (fmod(i,cell_size) == 0); //fmod because gird_cell_size is float, regular mod won't work

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
}
