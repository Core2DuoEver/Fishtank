#pragma once

#include "base_object.h"
#include "model_plus.h"

enum model_load_type {
	MODEL_EXTERNAL,MODEL_INTERNAL, MODEL_UNDEFINED
};

class model_object : public base_object
{
private:
	model_load_type load_type = MODEL_UNDEFINED;

	model_plus model_base;
public:
	void set_model(std::string path_in);

	void set_model_colision(Mesh collision_mesh_in) {
		//model_colision_mesh = collision_mesh_in;
	}

	model_plus get_model() {
		return(model_base);
	}
	Mesh get_mesh_colision() {
		//return(model_colision_mesh);
	}

	json json_serialize();
	void json_deserialize(json json_to_deserialize);

	~model_object();
};

