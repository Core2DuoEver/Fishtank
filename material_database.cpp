#include "material_database.h"

void material_database::database_init() {
	FilePathList material_paths = LoadDirectoryFiles("materials\\"); //fomo
	for (int path_index = 0; path_index < material_paths.capacity; path_index++) {  //poing
		if (IsFileExtension(material_paths.paths[path_index], ".Folder")) {

			material_plus material_temp{}; //newone

			material_temp.mat_main = LoadMaterialDefault();
			material_temp.mat_path = material_paths.paths[path_index];
			material_temp.mat_name = GetFileNameWithoutExt(material_paths.paths[path_index]);

			FilePathList material_paths = LoadDirectoryFiles(material_paths.paths[path_index]); //fumo

			/*
				MATERIAL_MAP_ALBEDO = 0,        // Albedo material (same as: MATERIAL_MAP_DIFFUSE)
				MATERIAL_MAP_METALNESS,         // Metalness material (same as: MATERIAL_MAP_SPECULAR)
				MATERIAL_MAP_NORMAL,            // Normal material
				MATERIAL_MAP_ROUGHNESS,         // Roughness material
				MATERIAL_MAP_OCCLUSION,         // Ambient occlusion material
				MATERIAL_MAP_EMISSION,          // Emission material
				MATERIAL_MAP_HEIGHT,            // Heightmap material
				MATERIAL_MAP_CUBEMAP,           // Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
				MATERIAL_MAP_IRRADIANCE,        // Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
				MATERIAL_MAP_PREFILTER,         // Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
				MATERIAL_MAP_BRDF
			*/

			std::vector<std::string> material_textures = { "ALBEDO.png","METALNESS.png","NORMAL.png","ROUGHNESS.png","OCCLUSION.png","EMISSION.png","HEIGHT.png","CUBEMAP.png","IRRIDIANCE.png","PREFILTER.png","BRDF.png" };

			for (short unsigned int material_texture_index = 0; material_texture_index < material_textures.size(); material_texture_index++) { //was  <= 10 before, now practically 11

				std::string material_path_name = material_paths.paths[path_index] + std::string("//") + material_textures[material_texture_index];

				SetMaterialTexture(&material_temp.mat_main, material_texture_index, LoadTexture(material_path_name.c_str()));

			}

			std::string material_binary_file_path = material_paths.paths[path_index] + std::string("//mat.mati"); //lofff

			std::ifstream binaryfile(material_binary_file_path.c_str(), std::ios::binary);

			binaryfile.read(reinterpret_cast<char*>(&material_temp.mat_main.maps->value), sizeof(material_temp.mat_main.maps->value));
			//Read shader value.
			short int shader_detector_value;
			
			binaryfile.read(reinterpret_cast<char*>(&shader_detector_value), sizeof(shader_detector_value));

			//If we do have a 1 then shader exists. If not, do nothing.
			if (shader_detector_value == 1) {
				std::string material_shader_path;

				size_t material_shader_path_size;
				binaryfile.read(reinterpret_cast<char*>(&material_shader_path_size), sizeof(material_shader_path_size));
				material_shader_path.resize(material_shader_path_size);
				binaryfile.read(&material_shader_path[0], material_shader_path_size);

				material_temp.mat_main.shader = LoadShader(NULL, material_shader_path.c_str());
			}

			std::string tmp2_name = material_paths.paths[path_index] + std::string("//PREVIEW.png");

			material_temp.mat_preview = LoadTexture(tmp2_name.c_str());

			material_vector.push_back(material_temp);

			binaryfile.close();

		}
	}
}
void material_database::database_re_init() {
	for (auto vector_texture_unload : material_vector) {
		UnloadMaterial(vector_texture_unload.mat_main);
		UnloadTexture(vector_texture_unload.mat_preview);
	}
	material_vector.clear();
}

