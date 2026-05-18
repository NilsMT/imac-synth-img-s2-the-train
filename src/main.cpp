#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include <filesystem>

#include "nlohmann/json.hpp"
#include "tools/shaders.hpp"
#include "draw_scene.hpp"
#include "json_data.hpp"
#include "camera.hpp"
#include "lighting.hpp"

using namespace glbasimac;
using namespace STP3D;
using namespace Draw;
using json = nlohmann::json;
namespace fs = std::filesystem;

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1200;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "The Train - SNCF";
static float aspectRatio = 1.0f;

/* modes n stuff */
//render mode
auto renderMode = GL_FILL;

//grid
bool isGridShown = false;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;


//////////////////////////////////////
/* Interactions (callbacks) */
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

void onCameraKeys(GLFWwindow* window) {

    //////////////////////////////////////
    // FPS

    if (cameraMode == CAMERA_MODE::FPS) {
        //compute vector it will add
        //direction its looking (like orbital camera)
        float dirf_x = sin(deg2rad(yaw)) * cos(deg2rad(pitch));
        float dirf_y = sin(deg2rad(pitch));
        float dirf_z = -cos(deg2rad(yaw)) * cos(deg2rad(pitch));

        //direction right of where its looking
        //no need to have pitch
        float dirr_x = sin(deg2rad(yaw + 90.0));
        float dirr_y = 0.0f;
        float dirr_z = -cos(deg2rad(yaw + 90.0));

        //handle keys
        if (cameraMode == CAMERA_MODE::FPS) {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                camera_pos_x += dirf_x;
                camera_pos_y += dirf_y;
                camera_pos_z += dirf_z;
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                camera_pos_x -= dirf_x;
                camera_pos_y -= dirf_y;
                camera_pos_z -= dirf_z;
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                camera_pos_x += dirr_x;
                camera_pos_y += dirr_y;
                camera_pos_z += dirr_z;
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                camera_pos_x -= dirr_x;
                camera_pos_y -= dirr_y;
                camera_pos_z -= dirr_z;
            }
        }
    }

    //////////////////////////////////////
    // ORBITAL

    else if (cameraMode == CAMERA_MODE::ORBITAL) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pitch += 1.0;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pitch -= 1.0;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) yaw -= 1.0;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) yaw += 1.0;
    }

    //////////////////////////////////////
    // TOP

    else if (cameraMode == CAMERA_MODE::TOP) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera_target_z += 1.0;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera_target_z -= 1.0;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera_target_x -= 1.0;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera_target_x += 1.0;
    }
}

void onCameraMouse(double nxpos, double nypos) {
    float offset_x = nxpos - xpos;
    float offset_y = ypos - nypos;
    xpos = nxpos;
    ypos = nypos;

    float sensitivity = 0.1f;
    yaw += offset_x * sensitivity;
    pitch += offset_y * sensitivity;

    //clamp pitch to avoid inverse
    if (pitch < -89.0f) pitch = -89.0f;
    if (pitch > 89.0f) pitch = 89.0f;
};

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

                switch (cameraMode)
                {
                    case CAMERA_MODE::ORBITAL:
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                        //reset all
                        camera_dist_zoom = 30.0f;
                        yaw = 0.0f;
                        pitch = 10.0f;
                        camera_target_x = 0.0;
                        camera_target_y = 0.0;
                        camera_target_z = 0.0;
                        break;
                    case CAMERA_MODE::TOP:
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                         //how the orbital camera was setup
                        camera_target_x = camera_pos_x;
                        camera_target_y = 0.0;
                        camera_target_z = camera_pos_z;
                        break;
                    case CAMERA_MODE::FPS:
                        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                        //how the top camera was setup
                        pitch = -89.0f;
                        yaw = 180.0f;
                        break;
                    default:
                        break;
                }
            }
            break;
        case GLFW_KEY_W:
            break; //handled by the other function
        case GLFW_KEY_A:
            break; //handled by the other function
        case GLFW_KEY_S:
            break; //handled by the other function
        case GLFW_KEY_D:
            break; //handled by the other function
        //default
		default: std::cerr<<"Touche non gérée "<<key<<std::endl;
	}
}

void onCursorPos(GLFWwindow* window, double nxpos, double nypos) {
    if (cameraMode == CAMERA_MODE::FPS) {
        onCameraMouse(nxpos, nypos);
    } else {
        //to avoid have a x and y pos at 0.0 (causing a difference between switched mode frame and update one)
        xpos = nxpos;
        ypos = nypos;
    }
}

void onScroll(GLFWwindow* window, double xoffset, double yoffset) {
    if (cameraMode == CAMERA_MODE::ORBITAL || cameraMode == CAMERA_MODE::TOP)
    camera_dist_zoom -= yoffset;
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



    //////////////////////////////////////
    /* JSON Reading */
    //////////////////////////////////////

    JsonData json_data;

    //check if not enough argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    //check if not a correct file path
    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        std::cerr << "Error: File not found or unable to open: " << argv[1] << std::endl;
        return 1;
    }

    //check if it can parse it then serialize (or fail)
    try {
        json data = json::parse(ifs);
        //serialization (NOTE: ty Enguerrand <3)
        json_data = {
            data["size_grid"],
            data["origin"].get<std::vector<float>>(),
            data["path"].get<std::vector<std::vector<float>>>(),
            data["trees"].get<std::vector<std::vector<float>>>()
        };
    } catch (const json::parse_error& e) {
        std::cerr << "Error: Failed to parse JSON: " << e.what() << std::endl;
        return 1;
    }


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
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE); //for multiple keys handling
	glfwSetKeyCallback(window, onKey);
	glfwSetCursorPosCallback(window, onCursorPos);
    glfwSetScrollCallback(window, onScroll);
    


    //////////////////////////////////////
    /* Stuff init */
    //////////////////////////////////////



    //compute assets path
    //this does : <exe path>/../../assets
    assetsPath = (
        fs::path(argv[0]).parent_path() / "../assets/"
    ).string();



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
        /* Handle camera keys */
        onCameraKeys(window);

		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render begins here */
		glClearColor(0.f,0.0f,0.2f,0.0f); //sky color

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        /* Handle lighting */
        if (myEngine.currentShader == 1) { //if phong shader is used
            handleLighting(startTime);
        }

        /* Camera position */
        myEngine.mvMatrixStack.loadIdentity();

        if (cameraMode == CAMERA_MODE::ORBITAL) {
            handleOrbitalCamera();
        } else if (cameraMode == CAMERA_MODE::TOP) {
            handleTopCamera();
        } else if (cameraMode == CAMERA_MODE::FPS) {
            handleFPSCamera();
        }

        Matrix4D viewMatrix = Matrix4D::lookAt(
            Vector3D(camera_pos_x,camera_pos_y,camera_pos_z), 
            Vector3D(camera_target_x, camera_target_y, camera_target_z), 
            up_vector
        );
        myEngine.setViewMatrix(viewMatrix);
        myEngine.updateMvMatrix();

        //draw the whole scene from draw_scene
        drawScene(startTime, &json_data, isGridShown);

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
