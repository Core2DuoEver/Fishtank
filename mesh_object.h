#pragma once

#include "Bait.h"
#include "material_plus.h"

class mesh_object
{
private:
	Matrix mesh_matrix{}; //Positional matrix of the Mesh
	
	Mesh mesh_model{}; //Model
	Mesh mesh_colision_mesh{}; //Colision model
	
	material_plus mesh_material{}; //Material
	
	std::vector<short unsigned int> object_modificators{}; //Possible modifcators
	
	std::string name{};
	
	unsigned int object_id{}; //Object id

public:
	void get_mesh_matrix(Matrix matrix_in) {
		mesh_matrix = matrix_in;
	}
	void set_mesh_model(Mesh model_in) {
		mesh_model = model_in;
	}
	void set_mesh_colision(Mesh collision_mesh_in) {
		mesh_colision_mesh = collision_mesh_in;
	}
	void set_mesh_material(material_plus material_in) {
		mesh_material = material_in;
	}
	void set_mesh_name(std::string name_in) {
		name = name_in;
	}
	void set_mesh_object_id(unsigned int object_id_in) {
		object_id = object_id_in;
	}

	Matrix get_matrix() {
		return mesh_matrix;
	}
	Mesh get_mesh_model() {
		return(mesh_model);
	}
	Mesh get_mesh_colision() {
		return(mesh_colision_mesh);
	}
	material_plus get_mesh_material() {
		return(mesh_material);
	}
	std::string get_mesh_name() {
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

	~mesh_object();

};

