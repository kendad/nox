#pragma once
#include "object.h"
#include <vector>

class Project {
public:
	Project(std::string base_path);
	std::vector<Object> objects;//serialize this
};

