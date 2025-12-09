#include "objects_database.h"



void objects_database::reload_gui_list() {

	bool is_mesh_vector_empty = mesh_vector.empty();
	bool is_model_vector_empty = model_vector.empty();

	gui_list_string.erase();

	if (!is_mesh_vector_empty || !is_model_vector_empty) {

		//std::vector<entry_object> string_temp;
		//list_vector.clear();
		list_vector.resize(last_id+1);

		for (auto& entry : list_vector) {
			entry.type = OBJECT_DISABLED;
		}

		for (mesh_object mesh_id_seek : mesh_vector) {
			int id = mesh_id_seek.get_object_id();
			if (id < list_vector.size()) {
				list_vector[id].name = mesh_id_seek.get_object_name();
				list_vector[id].id = id;
				list_vector[id].type = OBJECT_MESH;
			}
		}
		for (model_object model_id_seek : model_vector) {
			int id = model_id_seek.get_object_id();
			if (id < list_vector.size()) {
				list_vector[id].name = model_id_seek.get_object_name();
				list_vector[id].id = id;
				list_vector[id].type = OBJECT_MODEL;
			}
		}
		//Go through the vectors, get their ID's, set it to the [], set the name to the vector.

		unsigned int gui_list_index = 0;

		for (size_t list_index = 0; list_index < list_vector.size(); list_index++) {
			if (list_vector[list_index].type != OBJECT_DISABLED) {
				gui_list_string += list_vector[list_index].name + ";";
				list_vector[list_index].gui_list_id = gui_list_index;
				gui_list_index++;
			}
		}

		size = gui_list_index;

		gui_list_string.pop_back(); //Delete the last ";", kinda a hack. 

	}
	else {

		size = 0;

		gui_list_string = EMPTY_GUI_LIST;

		list_vector.clear();

		last_id = 0;
	}
}

unsigned int objects_database::get_size() {
	return size;
}

objects_database::entry_object objects_database::get_entry_from_index(unsigned int index_entry) {
	for (entry_object list_index : list_vector) {
		if (list_index.gui_list_id == index_entry) {
			return list_index;
		}
	}
	return{ "", NULL, NULL, OBJECT_DISABLED }; //Return a 0 with Uninit type if it's not found.
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

base_object* objects_database::get_base_object(objects_database::entry_object id_entry) {
	if (id_entry.type == OBJECT_DISABLED) {

		return nullptr; //If UNIT

	}
	if (id_entry.type == OBJECT_MODEL) {
		for (model_object& model_index : model_vector) {
			if (model_index.get_object_id() == id_entry.id) {
				return &model_index;
			}
		}
	}
	if (id_entry.type == OBJECT_MESH) {
		for (mesh_object& mesh_index : mesh_vector) {
			if (mesh_index.get_object_id() == id_entry.id) {
				return &mesh_index;
			}
		}
	}
	return nullptr; //If not found
}

void objects_database::add_mesh_object(Mesh mesh_entry) {
	mesh_object object_add;
	object_add.set_mesh_model(mesh_entry);
	object_add.set_object_name(STANDART_MESH_NAME);
	object_add.set_object_id(last_id);
	object_add.set_mesh_material(""); //Null will default.
	//object_add.set_mesh_material("");

	mesh_vector.push_back(object_add);

	last_id++; //Up the ID after adding the object.
	reload_gui_list();
}

void objects_database::add_mesh_object(mesh_object mesh_object_entry) {
	mesh_object_entry.set_object_id(last_id);

	mesh_vector.push_back(mesh_object_entry);

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

		//IF that vaoID has only one usage, then its only in one mesh, and its about to be deleted.

		if (mesh_temp != nullptr) { 
			if (mesh_vaoid_uses(mesh_temp->get_mesh_model().vaoId) == 1) {
				UnloadMesh(mesh_temp->get_mesh_model());
			}
		}

		for (unsigned int erase_index = 0; erase_index < mesh_vector.size(); erase_index++) {
			if (mesh_vector[erase_index].get_object_id() == entry_index.id) {
				mesh_vector.erase(mesh_vector.begin() + erase_index);

				break; //IDs are unique, no second ones.
			}
		}

		reload_gui_list(); //Reload gui_list at the end.


	}
					break;
	case OBJECT_MODEL: {
		model_object* model_temp = get_model_object(entry_index);

		if (model_vaoid_uses(model_temp->get_model().model_mdl.meshes[0].vaoId) == 1) { //IF that vaoID has only one usage, then its only in one mesh, and its about to be deleted.
			UnloadModel(model_temp->get_model().model_mdl);
		}

		
		for (unsigned int erase_index = 0; erase_index < model_vector.size(); erase_index++) {
			if (model_vector[erase_index].get_object_id() == entry_index.id) {
				model_vector.erase(model_vector.begin() + erase_index);

				break; //IDs are unique, no second ones.
			}
		}

		reload_gui_list(); //Reload gui_list at the end.

	}
					 break;
	}
}

