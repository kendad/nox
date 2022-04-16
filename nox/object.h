#pragma once
#include "model.h"
#include "shader.h"

class Object {
public:
	Object();
	Object(std::string _model_path,std::string _shader_path);

	std::string model_path;
	std::string shader_path;

	Model model;
	Shader shader;

	glm::mat4 modelMatrix;//serialize this

	void updateProjection();
	void updateView();
	void updateModel();
	void render();

	float positionX;
	float positionY;
	float positionZ;

	float scaleX;
	float scaleY;
	float scaleZ;
};
