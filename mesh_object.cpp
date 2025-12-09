#include "mesh_object.h"

Texture CreateDefaultTexture() {
	Image default_texture = GenImageColor(DEFAULT_TEXTURE_HEIGHT, DEFAULT_TEXTURE_WIDTH, DEFAULT_TEXTURE_COLOR_BG); //This is creating a standart texture.

	for (int y = 0; y < DEFAULT_TEXTURE_HEIGHT; y += DEFAULT_TEXTURE_SIZE_CHECKERS) {
		for (int x = 0; x < DEFAULT_TEXTURE_WIDTH; x += DEFAULT_TEXTURE_SIZE_CHECKERS) {
			if (((x / DEFAULT_TEXTURE_SIZE_CHECKERS) + (y / DEFAULT_TEXTURE_SIZE_CHECKERS)) % 2 == 1) {
				ImageDrawRectangle(&default_texture, x, y, DEFAULT_TEXTURE_SIZE_CHECKERS, DEFAULT_TEXTURE_SIZE_CHECKERS, DEFAULT_TEXTURE_COLOR_CHECKERS);
			}
		}
	}

	return LoadTextureFromImage(default_texture);
}

void mesh_object::set_mesh_material(std::string path_in, material_database* db_use) { //Depreceated
	UnloadMaterial(mesh_material);
	std::string material_binary_path = path_in + "//mat.mati";
	//if (FileExists(material_binary_path.c_str())) { //IF exists at all.
		mesh_material_path = path_in;
	//	mesh_material = get_material_from_path(path_in);
		mesh_material = db_use->get_material_from_path(path_in);
	//}

		//Check commented out, because the get_material_path already checks, and applies standart texture if so.
}

void mesh_object::set_mesh_material(std::string material_path_in) {
	mesh_material = LoadMaterialDefault();
	if ((IsFileExtension(material_path_in.c_str(), ".Folder")||(!material_path_in.empty()))) { //IS Really a folder)
		//Material material_temp{}; //Temp mat.
		std::string material_binary_path = material_path_in + "//mat.mati";

		if (!FileExists(material_binary_path.c_str())) {
			//return null; //IF the param file doesnt exists, break from the loop. This is file IS needed, so if isnt present, then NO!

			SetMaterialTexture(&mesh_material, MATERIAL_MAP_ALBEDO, CreateDefaultTexture());

			exit;
		}


		FilePathList material_files = LoadDirectoryFiles(material_path_in.c_str()); //Load every existing file.

		std::vector<std::string> material_textures = { //Every possible texture.
			"ALBEDO.png", "METALNESS.png", "NORMAL.png", "ROUGHNESS.png",
			"OCCLUSION.png", "EMISSION.png", "HEIGHT.png", "CUBEMAP.png",
			"IRRIDIANCE.png", "PREFILTER.png", "BRDF.png"
		};

		for (unsigned int texture_index = 0; texture_index < material_textures.size(); texture_index++) { //Go through every name, and try to load it.
			std::string texture_path = material_path_in + "//" + material_textures[texture_index];
			if (FileExists(texture_path.c_str())) SetMaterialTexture(&mesh_material, texture_index, LoadTexture(texture_path.c_str())); //IF it exists, load.
		}

		std::ifstream binary_file(material_binary_path.c_str(), std::ios::binary); //Load the param file now.

		if (binary_file.is_open()) { //File is opened. Double check, maybe the permissions aren't worky.
			if (mesh_material.maps != nullptr) { //Check if it is REALLY initialised
				binary_file.read(reinterpret_cast<char*>(&mesh_material.maps->value), sizeof(mesh_material.maps->value));
			}

			short int shader_detector;
			binary_file.read(reinterpret_cast<char*>(&shader_detector), sizeof(shader_detector)); //Shader detector. If its a 1, it has a shader, not a 1, doesnt have a shader. Change to bool.

			if (shader_detector == 1) {
				std::string shader_path;
				size_t shader_path_length;

				binary_file.read(reinterpret_cast<char*>(&shader_path_length), sizeof(shader_path_length)); //Read the shader path length.
				shader_path.resize(shader_path_length); //Resize the path.
				binary_file.read(&shader_path[0], shader_path_length); //Write into it.

				if (FileExists(shader_path.c_str())) { //IF shader exists. Load it.
					mesh_material.shader = LoadShader(NULL, shader_path.c_str());
				}
			}
			binary_file.close(); //Close the file.
		}
		else {
			UnloadMaterial(mesh_material); //Unload the material.
			UnloadDirectoryFiles(material_files);

			SetMaterialTexture(&mesh_material, MATERIAL_MAP_ALBEDO, CreateDefaultTexture());

			exit;
		}

		UnloadDirectoryFiles(material_files);

	}
	else {
		SetMaterialTexture(&mesh_material, MATERIAL_MAP_ALBEDO, CreateDefaultTexture());

		exit;
	}
}

