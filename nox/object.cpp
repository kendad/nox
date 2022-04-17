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
	matrixToArray();
	//arrayToMatrix();
	
	shader.use();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(positionX, positionY, positionZ));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleX, scaleX, scaleX));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void Object::render() {
	model.Draw(shader);
}

void Object::matrixToArray() {
	modelArray[0] = modelMatrix[0][0];
	modelArray[1] = modelMatrix[0][1];
	modelArray[2] = modelMatrix[0][2];
	modelArray[3] = modelMatrix[0][3];

	modelArray[4] = modelMatrix[1][0];
	modelArray[5] = modelMatrix[1][1];
	modelArray[6] = modelMatrix[1][2];
	modelArray[7] = modelMatrix[1][3];
	
	modelArray[8] = modelMatrix[2][0];
	modelArray[9] = modelMatrix[2][1];
	modelArray[10] = modelMatrix[2][2];
	modelArray[11] = modelMatrix[2][3];

	modelArray[12] = modelMatrix[3][0];
	modelArray[13] = modelMatrix[3][1];
	modelArray[14] = modelMatrix[3][2];
	modelArray[15] = modelMatrix[3][3];
}

void Object::arrayToMatrix() {
	modelMatrix[0][0] = modelArray[0];
	modelMatrix[0][1] = modelArray[1];
	modelMatrix[0][2] = modelArray[2];
	modelMatrix[0][3] = modelArray[3];

	modelMatrix[1][0] = modelArray[4];
	modelMatrix[1][1] = modelArray[5];
	modelMatrix[1][2] = modelArray[6];
	modelMatrix[1][3] = modelArray[7];

	modelMatrix[2][0] = modelArray[8];
	modelMatrix[2][1] = modelArray[9];
	modelMatrix[2][2] = modelArray[10];
	modelMatrix[2][3] = modelArray[11];

	modelMatrix[3][0] = modelArray[12];
	modelMatrix[3][1] = modelArray[13];
	modelMatrix[3][2] = modelArray[14];
	modelMatrix[3][3] = modelArray[15];
}