#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include "globals.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "model.h"
#include "project.h"

#include <fstream>
#include <cereal/archives/xml.hpp>
#include <cereal/types/array.hpp>

//screen settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

//timing
float deltaTime = 0.0f;
float lastTime = 0.0f;

void main() {
	//intialize GLFW & GLAD
	INIT();

	//Camera Class
	Camera camera(window, glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f, SCR_WIDTH / 2, SCR_HEIGHT / 2);
	gCamera = &camera;//update the global camera variable

	//#######################################################################################################################
	//load the model here
	Shader ourShader("Shaders/base.vs", "Shaders/base.fs");
	Model ourModel;
	Project project("SCENE/project0");

	{
		std::ifstream is("data.xml");
		cereal::XMLInputArchive archive(is);
		archive(project);
	}
	
	//projection matrix
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	PROJECTION_MATRIX = projection;
	//set projection for 3D MODEL
	ourShader.use();
	glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	//Activate IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	//project.objects[0].positionX = 0.01f;
	//update Project
	for (int i = 0; i < project.objects.size(); i++) {
		project.objects[i].updateProjection();
		project.objects[i].updateModel();
	}

	//render Loop
	glEnable(GL_DEPTH_TEST);//enable depth testing
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_CULL_FACE);
	while (!glfwWindowShouldClose(window)) {
		//get time
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//process user input
		processInput(window,deltaTime);

		//all render stuff goes here
		glClearColor(0, 0.0f, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		//set up IMGUI for rendering
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//Update view Matrix
		glm::mat4 view = glm::lookAt(gCamera->position, gCamera->position + gCamera->front, gCamera->up);
		VIEW_MATRIX = view;
		//set view for 3D MODEL
		ourShader.use();
		glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//update Project view matrix
		for (int i = 0; i < project.objects.size(); i++) {
			project.objects[i].updateView();
		}


		//draw stuff here
		
		//update and render 3D MODEL
		ourShader.use();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//ourModel.Draw(ourShader);
		for (int i = 0; i < project.objects.size(); i++) {
			project.objects[i].updateModel();
			project.objects[i].render();
		}

		//render IMGUI stuff here
		ImGui::Begin("Controls");
		//ImGui::SliderFloat("ScalingBias", &SCALING_BIAS, 0, 10);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	{
		std::ofstream os("data.xml");
		cereal::XMLOutputArchive archive(os);
		archive(CEREAL_NVP(project));
	}

	//End IMGUI here
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//exit
	glfwTerminate();
	return;
}
