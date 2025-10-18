#include "mesh_object.h"

Quaternion mesh_object::get_angle() {
	Quaternion matrix_angle_temp;
	MatrixDecompose(mesh_matrix, nullptr, &matrix_angle_temp, nullptr);
	return(matrix_angle_temp);
}
Vector3 mesh_object::get_position() {
	Vector3 matrix_translation_temp;
	MatrixDecompose(mesh_matrix, &matrix_translation_temp, nullptr, nullptr);
	return(matrix_translation_temp);
}
Vector3 mesh_object::get_scale() {
	Vector3 matrix_scale_temp;
	MatrixDecompose(mesh_matrix, nullptr, nullptr, &matrix_scale_temp);
	return(matrix_scale_temp);
}
//Destructor
mesh_object::~mesh_object() {
	if (mesh_model.vaoId != NULL) {
		UnloadMesh(mesh_model);
	} //Unload mesh if it exists
	if (mesh_colision_mesh.vaoId != NULL) {
		UnloadMesh(mesh_colision_mesh);
	} //Also. Materials are handled diffrently.
}