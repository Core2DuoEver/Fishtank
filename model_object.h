#pragma once

#include "Bait.h"
#include "base_object.h"
#include "model_plus.h"

class model_object : public base_object
{
private:
	Mesh model_colision_mesh{}; //Colision model
	Matrix model_matrix{}; //Positional matrix

	//Made one

	model_plus model_base;

public:
	void set_model(std::string path_in);

	void set_model_colision(Mesh collision_mesh_in) {
		model_colision_mesh = collision_mesh_in;
	}

	model_plus get_mesh_model() {
		return(model_base);
	}
	Mesh get_mesh_colision() {
		return(model_colision_mesh);
	}

	~model_object();
};

