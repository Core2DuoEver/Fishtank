#include "base_object.h"

void base_object::add_logic(std::string logic_string_in) {
	object_logic.push_back(logic_string_in);
}

void base_object::insert_logic(std::string logic_string_in, unsigned int logic_insert) {
	object_logic.insert(object_logic.begin() + logic_insert, logic_string_in);
}

void base_object::remove_logic(unsigned int logic_index) {
		if (logic_index < object_logic.size()) { //Check!
			object_logic.erase(object_logic.begin() + logic_index);
		}
}

std::string base_object::get_logic_string() {
	if (!object_logic.empty()) {
		std::string to_return;
		for (std::string to_write : object_logic) {
			to_return += to_write + ";";
		}
		to_return.pop_back(); //Remove the last ;
		return(to_return);
	}
		//IF empty
		return ""; //Return nothing.
}

Vector3 base_object::get_angle() {
	//Quaternion matrix_angle_temp;
	//MatrixDecompose(object_matrix, nullptr, &matrix_angle_temp, nullptr);
	return(object_angle);
}

Vector3 base_object::get_position() {
	//Vector3 matrix_translation_temp;
	//MatrixDecompose(object_matrix, &matrix_translation_temp, nullptr, nullptr);
	return(object_position);
}

Vector3 base_object::get_scale() {
	//Vector3 matrix_scale_temp;
	//MatrixDecompose(object_matrix, nullptr, nullptr, &matrix_scale_temp);
	return(object_scale);
}

void base_object::add_modificator(object_mods modificator_in) {
	object_modificators.push_back(modificator_in); //Just add it.
}

void base_object::remove_modificator(short unsigned int modificator_in) {
	//object_modificators.erase(
		//std::remove_if(object_modificators.begin(), object_modificators.end(),
			//[modificator_in](const object_mods& mod) {
				//return mod.mod_type == modificator_in;
			//}),
		//object_modificators.end()
	//);
}

std::vector<object_mods> base_object::find_modificator(short unsigned int modificator_in) {
	std::vector<object_mods> result;

	//std::copy_if(object_modificators.begin(), object_modificators.end(),std::back_inserter(result),[modificator_in](const object_mods& mod) {return mod.mod_type == modificator_in;});

	return result;
}

bool base_object::find_exact_modificator(object_mods modificator_in) {
	//auto find_temp = std::find(object_modificators.begin(), object_modificators.end(), modificator_in);
	//if (find_temp != object_modificators.end()) {
		//return true;
	//}
	return false;
}

void base_object::set_position(Vector3 in) {
	object_position = in;
	update_matrix();
}

void base_object::set_scale(Vector3 in) {
	object_scale = in;
	update_matrix();
}

void base_object::set_angle(Vector3 in) {
	object_angle = in;
	update_matrix();
}

void base_object::add_position(Vector3 in) {
	object_position = object_position + in;
	update_matrix();
}

void base_object::add_scale(Vector3 in) {
	object_scale = object_scale + in;
	update_matrix();
}

void base_object::add_angle(Vector3 in) {
	object_angle = object_angle + in;
	update_matrix();
}

void base_object::set_position(float in, matrix_change_index matrix_index) {
	
	switch (matrix_index) {
	case MATRIX_CHANGE_X: {
		object_position.x = in;
	} break;
	case MATRIX_CHANGE_Y: {
		object_position.y = in;
	} break;
	case MATRIX_CHANGE_Z: {
		object_position.z = in;
	} break;
	}

	update_matrix();
}

void base_object::set_scale(float in, matrix_change_index matrix_index) {
	switch (matrix_index) {
	case MATRIX_CHANGE_X: {
		object_scale.x = in;
	} break;
	case MATRIX_CHANGE_Y: {
		object_scale.y = in;
	} break;
	case MATRIX_CHANGE_Z: {
		object_scale.z = in;
	} break;
	}

	update_matrix();
}

void base_object::set_angle(float in, matrix_change_index matrix_index) {
	switch (matrix_index) {
	case MATRIX_CHANGE_X: {
		object_angle.x = in;
	} break;
	case MATRIX_CHANGE_Y: {
		object_angle.y = in;
	} break;
	case MATRIX_CHANGE_Z: {
		object_angle.z = in;
	} break;
	}

	update_matrix();
}

void base_object::update_matrix() {
	Matrix matScale = MatrixScale(object_scale.x, object_scale.y, object_scale.z);
	Matrix matRotate = MatrixRotateXYZ({object_angle.x* DEG2RAD, object_angle.y* DEG2RAD,object_angle.z* DEG2RAD});	//CONVERT TO RADIANS
	Matrix matTranslate = MatrixTranslate(object_position.x, object_position.y, object_position.z);
	// Scale then Rotate then Translate
	object_matrix = MatrixMultiply(MatrixMultiply(matScale, matRotate), matTranslate);
}

base_object::base_object() {
	object_matrix = MatrixIdentity();
}