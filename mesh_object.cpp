#include "mesh_object.h"

//Destructor
mesh_object::~mesh_object() {
	//Add check if it was duplicated or the duplicate exist
		if (mesh_model.vaoId != NULL) {
			UnloadMesh(mesh_model);
		} //Unload mesh if it exists
		if (mesh_colision_mesh.vaoId != NULL) {
			UnloadMesh(mesh_colision_mesh);
		} //Also. Materials are handled diffrently.
}