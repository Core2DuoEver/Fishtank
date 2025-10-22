#include "objects_database.h"



void objects_database::reload_gui_list() {

	bool is_mesh_vector_empty = mesh_vector.empty();
	bool is_model_vector_empty = model_vector.empty();

	if (!is_mesh_vector_empty && !is_model_vector_empty) {

		//std::vector<entry_object> string_temp;
		list_vector.resize(last_id);
		//Resizing the vector for the worst possible outcome.

		for (mesh_object mesh_id_seek : mesh_vector) {
			list_vector[mesh_id_seek.get_object_id()].name = mesh_id_seek.get_object_name();
			list_vector[mesh_id_seek.get_object_id()].id = mesh_id_seek.get_object_id();
			list_vector[mesh_id_seek.get_object_id()].type = OBJECT_MESH;
		}
		for (model_object model_id_seek : model_vector) {
			list_vector[model_id_seek.get_object_id()].name = model_id_seek.get_object_name();
			list_vector[model_id_seek.get_object_id()].id = model_id_seek.get_object_id();
			list_vector[model_id_seek.get_object_id()].type = OBJECT_MODEL;
		}
		//Go through the vectors, get their ID's, set it to the [], set the name to the vector.

		unsigned int gui_list_index = 0;

		for (size_t list_index = 0; list_index <= last_id; list_index++) {
			if (list_vector[list_index].type != 255) {
				gui_list_string += list_vector[list_index].name + ";";
				list_vector[list_index].gui_list_id = gui_list_index;
				gui_list_index++;
			}
		}

		gui_list_string.pop_back(); //Delete the last ";", kinda a hack. 
	
	}
	else { 

		gui_list_string = EMPTY_GUI_LIST;

	}
}

objects_database::entry_object objects_database::get_entry_from_index(unsigned int index_entry) {
	for (entry_object list_index : list_vector) {
		if (list_index.gui_list_id == index_entry) {
			return list_index;
		}
	}
	return{NULL, NULL, NULL, 255}; //Return a 0 with Uninit type if it's not found.
}

mesh_object* objects_database::get_mesh_object(objects_database::entry_object id_entry) {
	if (id_entry.type == OBJECT_MESH) {
		for (mesh_object& mesh_index : mesh_vector) {
			if (mesh_index.get_object_id() == id_entry.id) {
				return &mesh_index;
			}
		}
	}
	return nullptr; //If not found OR is not a OBJECT_MESH
}

model_object* objects_database::get_model_object(objects_database::entry_object id_entry) {
	if (id_entry.type == OBJECT_MODEL) {
		for (model_object& model_index : model_vector) {
			if (model_index.get_object_id() == id_entry.id) {
				return &model_index;
			}
		}
	}
	return nullptr; //If not found OR is not a OBJECT_MODEL
}

void objects_database::add_mesh_object(Mesh mesh_entry) {
	mesh_object object_add;
	object_add.set_mesh_model(mesh_entry);
	object_add.set_object_name(STANDART_MESH_NAME);
	object_add.set_object_id(last_id);
	object_add.set_mesh_material(standart_mesh_texture);

	mesh_vector.push_back(object_add);

	last_id++; //Up the ID after adding the object.
	reload_gui_list();
}

void objects_database::add_model_object(std::string path_in) {
	model_object object_add;
	object_add.set_model(path_in);
	object_add.set_object_name(STANDART_MODEL_NAME);
	object_add.set_object_id(last_id);

	model_vector.push_back(object_add);

	last_id++; //Up the ID after adding the object.
	reload_gui_list();
}

void objects_database::remove_object(objects_database::entry_object entry_index) {
	switch (entry_index.type) {
	case OBJECT_MESH: {
		mesh_object* mesh_temp = get_mesh_object(entry_index);

		//First. See if the object was duplicated or is a duplicate.

	}
					break;
	case OBJECT_MODEL: {
		model_object* model_temp = get_model_object(entry_index);

		//First. See if the object was duplicated or is a duplicate.

		auto vector_temp = model_temp->find_modificator(base_object::mod_duplicate); //Is it a duplicate?

		bool original_exist = false;
		bool copies_exist = false;

		if (!vector_temp.empty()) {
			//If it's not empty and there is something found. 
			for (auto model_temp : model_vector) { //Does original exist.
				if (model_temp.find_exact_modificator({base_object::mod_duplicated,int(entry_index.id)})) {
					original_exist = true;
				}
			}
		}


	}
					 break;
	}

	reload_gui_list();
}

void objects_database::duplicate_object(objects_database::entry_object entry_index) {
	switch (entry_index.type) {
	case OBJECT_MESH: {
		mesh_object* mesh_temp = get_mesh_object(entry_index);

		mesh_object mesh_duplicate_temp = *mesh_temp;

		mesh_duplicate_temp.add_modificator({ base_object::mod_duplicate, int(entry_index.id) });

		mesh_duplicate_temp.set_object_id(last_id);

		mesh_vector.push_back(mesh_duplicate_temp);

		last_id++; //Up the ID after adding the object.

		mesh_temp->add_modificator({ base_object::mod_duplicated,int(last_id) });

	}
					break;
	case OBJECT_MODEL: {
		model_object* model_temp = get_model_object(entry_index);

		model_object model_duplicate_temp = *model_temp;

		model_duplicate_temp.add_modificator({ base_object::mod_duplicate, int(entry_index.id) });

		model_duplicate_temp.set_object_id(last_id);

		model_vector.push_back(model_duplicate_temp);

		last_id++; //Up the ID after adding the object.

		model_temp->add_modificator({ base_object::mod_duplicated,int(last_id)});
	}
					break;
	}

	reload_gui_list();
}

objects_database::objects_database() {
	//Standart texture load HERE. Add after implementing texture_db

	objects_database::reload_gui_list(); 
}