#include "scene.h"

Scene::Scene(std::string _obj_file_path, std::string _shader_path) {
	base_address = "SCENE/";
	obj_file_path = base_address + _obj_file_path;
	shader_path = base_address + _shader_path;

	model = Model(obj_file_path);
	shader = Shader((shader_path+"shader.vs").c_str(), (shader_path + "shader.fs").c_str());
}