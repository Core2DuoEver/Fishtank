#pragma once

#include "material_plus.h"
#include "base_object.h"

class mesh_object : public base_object
{
private:
	Mesh mesh_model{}; //Model
	Mesh mesh_colision_mesh{}; //Colision model
	material_plus mesh_material{}; //Material
public:
	void set_mesh_model(Mesh model_in) {
		mesh_model = model_in;
	}
	void set_mesh_colision(Mesh collision_mesh_in) {
		mesh_colision_mesh = collision_mesh_in;
	}
	void set_mesh_material(material_plus material_in) {
		mesh_material = material_in;
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

	~mesh_object();

};

