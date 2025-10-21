#include "model_object.h"

//Destructor
model_object::~model_object() {
	//Add check if it was duplicated or the duplicate exist

	if (model_mdl.meshes != NULL) {
		UnloadModel(model_mdl);
	} //Unload mesh if it exists
	if (model_colision_mesh.vaoId != NULL) {
		UnloadMesh(model_colision_mesh);
	} //Also. Materials are handled diffrently.
}