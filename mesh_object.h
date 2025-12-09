#pragma once

#include "base_object.h"
#include "material_database.h"

Texture CreateDefaultTexture();

class mesh_object : public base_object
{
private:
	Mesh mesh_model{}; //Model
	Material mesh_material{}; //Material
	std::string mesh_material_path{}; //Material path.

	int param1{};
	int param2{};

	unsigned char mesh_type = mesh_cube;
public:

	json json_serialize();

	void json_deserialize(json& j_load);

	void set_mesh_model(Mesh model_in) {
		mesh_model = model_in;
	}

	Mesh gen_mesh_model(); //Generates a mesh base on a current mesh_type.

	void set_mesh_type(unsigned char mesh_type_in) {
		mesh_type = mesh_type_in;
	}

	void set_mesh_material(std::string path_in, material_database* db_use);

	void set_mesh_material(std::string path_in);

	void set_mesh_material(Material material_in) {
		mesh_material = material_in;
	}

	void set_param1(int param1_in) {
		param1 = param1_in;
	}
	void set_param2(int param2_in) {
		param2 = param2_in;
	}

	int get_param1() {
		return (param1);
	}
	int get_param2() {
		return (param2);
	}

	Mesh& get_mesh_model() {
		return(mesh_model);
	}
	Material get_mesh_material() {
		return(mesh_material);
	}
	std::string get_mesh_material_path() {
		return mesh_material_path;
	}
   


	unsigned char get_mesh_type() {
		return(mesh_type);
	}
	mesh_object();

	~mesh_object();

};

