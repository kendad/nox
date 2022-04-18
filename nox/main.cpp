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
	Project project(PROJECT_NAME);
	CURRENT_ACTIVE_OBJECT_SHADER_ID = project.objects[CURRENT_ACTIVE_OBJECT].shader.ID;
	project.objects[CURRENT_ACTIVE_OBJECT].updateTextures();
	//Deserialize the data
	{
		std::ifstream dataFile;
		dataFile.open(PROJECT_NAME + "data.xml");
		if (dataFile) {//check if data.xml exists then deserialze
			std::ifstream is(PROJECT_NAME + "data.xml");
			cereal::XMLInputArchive archive(is);
			archive(project);

			for (int i = 0; i < project.objects.size(); i++) {
				project.objects[i].arrayToMatrix();
			}
		}
		dataFile.close();
	}
	
	//projection matrix
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	PROJECTION_MATRIX = projection;
	//set projection for 3D MODEL
	for (int i = 0; i < project.objects.size(); i++) {
		project.objects[i].updateProjection();
	}

	//Activate IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

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
		//update Project view matrix
		for (int i = 0; i < project.objects.size(); i++) {
			project.objects[i].updateView();
		}


		//draw stuff here
		
		//update and render 3D MODEL
		//project.objects[2].positionX = 0.01;
		for (int i = 0; i < project.objects.size(); i++) {
			CURRENT_ACTIVE_OBJECT_SHADER_ID = project.objects[i].shader.ID;
			project.objects[i].updateModel();
			project.objects[i].updateUniforms();
			project.objects[i].render();
		}

		//render IMGUI stuff here
		ImGui::Begin("Controls");
		ImGui::Text("Objects");
		for (int i = 0; i < OBJECT_LIST.size(); i++) {
			if (ImGui::Button(OBJECT_LIST[i].c_str())) {
				CURRENT_ACTIVE_OBJECT = i;
			}
		}
		ImGui::Checkbox("Wireframe Mode:- ", &project.objects[CURRENT_ACTIVE_OBJECT].wireFrameMode);
		ImGui::Text(("Controls:- "+OBJECT_LIST[CURRENT_ACTIVE_OBJECT]).c_str());
		ImGui::DragFloat("PositionX", &project.objects[CURRENT_ACTIVE_OBJECT].modelArray[12], 0.001f, -20, 20);
		ImGui::DragFloat("PositionY", &project.objects[CURRENT_ACTIVE_OBJECT].modelArray[13], 0.001f, -20, 20);
		ImGui::DragFloat("PositionZ", &project.objects[CURRENT_ACTIVE_OBJECT].modelArray[14], 0.001f, -20, 20);
		ImGui::DragFloat("ScaleX", &project.objects[CURRENT_ACTIVE_OBJECT].modelArray[0], 0.001f, 0, 10);
		ImGui::DragFloat("ScaleY", &project.objects[CURRENT_ACTIVE_OBJECT].modelArray[5], 0.001f, 0, 10);
		ImGui::DragFloat("ScaleZ", &project.objects[CURRENT_ACTIVE_OBJECT].modelArray[10], 0.001f, 0, 10);
		project.objects[CURRENT_ACTIVE_OBJECT].arrayToMatrix();
		if(ImGui::Button("updateTextures")){ project.objects[CURRENT_ACTIVE_OBJECT].updateTextures(); }
		ImGui::End();

		ImGui::Begin("Projects");
		ImGui::Text(("CurrentProject:- " + PROJECT_LIST[CURRENT_ACTIVE_PROJECT]).c_str());
		for (int i = 0; i < PROJECT_LIST.size(); i++) {
			if (ImGui::Button(PROJECT_LIST[i].c_str())) {
				CURRENT_ACTIVE_PROJECT = i;
				CURRENT_ACTIVE_OBJECT = 0;
				//convert the current matrix to array before serialization
				for (int i = 0; i < project.objects.size(); i++) {
					project.objects[i].arrayToMatrix();
				}

				//seriliaze the data before closing
				{
					std::ofstream os(PROJECT_NAME + "data.xml");
					cereal::XMLOutputArchive archive(os);
					archive(CEREAL_NVP(project));
				}

				PROJECT_NAME = "SCENE/"+PROJECT_LIST[i]+"/";
				project = Project(PROJECT_NAME);
				project.objects[CURRENT_ACTIVE_OBJECT].updateTextures();

				//Deserialize the data
				{
					std::ifstream dataFile;
					dataFile.open(PROJECT_NAME + "data.xml");
					if (dataFile) {//check if data.xml exists then deserialze
						std::ifstream is(PROJECT_NAME + "data.xml");
						cereal::XMLInputArchive archive(is);
						archive(project);

						for (int i = 0; i < project.objects.size(); i++) {
							project.objects[i].arrayToMatrix();
						}
					}
					dataFile.close();
				}
				//update Projection
				for (int i = 0; i < project.objects.size(); i++) {
					project.objects[i].updateProjection();
				}
				//update view
				for (int i = 0; i < project.objects.size(); i++) {
					project.objects[i].updateView();
				}
				//update the objects list
				get_objects_list();
			}
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}//end of render loop

	//convert the current matrix to array before serialization
	for (int i = 0; i < project.objects.size(); i++) {
		project.objects[i].arrayToMatrix();
	}

	//seriliaze the data before closing
	{
		std::ofstream os(PROJECT_NAME + "data.xml");
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
