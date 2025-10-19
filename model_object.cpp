#include "model_object.h"

Quaternion model_object::get_angle() {
	Quaternion matrix_angle_temp;
	MatrixDecompose(model_matrix, nullptr, &matrix_angle_temp, nullptr);
	return(matrix_angle_temp);
}
Vector3 model_object::get_position() {
	Vector3 matrix_translation_temp;
	MatrixDecompose(model_matrix, &matrix_translation_temp, nullptr, nullptr);
	return(matrix_translation_temp);
}
Vector3 model_object::get_scale() {
	Vector3 matrix_scale_temp;
	MatrixDecompose(model_matrix, nullptr, nullptr, &matrix_scale_temp);
	return(matrix_scale_temp);
}

void model_object::add_modificator(short unsigned int modificator_in) {
	object_modificators.push_back(modificator_in); //Just add it.
}

void model_object::remove_modificator(short unsigned int modificator_in) {

	auto find_temp = std::find(object_modificators.begin(), object_modificators.end(), modificator_in);

	if (find_temp != object_modificators.end()) {
		object_modificators.erase(find_temp);
	}

}

bool model_object::find_modificator(short unsigned int modificator_in) {

	auto find_temp = std::find(object_modificators.begin(), object_modificators.end(), modificator_in);

	if (find_temp != object_modificators.end()) {
		return true;
	}

	return false;

}

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