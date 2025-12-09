#include "model_object.h"

void model_object::json_deserialize(json json_to_deserialize){
	set_object_name(json_to_deserialize.value("name", "Model"));

	set_object_id(json_to_deserialize.value("object_id", 0));

	load_type = json_to_deserialize.value("model_type", MODEL_UNDEFINED);

	// Vector3 pos
	if (json_to_deserialize.contains("position") && json_to_deserialize["position"].is_array() && json_to_deserialize["position"].size() >= 3) {
		set_position({ json_to_deserialize["position"][0], json_to_deserialize["position"][1], json_to_deserialize["position"][2] });
	}

	// Vector3 angle
	if (json_to_deserialize.contains("angle") && json_to_deserialize["angle"].is_array() && json_to_deserialize["angle"].size() >= 3) {
		set_angle({ json_to_deserialize["angle"][0], json_to_deserialize["angle"][1], json_to_deserialize["angle"][2] });
	}

	// Vector3 scale
	if (json_to_deserialize.contains("scale") && json_to_deserialize["scale"].is_array() && json_to_deserialize["scale"].size() >= 3) {
		set_scale({ json_to_deserialize["scale"][0], json_to_deserialize["scale"][1], json_to_deserialize["scale"][2] });
	}

	// Logic
	if (json_to_deserialize.contains("logic") && json_to_deserialize["logic"].is_array()) {
		set_logic_vector(json_to_deserialize["logic"].get<std::vector<std::string>>());
	}

	// mods
	if (json_to_deserialize.contains("modificators") && json_to_deserialize["modificators"].is_array()) {
		for (const auto& mod_json : json_to_deserialize["modificators"]) {
			object_mods mod;
			mod.mod_type = mod_json.value("type", 0);
			mod.mod_param = mod_json.value("param", 0);
			add_modificator(mod);
		}
	}

	std::string path_to_load = json_to_deserialize.value("model_path", "");

	set_model(path_to_load); //IMPLEMENT MISSING MODEL

	update_matrix(); //Update the matrix
}

json model_object::json_serialize() {
	json j_save;

	//Save names and object_id
	j_save["object_type"] = OBJECT_MODEL;

	j_save["name"] = get_object_name();
	j_save["object_id"] = get_object_id();

	//Save model settings
	j_save["model_type"] = load_type;

	switch (load_type) {
	case MODEL_EXTERNAL: j_save["model_path"] = "temp\\" + model_base.path; break;
	case MODEL_INTERNAL: j_save["model_path"] = model_base.path; break;
	}

	//Save positions and stuff as array.
	j_save["position"] = { get_position().x,get_position().y ,get_position().z };
	j_save["angle"] = { get_angle().x,get_angle().y ,get_angle().z };
	j_save["scale"] = { get_scale().x,get_scale().y ,get_scale().z };

	j_save["logic"] = get_logic_vector(); //Save logic

	json mods_array = json::array(); //Set the array
	//Convert object_mods for easy use
	for (const auto& mod : get_object_modificators()) {
		mods_array.push_back({ {"type", mod.mod_type}, {"param", mod.mod_param} }); //Push them
	}

	//Save them.
	j_save["modificators"] = mods_array;

	return j_save; //Return them. 
}


void model_object::set_model(std::string path_in) {
	if (FileExists(path_in.c_str())) {
		std::regex model_regex(R"(resources\\.*)");
		std::smatch matches;

		if (std::regex_search(path_in, matches, model_regex)) {
			model_base.model_mdl = LoadModel(path_in.c_str());
			model_base.path = matches[0];
			load_type = MODEL_INTERNAL;
		}
		else {
			model_base.model_mdl = LoadModel(path_in.c_str());
			model_base.path = path_in.c_str();
			load_type = MODEL_EXTERNAL;
		}
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