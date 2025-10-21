#pragma once

#include "Bait.h"

class model_object
{
private:
	Matrix model_matrix{}; //Positional matrix
	Model model_mdl{}; //Model
	Mesh model_colision_mesh{}; //Colision model
	std::string path{}; //Path of the model. Those are stored in models//
public:
	void set_model_mdl(Model model_in) {
		model_mdl = model_in;
	}
	void set_model_colision(Mesh collision_mesh_in) {
		model_colision_mesh = collision_mesh_in;
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

	~model_object();
};

