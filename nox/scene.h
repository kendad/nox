#pragma once
#include "model.h"
#include "shader.h"

class Scene {
	public:
	Scene(std::string _obj_file_path, std::string _shader_path_vs);


	std::string base_address;
	std::string obj_file_path;
	std::string shader_path;
	Shader shader;
	Model model;

};