bool objects_database::empty() {
	if (!mesh_vector.empty()) {
		return false;
	}
	if (!model_vector.empty()) {
		return false;
	}
	return true;
}

void objects_database::duplicate_object(objects_database::entry_object entry_index) {
	switch (entry_index.type) {
	case OBJECT_MESH: {
		mesh_object* mesh_temp = get_mesh_object(entry_index);

		mesh_object mesh_duplicate_temp = *mesh_temp;

		mesh_duplicate_temp.set_object_id(last_id);

		mesh_duplicate_temp.set_mesh_material(LoadMaterialDefault()); //Load it again

		mesh_vector.push_back(mesh_duplicate_temp);

		last_id++; //Up the ID after adding the object.

		reload_gui_list();
	}
					break;
	case OBJECT_MODEL: {
		model_object* model_temp = get_model_object(entry_index);

		model_object model_duplicate_temp = *model_temp;

		model_duplicate_temp.set_object_id(last_id);

		model_vector.push_back(model_duplicate_temp);

		last_id++; //Up the ID after adding the object.

		reload_gui_list();
	}
					break;
	}
}
unsigned int objects_database::mesh_vaoid_uses(unsigned int mesh_vaoid) {

	unsigned int int_temp = 0;

	for (mesh_object& mesh_index : mesh_vector) {
		if (mesh_index.get_mesh_model().vaoId == mesh_vaoid) {
			int_temp++;
		}
	}

	return int_temp;
}

unsigned int objects_database::model_vaoid_uses(unsigned int model_vaoid) {

	unsigned int int_temp = 0;

	for (model_object& model_index : model_vector) {
		if ((IsModelValid(model_index.get_model().model_mdl))&&(model_index.get_model().model_mdl.meshCount > 0)) { //Check if the model at least valid.
			if (model_index.get_model().model_mdl.meshes[0].vaoId == model_vaoid) { //HACK! Uses the first mesh of the model. 
				int_temp++;
			}
		}
	}

	return int_temp;
}

void objects_database::change_mesh_object_model(entry_object entry_index, Mesh changer_mesh_in) {
	auto to_change = get_mesh_object(entry_index);
	if (to_change != nullptr) {
		if (mesh_vaoid_uses(to_change->get_mesh_model().vaoId) == 1) { //IF the model has one instance
			UnloadMesh(to_change->get_mesh_model()); //Unload the model then.
		}
		to_change->set_mesh_model(changer_mesh_in); //Change the mesh after this.
	}
	else {
		std::cout << "FISHTANK: Failed to change the mesh. Entry_index failed";
	}
}

objects_database::objects_database() {
	//Standart texture load HERE. Add after implementing texture_db

	objects_database::reload_gui_list(); 
}
objects_database::~objects_database() {
	//Standart texture load HERE. Add after implementing texture_db


	for (auto& mesh_unload : mesh_vector) {
		if (_CrtIsValidHeapPointer(mesh_unload.get_mesh_model().vertices)) { //Valid check | breaks on duplicats!
			UnloadMesh(mesh_unload.get_mesh_model());
		}
	}
	for (auto model_unload : model_vector) {
		if ((IsModelValid(model_unload.get_model().model_mdl)) && (model_unload.get_model().model_mdl.meshCount > 0)) { //Check if the model at least valid.

			UnloadModel(model_unload.get_model().model_mdl);
		}
	}
	std::cout << "FISHTANK: Object database unloaded! \n";
}

json objects_database::json_serialize_db() {
	json j_db_save = json::array();

	for (auto& mesh_save : mesh_vector) {
		j_db_save.push_back(mesh_save.json_serialize());
	}

	for (auto& model_save : model_vector) {
		j_db_save.push_back(model_save.json_serialize());
	}

	return j_db_save;
}

