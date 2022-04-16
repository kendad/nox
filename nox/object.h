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

	template<class Archive>
	/*void serialize(Archive& ar, glm::mat4& m) {
		ar(m[0],m[1],m[2],m[3]);
	}*/
	void serialize(Archive& ar) {
		ar(positionX,positionY,positionZ,scaleX,scaleY,scaleZ);
	}
};
