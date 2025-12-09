#pragma once

#include "raylib.h"
#include <vector>
#include <string>

class model_database 
{
private:

	//First, we load all models previews as images, also load their paths.
	//Then, when the user selects one, load it, and add to the scene. If you try to load the same model, raylib will notice it.

	class model_entry_show { //Preview
	public:
		Image model_preview_image; //I decided to make it in software for easier threaded loading. OpenGL doesnt support threaded work.
		std::string model_path; //Path for loading the model. Name of the model is made from 
	};

	class model_entry { //The thing that's going to get loaded/saved.
	public:
		Model model_in;
		Shader model_shader; // IF present
		ModelAnimation model_animation; //IF present.
		std::string model_path;
		
	}; //Make a converter/loader.

	std::vector<model_entry_show> model_preview_vector{};
};

