#include "model_object.h"


void model_object::set_model(std::string path_in) {
	if (FileExists(path_in.c_str())) {
		model_base.model_mdl = LoadModel(path_in.c_str());
		model_base.path = path_in;
	}
	else {
		std::cout << "WARNING : Could't load the model, wrong path : " + path_in + "\n";
	}
}
//Destructor
model_object::~model_object() {
	/*
	//Add check if it was duplicated or the duplicate exist
	if (!model_base.path.empty()) {
		UnloadModel(model_base.model_mdl);
	} //Unload mesh if it exists
	if (model_colision_mesh.vaoId != NULL) {
		UnloadMesh(model_colision_mesh);
	} //Also. Materials are handled diffrently.*/
}