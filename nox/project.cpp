#include "project.h"
#include <fstream>

Project::Project(std::string base_path) {
	//Open the object txt file and check how many object in scene and store in memory
	std::ifstream file(base_path);
	file.open(base_path+"/object_data.txt");

	std::vector<std::string> object_data;
	std::string object_data_string;
	while (file >> object_data_string) { object_data.push_back(object_data_string); }

	file.close();

	for (int i = 0; i < object_data.size(); i++) { 
		Object object(base_path + object_data[i] + "/OBJ/model.obj", base_path + object_data[i] + "/Shaders/");
		objects.push_back(object);
	}

	/*Object object_default(base_path + "object0/OBJ/model.obj", base_path + "/object0/Shaders/");
	Object object_default2(base_path+"object1/OBJ/model.obj",base_path+"/object1/Shaders/");
	objects.push_back(object_default);
	objects.push_back(object_default2);*/
};