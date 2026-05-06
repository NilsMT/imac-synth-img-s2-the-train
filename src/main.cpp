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
        //escape shortcut
		case GLFW_KEY_A :
		case GLFW_KEY_ESCAPE :
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;

        //render modes
		case GLFW_KEY_L:
			if (is_pressed) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //render lines
			break;
		case GLFW_KEY_P:
			if (is_pressed) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //render filled
            break;
        
        //orbital camera controls
        case GLFW_KEY_UP :
            camera_angle_z += 1.0;
            break;
        case GLFW_KEY_DOWN :
            camera_angle_z -= 1.0;
            break;
        case GLFW_KEY_LEFT :
            camera_angle_x += 1.0;
            break;
        case GLFW_KEY_RIGHT :
            camera_angle_x -= 1.0;
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


//////////////////////////////////////
/* Custom exception */
//////////////////////////////////////



//NOTE: from https://www.geeksforgeeks.org/cpp/how-to-throw-custom-exception-in-cpp/
class CustomException : public std::exception {
private:
    std::string message;
public:

    // Constructor accepting const char*
    CustomException(const char* msg) :
    message(msg) {}

    // Override what() method, marked
    // noexcept for modern C++
    const char* what() const noexcept {
        return message.c_str();
    }
};


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

    //NOTE: https://www.pointerlab.fr/blog/cpp-argc-argv
    if ((argc == 2 && std::string(argv[1]) == "--help") || argc == 1) {
        std::cout << "\033[33m<> sont des arguments\n\n";
        std::cout << "./main.exe --help                                 Affiche ce message\n";
        std::cout << "./main.exe <chemin/vers/un/fichier.json>          Lit le fichier JSON\033[0m\n";
        return 0;
    }

    //turn it into a premade class
    Railways railways;
    try {
        //json reading
        std::ifstream ifs(argv[1]); //lit le json

        if (!ifs) {
            throw CustomException("Erreur: Fichier inexistant ou impossible à ouvrir\n");
        }

        json j = json::parse(ifs);

        //serialization
        railways.size_grid = j["size_grid"];
        railways.origin = j["origin"].get<std::vector<float>>();
        railways.path = j["path"].get<std::vector<std::vector<float>>>();
        railways.train_position = railways.origin;
    } catch (std::exception& ex) {
        std::cout << "\033[31mUne erreur est survenu pendant la lecture du fichier JSON:\n";
        std::cout << ex.what();
        std::cout << "\033[0m";
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
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, onMouseButton);
    


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
        myEngine.mvMatrixStack.loadIdentity();
        Vector3D pos_camera = 
        Vector3D(dist_zoom*cos(deg2rad(camera_angle_x))*cos(deg2rad(camera_angle_z)),
        dist_zoom*sin(deg2rad(camera_angle_x))*cos(deg2rad(camera_angle_z)),
        dist_zoom*sin(deg2rad(camera_angle_z)));
        Vector3D viewed_point = Vector3D(0.0,0.0,0.0);
        Vector3D up_vector = Vector3D(0.0,0.0,1.0);
        Matrix4D viewMatrix = Matrix4D::lookAt(pos_camera,viewed_point,up_vector);
        myEngine.setViewMatrix(viewMatrix);
        myEngine.updateMvMatrix();

        //draw the whole scene from draw_scene
        drawScene(startTime, &railways);

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
