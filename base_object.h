#pragma once
#include "Bait.h"

class object_mods {
public:
	short unsigned int mod_type;
	int mod_param;
};

class base_object
{
private:
	std::string name{};

	unsigned int object_id{};
	
	Vector3 object_position = { 0 };
	Vector3 object_angle = { 0 }; //STORED IN DEGREE's
	Vector3 object_scale = { 1, 1, 1 };

	Matrix object_matrix{};

	std::vector <std::string> object_logic{}; //Logic - Qualifies for onHit/onTick/onTouch, what to change and etc.
	std::vector<object_mods> object_modificators{}; //Possible mods for the editor. Not for the engine.

public:
	enum object_modifcators_types {
		object_hidden
	};
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
	std::string get_object_name() {
		return(name);
	}
	unsigned int get_object_id() {
		return object_id;
	}

	void add_modificator(object_mods modificator_in); //Adds modificator to the vector.
	void remove_modificator(short unsigned int modificator_type_in); //Removes modificator to the vector.
	std::vector<object_mods> find_modificator(short unsigned int modificator_type_in); //Find modificator, if found, returns all found mods with that type.
	bool find_exact_modificator(object_mods modificator_in); //Find modificator, if found, returns all found mods with that type.

	std::vector<object_mods> get_object_modificators() {
		return object_modificators;
	}

	void insert_logic(std::string logic_string_in, unsigned int logic_insert); //Insert the logic in that place.
	void add_logic(std::string logic_string_in); //Add the logic .push_back()
	void remove_logic(unsigned int logic_index); //Remove the logic at index (0,1,2,3)
	
	std::string get_logic_string(); //Get the logic vector as a string for the list view
	std::vector<std::string> get_logic_vector() {
		return (object_logic);
	}
	void set_logic_vector(std::vector<std::string> to_set) {
		object_logic = to_set;
	}


	unsigned int get_logic_size() {
		return(object_logic.size());
	}

	Vector3 get_position();
	Vector3 get_scale();
	Vector3 get_angle();

	void set_position(Vector3 in); //Sets the position of the object, and updates it.
	void set_position(float in, matrix_change_index matrix_index); //Sets the position of object ONE x/y/z thing, using the enum, and updates it.
	void set_scale(Vector3 in);//Sets the scale of object, and updates it.
	void set_scale(float in, matrix_change_index matrix_index); //Sets the scale of object ONE x/y/z thing, using the enum, and updates it.
	void set_angle(Vector3 in);//Sets the angle of object, and updates it.
	void set_angle(float in, matrix_change_index matrix_index); //Sets the angle of object ONE x/y/z thing, using the enum, and updates it.

	//No second versions because {1,0,0} equal to {1} X
	void add_position(Vector3 in); //Adds the position of the object, and updates it.
	void add_scale(Vector3 in);//Sets the scale of object, and updates it.
	void add_angle(Vector3 in);//Sets the angle of object, and updates it.

	void update_matrix();

	base_object();
};

