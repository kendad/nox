#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "globals.h"


bool IS_MOUSE_CAPTURED = true;

GLFWwindow* window = nullptr;
Camera* gCamera = nullptr;

glm::mat4 PROJECTION_MATRIX;
glm::mat4 VIEW_MATRIX;

std::string PROJECT_NAME="SCENE/project0/";
std::vector<std::string> PROJECT_LIST;

int CURRENT_ACTIVE_PROJECT = 0;
int CURRENT_ACTIVE_OBJECT=0;
int CURRENT_ACTIVE_OBJECT_SHADER_ID = 0;
std::vector<std::string>  OBJECT_LIST;

void INIT() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window context
	GLFWwindow* _window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "[Nox]", NULL, NULL);
	if (_window == NULL) {
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return;
	}
	//update the global window variable
	window = _window;
	//make the current window in the current thread
	glfwMakeContextCurrent(window);
	//resize the window when users changes screen size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//set mouse callback
	glfwSetCursorPosCallback(window, mouse_callback);
	//set keyboard input callback
	glfwSetKeyCallback(window, keyboard_input_callback);

	//load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to init GLAD" << std::endl;
		return;
	}

	//get project file names
	get_project_list();

	//get objects name
	get_objects_list();
}

//#######################################################################################################################
// CALLBACK FUNCTIONS
//#######################################################################################################################
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window,float& deltaTime) {
	float cameraSpeed = (float)(2.5 * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	gCamera->processKeyboardInput(deltaTime);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	gCamera->processMouseMovement(xPos, yPos);
}

void keyboard_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//set mouse Cursor Mode
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		IS_MOUSE_CAPTURED = !IS_MOUSE_CAPTURED;
		if (IS_MOUSE_CAPTURED) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}
//#######################################################################################################################

void get_project_list() {
	std::ifstream project_list;
	std::string project_list_item;

	project_list.open("SCENE/project_list.txt");
	while (project_list >> project_list_item) { PROJECT_LIST.push_back(project_list_item); }
	project_list.close();

}

void get_objects_list() {
	if (OBJECT_LIST.size() > 0) { OBJECT_LIST.clear(); }

	std::ifstream object_list;
	std::string object_name;

	object_list.open(PROJECT_NAME + "object_data.txt");
	while (object_list >> object_name) { OBJECT_LIST.push_back(object_name); }
	object_list.close();
}