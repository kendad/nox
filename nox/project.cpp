#include "project.h"

Project::Project(std::string base_path) {
	Object object_default;
	Object object_default2(base_path+"/object1/OBJ/plane.obj",base_path+"/object1/Shaders/");
	objects.push_back(object_default);
	objects.push_back(object_default2);
};