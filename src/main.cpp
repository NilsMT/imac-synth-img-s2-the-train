#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <cstdlib>

#include "nlohmann/json.hpp"
#include "tools/shaders.hpp"
#include "draw_scene.hpp"
#include "railways.cpp"
#include "camera.cpp"

using namespace glbasimac;
using namespace STP3D;
using namespace Draw;
using json = nlohmann::json;

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
    // Poll WASD keys every frame
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (cameraMode == CAMERA_MODE::ORBITAL) pitch += 1.0;
        else if (cameraMode == CAMERA_MODE::TOP) camera_target_z += 1.0;
        // FPS mode TODO
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (cameraMode == CAMERA_MODE::ORBITAL) pitch -= 1.0;
        else if (cameraMode == CAMERA_MODE::TOP) camera_target_z -= 1.0;
        // FPS mode TODO
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (cameraMode == CAMERA_MODE::ORBITAL) yaw -= 1.0;
        else if (cameraMode == CAMERA_MODE::TOP) camera_target_x -= 1.0;
        // FPS mode TODO
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (cameraMode == CAMERA_MODE::ORBITAL) yaw += 1.0;
        else if (cameraMode == CAMERA_MODE::TOP) camera_target_x += 1.0;
        // FPS mode TODO
    }
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
                resetCamera();
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

void onCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    if (cameraMode == CAMERA_MODE::FPS) {
        double nxpos,nypos;
        glfwGetCursorPos(window, &nxpos, &nypos);
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



    std::ifstream ifs(argv[1]); //NOTE: https://www.pointerlab.fr/blog/cpp-argc-argv
    json data = json::parse(ifs);

    //serialization

    Railways railways = {
        data["size_grid"],
        data["origin"].get<std::vector<float>>(),
        data["path"].get<std::vector<std::vector<float>>>()
    };


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
		glClearColor(0.f,0.0f,0.2f,0.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        /* Fix camera position */
        myEngine.mvMatrixStack.loadIdentity();

        //camera definition depending on the mode
        Vector3D pos_camera = {};
        Vector3D viewed_point = {};
        Vector3D up_vector = {};

        if (cameraMode == CAMERA_MODE::ORBITAL) {
            //clamp to avoid inversion
            if (pitch < 0.0f) pitch = 0.0f;
            if (pitch > 89.0f) pitch = 89.0f;

            pos_camera = Vector3D(
                camera_dist_zoom * sin(deg2rad(yaw)) * cos(deg2rad(pitch)),
                camera_dist_zoom * sin(deg2rad(pitch)),
                -camera_dist_zoom * cos(deg2rad(yaw)) * cos(deg2rad(pitch))
            );

            viewed_point = Vector3D(camera_target_x, camera_target_y, camera_target_z);
            up_vector = Vector3D(0.0, 1.0, 0.0);  // Y is up
        } else if (cameraMode == CAMERA_MODE::TOP) {
            pos_camera = Vector3D(
                camera_target_x,
                camera_dist_zoom,
                camera_target_z
            );

            viewed_point = Vector3D(camera_target_x, camera_target_y, camera_target_z);
            up_vector = Vector3D(0.0, 0.0, 1.0);  // Z is up
        } else if (cameraMode == CAMERA_MODE::FPS) {
            //TODO: FPS camera
        }
        //
        Matrix4D viewMatrix = Matrix4D::lookAt(pos_camera, viewed_point, up_vector);
        myEngine.setViewMatrix(viewMatrix);
        myEngine.updateMvMatrix();

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
