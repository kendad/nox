#pragma once
#include "object.h"
#include <vector>
#include <cereal/types/vector.hpp>

class Project {
public:
	Project(std::string base_path);
	std::vector<Object> objects;


	template<class Archive>
	void serialize(Archive& ar) {
		ar(objects);
	}
};

