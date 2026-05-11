#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "draw_scene.hpp"
#include "railways.hpp"
#include "tools/shaders.hpp"
#include <iostream>
#include "nlohmann/json.hpp"
#include <iomanip>
#include <windows.h>
#include <cstdlib>

using namespace glbasimac;
using namespace STP3D;
using json = nlohmann::json;

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1200;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "The Train - SNCF";
static float aspectRatio = 1.0f;

/* modes n stuff */
auto renderMode = GL_FILL;

enum CAMERA_MODE {
    ORBITAL,
    TOP,
    FPS,
};
int cameraMode = CAMERA_MODE::ORBITAL;

bool isGridShown = false;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;


//////////////////////////////////////
/* Callbacks */
//////////////////////////////////////



/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* /*window*/, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);

	std::cerr<<"Setting 3D projection"<<std::endl;
	myEngine.set3DProjection(90.0,aspectRatio,Z_NEAR,Z_FAR);
}

void onKey(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
	int is_pressed = (action == GLFW_PRESS);

	switch(key) {
        //escape shortcut (Esc)
		case GLFW_KEY_ESCAPE :
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;

        //render toggle (R)
		case GLFW_KEY_R:
			if (is_pressed) {
                renderMode = (renderMode == GL_LINE ? GL_FILL : GL_LINE);
                glPolygonMode(GL_FRONT_AND_BACK,renderMode); //render mode
            }
			break;

        //lighting toggle (F)
		case GLFW_KEY_F:
			if (is_pressed) {
                if (myEngine.currentShader == 0) {
                    myEngine.switchToPhongShading();
                } else {
	                myEngine.switchToFlatShading();
                }
            }
			break;
        
        //grid toggle (G)
		case GLFW_KEY_G:
			if (is_pressed) {
                isGridShown = !isGridShown;
            }
			break;
        
        //camera cycle (C)
        case GLFW_KEY_C:
            if (is_pressed) {
                cameraMode = (cameraMode + 1) % 3;
                
                if (cameraMode == CAMERA_MODE::ORBITAL) {
                    camera_dist_zoom = 30.0;
                    camera_angle_x = 45.0f;
                    camera_angle_z = 25.0f;
                    camera_target_x = 0.0f;
                    camera_target_y = 0.0f;
                    camera_target_z = 0.0f;
                } else if (cameraMode == CAMERA_MODE::TOP) {
                    camera_dist_zoom = 30.0;
                    camera_angle_x = 0.0f;
                    camera_angle_z = 90.0f;
                    camera_target_x = 0.0f;
                    camera_target_y = 0.0f;
                    camera_target_z = 0.0f;
                } else if (cameraMode == CAMERA_MODE::FPS) {

                }
            }
            break;

        //Camera controls (ZSQD / WASD)
        case GLFW_KEY_W :
            if (cameraMode == CAMERA_MODE::ORBITAL) {
                camera_angle_z += 1.0;
            } else if (cameraMode == CAMERA_MODE::TOP) {
                camera_target_y += 1.0;
            } else if (cameraMode == CAMERA_MODE::FPS) {
                //TODO: move it from where you are facing
            }
            break;
        case GLFW_KEY_S :
            if (cameraMode == CAMERA_MODE::ORBITAL) {
                camera_angle_z -= 1.0;
            } else if (cameraMode == CAMERA_MODE::TOP) {
                camera_target_y -= 1.0;
            } else if (cameraMode == CAMERA_MODE::FPS) {
                //TODO: move it from where you are facing
            }
            break;
        case GLFW_KEY_D :
            if (cameraMode == CAMERA_MODE::ORBITAL) {
                camera_angle_x += 1.0;
            } else if (cameraMode == CAMERA_MODE::TOP) {
                camera_target_x += 1.0;
            } else if (cameraMode == CAMERA_MODE::FPS) {
                //TODO: move it from where you are facing
            }
            break;
        case GLFW_KEY_A :
            if (cameraMode == CAMERA_MODE::ORBITAL) {
                camera_angle_x -= 1.0;
            } else if (cameraMode == CAMERA_MODE::TOP) {
                camera_target_x -= 1.0;
            } else if (cameraMode == CAMERA_MODE::FPS) {
                //TODO: move it from where you are facing
            }
        break;

        //default
		default: std::cerr<<"Touche non gérée "<<key<<std::endl;
	}
}

