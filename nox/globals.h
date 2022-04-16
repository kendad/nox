#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include <string>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//window value created on intilization
extern GLFWwindow* window;

extern Camera* gCamera;

extern bool IS_MOUSE_CAPTURED;

extern glm::mat4 PROJECTION_MATRIX;
extern glm::mat4 VIEW_MATRIX;

extern std::string PROJECT_NAME;

//intialize GLFW for processing
extern void INIT();


//#######################################################################################################################
// CALLBACK FUNCTIONS
//#######################################################################################################################
//window resize callback function
extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//process user input
extern void processInput(GLFWwindow* window,float& deltaTime);
//mouse callback function
extern void mouse_callback(GLFWwindow* window, double xPos, double yPos);
//keyboard input callback function
extern void keyboard_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//#######################################################################################################################