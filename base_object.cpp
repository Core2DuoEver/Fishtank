#include "base_object.h"

Quaternion base_object::get_angle() {
	Quaternion matrix_angle_temp;
	MatrixDecompose(object_matrix, nullptr, &matrix_angle_temp, nullptr);
	return(matrix_angle_temp);
}

Vector3 base_object::get_position() {
	Vector3 matrix_translation_temp;
	MatrixDecompose(object_matrix, &matrix_translation_temp, nullptr, nullptr);
	return(matrix_translation_temp);
}

Vector3 base_object::get_scale() {
	Vector3 matrix_scale_temp;
	MatrixDecompose(object_matrix, nullptr, nullptr, &matrix_scale_temp);
	return(matrix_scale_temp);
}

void base_object::add_modificator(base_object::object_mods modificator_in) {
	object_modificators.push_back(modificator_in); //Just add it.
}

void base_object::remove_modificator(short unsigned int modificator_in) {
	object_modificators.erase(
		std::remove_if(object_modificators.begin(), object_modificators.end(),
			[modificator_in](const object_mods& mod) {
				return mod.mod_type == modificator_in;
			}),
		object_modificators.end()
	);
}

std::vector<base_object::object_mods> base_object::find_modificator(short unsigned int modificator_in) {
	std::vector<base_object::object_mods> result;

	std::copy_if(object_modificators.begin(), object_modificators.end(),std::back_inserter(result),[modificator_in](const object_mods& mod) {return mod.mod_type == modificator_in;});

	return result;
}

bool base_object::find_exact_modificator(object_mods modificator_in) {
	auto find_temp = std::find(object_modificators.begin(), object_modificators.end(), modificator_in);
	if (find_temp != object_modificators.end()) {
		return true;
	}
	return false;
}