Mesh mesh_object::gen_mesh_model() {
	switch (mesh_type) {
	case mesh_poly: {
		return GenMeshPoly(param1, STANDART_MESH_SIZE);
	}break;
	case mesh_plane: {
		return GenMeshPlane(STANDART_MESH_SIZE, STANDART_MESH_SIZE, STANDART_MESH_PLANE_RES, STANDART_MESH_PLANE_RES); 
	}break;
	case mesh_cube: {
		return GenMeshCube(STANDART_MESH_SIZE, STANDART_MESH_SIZE, STANDART_MESH_SIZE);
	}break;
	case mesh_sphere: {
		return GenMeshSphere(STANDART_MESH_SIZE, param1, param2);
	}break;
	case mesh_hemisphere: {
		return GenMeshHemiSphere(STANDART_MESH_SIZE, param1, param2);
	}break;
	case mesh_cylinder : {
		return GenMeshCylinder(STANDART_MESH_SIZE, STANDART_MESH_SIZE, param1);
	}break;
	case mesh_cone: {
		return GenMeshCone(STANDART_MESH_SIZE, STANDART_MESH_SIZE, param1);
	}break;
	case mesh_torus: {
		return GenMeshTorus(STANDART_MESH_SIZE, STANDART_MESH_SIZE, param1, param2);
	}break;
	case mesh_knot: {
		return GenMeshKnot(STANDART_MESH_SIZE, STANDART_MESH_SIZE, param1, param2);
	}break;
	}
}

json mesh_object::json_serialize() {
	json j_save;

	//Save names and object_id
	j_save["object_type"] = OBJECT_MESH;

	j_save["name"] = get_object_name();
	j_save["object_id"] = get_object_id();
	
	//Save mat_path
	j_save["mesh_material_path"] = get_mesh_material_path();

	//Save mesh settings
	j_save["param1"] = param1;
	j_save["param2"] = param2;
	j_save["mesh_type"] = mesh_type;

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

void mesh_object::json_deserialize(json& j_load) {
	set_object_name(j_load.value("name",""));

	set_object_id(j_load.value("object_id", 0));

	mesh_material_path = (j_load.value("mesh_material_path", "")); //NEEDS TO BE RELOADED IN MAIN CYCLE

	set_param1(j_load.value("param1", 0));
	set_param2(j_load.value("param2", 0));

	set_mesh_type(j_load.value("mesh_type", mesh_cube));

	// Vector3 pos
	if (j_load.contains("position") && j_load["position"].is_array() && j_load["position"].size() >= 3) {
		set_position( { j_load["position"][0], j_load["position"][1], j_load["position"][2]});
	}

	// Vector3 angle
	if (j_load.contains("angle") && j_load["angle"].is_array() && j_load["angle"].size() >= 3) {
		set_angle({ j_load["angle"][0], j_load["angle"][1], j_load["angle"][2] });
	}

	// Vector3 scale
	if (j_load.contains("scale") && j_load["scale"].is_array() && j_load["scale"].size() >= 3) {
		set_scale({ j_load["scale"][0], j_load["scale"][1], j_load["scale"][2] });
	}

	// Logic
	if (j_load.contains("logic") && j_load["logic"].is_array()) {
		set_logic_vector(j_load["logic"].get<std::vector<std::string>>());
	}

	// mods
	if (j_load.contains("modificators") && j_load["modificators"].is_array()) {
		for (const auto& mod_json : j_load["modificators"]) {
			object_mods mod;
			mod.mod_type = mod_json.value("type", 0);
			mod.mod_param = mod_json.value("param", 0);
			add_modificator(mod);
		}
	}

	set_mesh_material(mesh_material_path);
	mesh_model = gen_mesh_model(); //Generate mesh
	update_matrix(); //Update the matrix
}

//Destructor
mesh_object::mesh_object() {
	mesh_material = LoadMaterialDefault();
}



mesh_object::~mesh_object() {
	//Add check if it was duplicated or the duplicate exist
	//	if (mesh_model.vaoId != NULL) {
		//	UnloadMesh(mesh_model);
		//} //Unload mesh if it exists
		//if (mesh_colision_mesh.vaoId != NULL) {
			//UnloadMesh(mesh_colision_mesh);
		//} //Also. Materials are handled diffrently.
}