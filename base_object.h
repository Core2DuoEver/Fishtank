#pragma once
#include "Bait.h"

class base_object
{
private:
	std::string name{};

	unsigned int object_id{};

	Matrix object_matrix{};

	class object_mods { 
	public:
		short unsigned int mod_type;
		int mod_param;
	};

	std::vector<object_mods> object_modificators{}; //Possible modifcators

	enum object_modifcators_types {
		mod_duplicated = 1, mod_duplicate = 2
	};

public:
	void set_object_name(std::string name_in) {
		name = name_in;
	}
	void set_object_id(unsigned int object_id_in) {
		object_id = object_id_in;
	}
	void set_object_matrix(Matrix matrix_in) {
		object_matrix = matrix_in;
	}

	Matrix get_object_matrix() {
		return object_matrix;
	}
	std::string get_mesh_name() {
		return(name);
	}
	unsigned int get_object_id() {
		return object_id;
	}

	void add_modificator(object_mods modificator_in); //Adds modificator to the vector.
	void remove_modificator(object_mods modificator_in); //Removes modificator to the vector.
	std::vector<object_mods> find_modificator(short unsigned int modificator_type_in); //Find modificator, if found, returns all found mods with that type.

	Vector3 get_position();
	Vector3 get_scale();
	Quaternion get_angle();
};

