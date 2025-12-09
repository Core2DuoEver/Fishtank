#include "material_database.h"

void material_database::create_default_texture() {
    default_texture = GenImageColor(DEFAULT_TEXTURE_HEIGHT, DEFAULT_TEXTURE_WIDTH, DEFAULT_TEXTURE_COLOR_BG); //This is creating a standart texture.

    for (int y = 0; y < DEFAULT_TEXTURE_HEIGHT; y += DEFAULT_TEXTURE_SIZE_CHECKERS) {
        for (int x = 0; x < DEFAULT_TEXTURE_WIDTH; x += DEFAULT_TEXTURE_SIZE_CHECKERS) {
            if (((x / DEFAULT_TEXTURE_SIZE_CHECKERS) + (y / DEFAULT_TEXTURE_SIZE_CHECKERS)) % 2 == 1) {
                ImageDrawRectangle(&default_texture, x, y, DEFAULT_TEXTURE_SIZE_CHECKERS, DEFAULT_TEXTURE_SIZE_CHECKERS, DEFAULT_TEXTURE_COLOR_CHECKERS);
            }
        }
    }

}

unsigned int material_database::size() {
    return material_show_vector.size();
}

void material_database::database_init() {
    FilePathList material_folders = LoadDirectoryFiles("resources\\materials\\"); //Load every material from the material folder.
     
    create_default_texture();

    //Should go to another function

    for (int folder_index = 0; folder_index < material_folders.count; folder_index++) { //Go through every folder.
        if (IsFileExtension(material_folders.paths[folder_index], ".Folder")) { //IS Really a folder)

            std::string material_binary_path = std::string(material_folders.paths[folder_index]) + "//mat.mati"; 

            if (!FileExists(material_binary_path.c_str())) { 
                break; //IF the param file doesnt exists, break from the loop. This is file IS needed, so if isnt present, then NO!
            }

            material_show_plus material_temp{}; //Temp mat.
            material_temp.mat_path = material_folders.paths[folder_index]; //Set the path

            /*
            FilePathList material_files = LoadDirectoryFiles(material_folders.paths[folder_index]); //Load every existing file.

            std::vector<std::string> material_textures = { //Every possible texture.
                "ALBEDO.png", "METALNESS.png", "NORMAL.png", "ROUGHNESS.png",
                "OCCLUSION.png", "EMISSION.png", "HEIGHT.png", "CUBEMAP.png",
                "IRRIDIANCE.png", "PREFILTER.png", "BRDF.png"
            };

            for (unsigned int texture_index = 0; texture_index < material_textures.size(); texture_index++) { //Go through every name, and try to load it.
                std::string texture_path = std::string(material_folders.paths[folder_index]) + "//" + material_textures[texture_index];
                if(FileExists(texture_path.c_str())) SetMaterialTexture(&material_temp.mat_main, texture_index, LoadTexture(texture_path.c_str())); //IF it exists, load.
            }

                std::ifstream binary_file(material_binary_path.c_str(), std::ios::binary); //Load the param file now.

                if (binary_file.is_open()) { //File is opened. Double check, maybe the permissions aren't worky.
                    if (material_temp.mat_main.maps != nullptr) { //Check if it is REALLY initialised 
                        binary_file.read(reinterpret_cast<char*>(&material_temp.mat_main.maps->value), sizeof(material_temp.mat_main.maps->value));
                    }

                    short int shader_detector;
                    binary_file.read(reinterpret_cast<char*>(&shader_detector), sizeof(shader_detector)); //Shader detector. If its a 1, it has a shader, not a 1, doesnt have a shader. Change to bool.

                    if (shader_detector == 1) { 
                        std::string shader_path;
                        size_t shader_path_length;

                        binary_file.read(reinterpret_cast<char*>(&shader_path_length),sizeof(shader_path_length)); //Read the shader path length.
                        shader_path.resize(shader_path_length); //Resize the path.
                        binary_file.read(&shader_path[0], shader_path_length); //Write into it.

                        if (FileExists(shader_path.c_str())) { //IF shader exists. Load it.
                            material_temp.mat_main.shader = LoadShader(NULL, shader_path.c_str());
                        }
                    }
                    binary_file.close(); //Close the file.
                }
                else {
                    UnloadMaterial(material_temp.mat_main); //Unload the material.
                    break; //break from the for loop then.
                }
             */

            std::string preview_path = std::string(material_folders.paths[folder_index]) + "//PREVIEW.png"; //Load the preview file.
            if (FileExists(preview_path.c_str())) { 
             //   material_temp.mat_preview = LoadImage(preview_path.c_str()); //Changed to image.
            }
            
            material_show_vector.push_back(material_temp); //PUSH BACK!
            //UnloadDirectoryFiles(material_files);
        }
    }

    UnloadDirectoryFiles(material_folders);
}