void objects_database::json_deserialize_db(json json_to_deserialize) {
	
	//Unload
	for (auto& mesh_unload : mesh_vector) {
		if (_CrtIsValidHeapPointer(mesh_unload.get_mesh_model().vertices)) { //Valid check | breaks on duplicats!
			UnloadMesh(mesh_unload.get_mesh_model());
		}
	}
	for (auto model_unload : model_vector) {
		if ((IsModelValid(model_unload.get_model().model_mdl)) && (model_unload.get_model().model_mdl.meshCount > 0)) { //Check if the model at least valid.

			UnloadModel(model_unload.get_model().model_mdl);
		}
	}

	mesh_vector.clear();
	model_vector.clear();

	if (json_to_deserialize.is_array()) {
		for (auto obj_json : json_to_deserialize) {
			char obj_type = obj_json.value("object_type", OBJECT_DISABLED);

			unsigned max_last_id = 0;

			switch (obj_type) {
			case OBJECT_MESH: {
				mesh_object obj;
				obj.json_deserialize(obj_json);
				if (obj.get_object_id() > max_last_id) {
					max_last_id = obj.get_object_id();
				}
				mesh_vector.push_back(obj);

				reload_gui_list();
			}break;

			case OBJECT_MODEL: {
				model_object obj;
				obj.json_deserialize(obj_json);
				if (obj.get_object_id() > max_last_id) {
					max_last_id = obj.get_object_id();
				}
				model_vector.push_back(obj);

				reload_gui_list();

			}break;

			default: {

			}break;
			}

			last_id = max_last_id+1;
		}
	}

}
std::string ChangeFileExtension(const std::string& filePath, const std::string& newExt) {
	size_t lastSlash = filePath.find_last_of("\\/");
	size_t lastDot = filePath.find_last_of('.');
	if (lastDot != std::string::npos && (lastSlash == std::string::npos || lastDot > lastSlash)) {
		return filePath.substr(0, lastDot) + newExt;
	}
	return filePath + newExt;
}

void objects_database::save(std::string path_to_save) {
	fs::remove_all("temp");
	fs::path save_temp_path = "temp";
	fs::create_directories(save_temp_path);

	json to_save_db = json_serialize_db();

	int zip_error_code;

	zip_t* zip_archive = zip_open(path_to_save.c_str(), ZIP_CREATE | ZIP_TRUNCATE, &zip_error_code);

		for (auto& obj_json : to_save_db) {
			auto obj_type = obj_json.value("object_type", OBJECT_DISABLED);

			if (obj_type == OBJECT_MODEL) {
				
				auto load_type = obj_json.value("model_type", MODEL_UNDEFINED);

				time_t current_time = time(nullptr);

				if (load_type == MODEL_EXTERNAL) {
					std::string file_to_copy = obj_json.value("model_path", "");
					if (!file_to_copy.empty()) {
						if (!file_to_copy.empty()) {
							std::string folder_name = std::string(GetFileNameWithoutExt(file_to_copy.c_str())) + std::to_string(obj_json.value("object_id", -1)); //make the folder name

							zip_dir_add(zip_archive, (folder_name + "/").c_str(), ZIP_FL_ENC_UTF_8); //folder in zip itself
							zip_file_set_mtime(zip_archive, zip_name_locate(zip_archive, (folder_name + "/").c_str(), 0), current_time, 0); //time to zip

							std::string zip_path = folder_name + "/" + std::string(GetFileName(file_to_copy.c_str())); 
							zip_source_t* source = zip_source_file(zip_archive, file_to_copy.c_str(), 0, 0); 
							auto file_index = zip_file_add(zip_archive, zip_path.c_str(), source, ZIP_FL_ENC_UTF_8); //add the file to the folder
							zip_file_set_mtime(zip_archive, file_index, current_time, 0); //and time

							obj_json["model_path"] = zip_path;

							std::string mtl_file = ChangeFileExtension(file_to_copy, ".mtl"); 

							//Now copy the material. If exists
							if (FileExists(mtl_file.c_str())) {
								std::string mtl_zip_path = folder_name + "/" + std::string(GetFileName(mtl_file.c_str())); //Add the mtl file too then.
								zip_source_t* mtl_source = zip_source_file(zip_archive, mtl_file.c_str(), 0, 0);
								auto mtl_index = zip_file_add(zip_archive, mtl_zip_path.c_str(), mtl_source, ZIP_FL_ENC_UTF_8); 
								zip_file_set_mtime(zip_archive, mtl_index, current_time, 0);

								std::ifstream mtl_stream(mtl_file);
								std::string mtl_content((std::istreambuf_iterator<char>(mtl_stream)),std::istreambuf_iterator<char>()); //copy the whole file to the string

								std::regex png_regex(R"(map_Kd\s+([^\s]+\.png))"); //regex searches for the .png inside the file
								auto begin = std::sregex_iterator(mtl_content.begin(), mtl_content.end(), png_regex);
								auto end = std::sregex_iterator();

								std::string texture_dir = GetDirectoryPath(mtl_file.c_str()); //Add textures from mtl

								for (std::sregex_iterator i = begin; i != end; ++i) {
									std::string texture_file = (*i)[1]; 
									std::string texture_path = texture_dir + "\\" + texture_file;

									if (FileExists(texture_path.c_str())) {
										std::string texture_zip_path = folder_name + "/" + texture_file; //Copy to zip.
										zip_source_t* texture_source = zip_source_file(zip_archive, texture_path.c_str(), 0, 0);
										auto texture_index = zip_file_add(zip_archive, texture_zip_path.c_str(), texture_source, ZIP_FL_ENC_UTF_8);
										zip_file_set_mtime(zip_archive, texture_index, current_time, 0);
									}

								}
							}

						}
					}
					else {
						break;
					}
				}

			}

		}

	std::string json_file_path_and_name = save_temp_path.string() + MAP_SAVE_JSON_NAME;

	std::ofstream file_save(json_file_path_and_name.c_str());
	file_save << to_save_db.dump(4);
	file_save.close();

	zip_source* json_source_zip = zip_source_file(zip_archive, json_file_path_and_name.c_str(), 0, 0); //it works
	int zip_file_index = zip_file_add(zip_archive, MAP_SAVE_JSON_NAME, json_source_zip, ZIP_FL_OVERWRITE); //Save the json.
	time_t time_zip = time(nullptr);
	zip_file_set_mtime(zip_archive, zip_file_index, time_zip, 0);

	int zip_close_int = zip_close(zip_archive);

	fs::remove_all("temp");
}