void onMouseButton(GLFWwindow* window, int button, int action, int /*mods*/)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout<<"Pressed in "<<xpos<<" "<<ypos<<std::endl;
	}
}

void onScroll(GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << yoffset <<"\n";
    camera_dist_zoom += (yoffset < 0 ? 1 : -1);
    camera_dist_zoom = std::max(Z_NEAR, std::min(camera_dist_zoom, Z_FAR)); //clamp between Z_NEAR and Z_FAR
}




//////////////////////////////////////
/* Main function */
//////////////////////////////////////



int main(int argc, char** argv)
{
    //tell Windows console to use UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
    //enable ANSI Coloring
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);



    //mute looping output of "Id VBO ..."
    MeshOutput = false;
    
    Railways railways;
    std::ifstream ifs(argv[1]); //NOTE: https://www.pointerlab.fr/blog/cpp-argc-argv
    json j = json::parse(ifs);

    //serialization
    railways.size_grid = j["size_grid"];
    railways.origin = j["origin"].get<std::vector<float>>();
    railways.path = j["path"].get<std::vector<std::vector<float>>>();
    railways.train_position = railways.origin;



    //////////////////////////////////////
    /* GLFW initialisation */
    //////////////////////////////////////



	GLFWwindow* window;
	if (!glfwInit()) return -1;

    /* Try to uncomment this for MAC OS if it did not work */
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

    std::cout<<"Loading GL extension"<<std::endl;

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}



    //////////////////////////////////////
    /* Callback init */
    //////////////////////////////////////



	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, onMouseButton);
    glfwSetScrollCallback(window, onScroll);
    


    //////////////////////////////////////
    /* Engine init */
    //////////////////////////////////////



	std::cout<<"Engine init"<<std::endl;
    myEngine.mode2D = false;
	myEngine.initGL();
	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);
	CHECK_GL;

	initScene();


    
    //////////////////////////////////////
    /* Running scene */
    //////////////////////////////////////



	double elapsedTime{0.0};

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render begins here */
		glClearColor(0.f,0.0f,0.2f,0.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        /* Fix camera position */

        if (cameraMode == CAMERA_MODE::ORBITAL) {
            myEngine.mvMatrixStack.loadIdentity();

            //camera def
            Vector3D pos_camera = Vector3D(
                camera_dist_zoom * cos(deg2rad(camera_angle_x)) * cos(deg2rad(camera_angle_z)),
                camera_dist_zoom * sin(deg2rad(camera_angle_x)) * cos(deg2rad(camera_angle_z)),
                camera_dist_zoom * sin(deg2rad(camera_angle_z))
            );
            Vector3D viewed_point = Vector3D(camera_target_x,camera_target_y,camera_target_z);
            Vector3D up_vector = Vector3D(0.0,0.0,1.0);
            Matrix4D viewMatrix = Matrix4D::lookAt(pos_camera,viewed_point,up_vector);
            //
            
            myEngine.setViewMatrix(viewMatrix);
            myEngine.updateMvMatrix();
        } else if (cameraMode == CAMERA_MODE::TOP) {
            myEngine.mvMatrixStack.loadIdentity();

            //camera def
            Vector3D pos_camera = Vector3D(camera_target_x,camera_target_y,camera_dist_zoom);
            Vector3D viewed_point = Vector3D(camera_target_x,camera_target_y,0.0f);
            Vector3D up_vector = Vector3D(0.0, 1.0, 0.0);  // Up is Y-axis (since we're looking down)
            Matrix4D viewMatrix = Matrix4D::lookAt(pos_camera, viewed_point, up_vector);
            //

            myEngine.setViewMatrix(viewMatrix);
            myEngine.updateMvMatrix();
        } else if (cameraMode == CAMERA_MODE::TOP) {
            //TODO: Don't do it yet
        }

        

        //draw the whole scene from draw_scene
        drawScene(startTime, &railways, isGridShown);

        myEngine.mvMatrixStack.loadIdentity();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}

	glfwTerminate();
	return 0;
}
