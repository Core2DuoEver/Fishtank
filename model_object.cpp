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
//Destructor
model_object::~model_object() {
	if (model_mdl.meshes != NULL) {
		UnloadModel(model_mdl);
	} //Unload mesh if it exists
	if (model_colision_mesh.vaoId != NULL) {
		UnloadMesh(model_colision_mesh);
	} //Also. Materials are handled diffrently.
}