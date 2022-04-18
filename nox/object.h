#pragma once
#include "model.h"
#include "shader.h"

#include <cereal/types/array.hpp>
#include <cereal/types/memory.hpp>

class Object {
public:
	Object();
	Object(std::string _model_path,std::string _shader_path);

	std::string model_path;
	std::string shader_path;

	Model model;
	Shader shader;

	glm::mat4 modelMatrix;
	float modelArray[16];

	void updateProjection();
	void updateView();
	void updateModel();
	void updateUniforms();
	void updateTextures();
	void render();

	void matrixToArray();
	void arrayToMatrix();

	float positionX;
	float positionY;
	float positionZ;

	float scaleX;
	float scaleY;
	float scaleZ;

	template<class Archive>
	void serialize(Archive& ar) {
		ar(modelArray);
	}
};
