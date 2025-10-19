#pragma once

#include "Bait.h"

class model_object
{
private:
	Matrix model_matrix{}; //Positional matrix

	Model model_mdl{}; //Model
	Mesh model_colision_mesh{}; //Colision model

	std::vector<short unsigned int> object_modificators{}; //Possible modifcators

	enum object_modifcators_types {
		mod_duplicated = 1, mod_duplicate = 2
	};

	std::string path{}; //Path of the model. Those are stored in models//

	std::string name{};

	unsigned int object_id{};
public:
	void get_model_matrix(Matrix matrix_in) {
		model_matrix = matrix_in;
	}
	void set_model_mdl(Model model_in) {
		model_mdl = model_in;
	}
	void set_model_colision(Mesh collision_mesh_in) {
		model_colision_mesh = collision_mesh_in;
	}
	void set_model_name(std::string name_in) {
		name = name_in;
	}
	void set_model_object_id(int object_id_in) {
		object_id = object_id_in;
	}

	Matrix get_matrix() {
		return model_matrix;
	}
	Model get_mesh_model() {
		return(model_mdl);
	}
	Mesh get_mesh_colision() {
		return(model_colision_mesh);
	}
	std::string get_model_name() {
		return(name);
	}
	unsigned int get_object_id() {
		return object_id;
	}


	void add_modificator(short unsigned int modificator_in); //Adds modificator to the vector.
	void remove_modificator(short unsigned int modificator_in); //Removes modificator to the vector.
	bool find_modificator(short unsigned int modificator_in); //Find modificator, if found, returns true.

	Vector3 get_position();
	Vector3 get_scale();
	Quaternion get_angle();

	~model_object();
};

