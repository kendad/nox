#include "object.h"
#include "globals.h"

Object::Object() {
	model_path = "resources/monkey/monkey.obj";
	shader_path = "Shaders/";

	model = Model(model_path);
	shader = Shader((shader_path + "base.vs").c_str(), (shader_path + "base.fs").c_str());

	modelMatrix = glm::mat4(1.0f);

	positionX = 0.0f;
	positionY = 0.0f;
	positionZ = 0.0f;

	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;
}

Object::Object(std::string _model_path, std::string _shader_path) {
	model_path = _model_path;
	shader_path = _shader_path;

	model = Model(model_path);
	shader = Shader((shader_path+"base.vs").c_str(), (shader_path + "base.fs").c_str());

	modelMatrix=glm::mat4(1.0f);

	positionX = 0.0f;
	positionY = 0.0f;
	positionZ = 0.0f;

	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;
}

void Object::updateProjection() {
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(PROJECTION_MATRIX));
}

void Object::updateView() {
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(VIEW_MATRIX));
}

void Object::updateModel() {
	shader.use();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(positionX, positionY, positionZ));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleX, scaleY, scaleZ));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Object::render() {
	model.Draw(shader);
}