Texture material_database::get_material_preview(std::string material_path_in) {
    Texture temp_preview;

    if (material_path_in.empty() || !DirectoryExists(material_path_in.c_str())) {
        std::cout << "FISHTANK: ERROR: Error loading the texture. Wrong path";
        return LoadTextureFromImage(default_texture);
    }
    std::string preview_path = material_path_in + "//PREVIEW.png";

    if (FileExists(preview_path.c_str())) {
        temp_preview = LoadTexture(preview_path.c_str());
        return temp_preview;
    }
    else {
        return LoadTextureFromImage(default_texture);
    }

    return LoadTextureFromImage(default_texture); //If, for some reason, IFs dont work. Last resort.
}

void material_database::database_re_init() {
	for (auto vector_texture_unload : material_show_vector) {
		//UnloadMaterial(vector_texture_unload.mat_main);
	//	UnloadTexture(vector_texture_unload.mat_preview);
       // UnloadImage(vector_texture_unload.mat_preview);
	}
    material_show_vector.clear();
}

Material material_database::get_material_from_path(std::string material_path_in) {
    if (IsFileExtension(material_path_in.c_str(), ".Folder")) { //IS Really a folder)
        Material material_temp{}; //Temp mat.
        material_temp = LoadMaterialDefault();
        std::string material_binary_path = material_path_in + "//mat.mati";

        if (!FileExists(material_binary_path.c_str())) {
            //return null; //IF the param file doesnt exists, break from the loop. This is file IS needed, so if isnt present, then NO!
            Texture2D texture_temp = LoadTextureFromImage(default_texture);
            SetMaterialTexture(&material_temp, MATERIAL_MAP_ALBEDO, texture_temp); 
            return material_temp;
        }


        FilePathList material_files = LoadDirectoryFiles(material_path_in.c_str()); //Load every existing file.

        std::vector<std::string> material_textures = { //Every possible texture.
            "ALBEDO.png", "METALNESS.png", "NORMAL.png", "ROUGHNESS.png",
            "OCCLUSION.png", "EMISSION.png", "HEIGHT.png", "CUBEMAP.png",
            "IRRIDIANCE.png", "PREFILTER.png", "BRDF.png"
        };

        for (unsigned int texture_index = 0; texture_index < material_textures.size(); texture_index++) { //Go through every name, and try to load it.
            std::string texture_path = material_path_in + "//" + material_textures[texture_index];
            if (FileExists(texture_path.c_str())) SetMaterialTexture(&material_temp, texture_index, LoadTexture(texture_path.c_str())); //IF it exists, load.
        }

        std::ifstream binary_file(material_binary_path.c_str(), std::ios::binary); //Load the param file now.

        if (binary_file.is_open()) { //File is opened. Double check, maybe the permissions aren't worky.
            if (material_temp.maps != nullptr) { //Check if it is REALLY initialised
                binary_file.read(reinterpret_cast<char*>(&material_temp.maps->value), sizeof(material_temp.maps->value));
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
                    material_temp.shader = LoadShader(NULL, shader_path.c_str());
                }
            }
            binary_file.close(); //Close the file.
        }
        else {
            UnloadMaterial(material_temp); //Unload the material.
            UnloadDirectoryFiles(material_files);

            Texture2D texture_temp = LoadTextureFromImage(default_texture);
            material_temp = LoadMaterialDefault();
            SetMaterialTexture(&material_temp, MATERIAL_MAP_ALBEDO, texture_temp);
            return material_temp;

        }

        UnloadDirectoryFiles(material_files);

        return material_temp;

    }
}

material_database::~material_database() {
    for (auto to_unload : material_show_vector) {
      //  UnloadImage(to_unload.mat_preview);
    }
    std::cout << "FISHTANK: Material Database unloaded! \n";
}