void objects_database::load(std::string path_to_load) {
	int zip_error;
	zip_t* zip_archive_load = zip_open(path_to_load.c_str(), ZIP_RDONLY, &zip_error); //Открыаем архив.

	if (zip_archive_load) {
		fs::remove_all("temp");
		fs::create_directories("temp");

		zip_int64_t zip_entries = zip_get_num_entries(zip_archive_load, 0);

		std::vector<std::string> files_unarchavied;

		for (zip_int64_t zip_file_index = 0; zip_file_index < zip_entries; zip_file_index++) {
			zip_stat_t file_info;
			zip_stat_init(&file_info);
			zip_stat_index(zip_archive_load, zip_file_index, 0, &file_info);

			fs::path file_to_unarchive_path = fs::path("temp") / file_info.name;

			fs::create_directories(file_to_unarchive_path.parent_path());

			if (file_info.name[strlen(file_info.name) - 1] == '/') {
				continue;
			}

			zip_file_t* file = zip_fopen_index(zip_archive_load, zip_file_index, 0);
			if (!file) {
				std::cout << "EXIT";
				continue;
			}

			std::ofstream file_to_unarchive(file_to_unarchive_path.string(), std::ios::binary);
			std::vector<char> buffer(1024 * 16);

			zip_int64_t bytesRead;
			while ((bytesRead = zip_fread(file, buffer.data(), buffer.size())) > 0) {
				file_to_unarchive.write(buffer.data(), bytesRead);
			}
			file_to_unarchive.close();
			zip_fclose(file);

			files_unarchavied.push_back(file_to_unarchive_path.string());
		}

		std::string path_to_load = std::string(GetWorkingDirectory()) + "\\temp\\" + std::string(MAP_SAVE_JSON_NAME);

		std::fstream file_load(path_to_load);
		if (file_load.is_open()) {
			json json_to_load;
			try {
				json_to_load = json::parse(file_load);
			}
			catch (const json::parse_error& e) {
				std::cout << "FISHTANK: ERROR: Error loading the JSON! \n";
				exit;
			}

			json_deserialize_db(json_to_load);

		}
	}
}