#pragma once

#include "Bait.h"

#include "material_plus.h"

class material_database
{
private:
	std::vector <material_show_plus> material_show_vector{};

	Image default_texture; //Why isn't it a texture? - For safe Unloading.
public:
	Material get_material_from_path( std::string material_path_in);
	Texture get_material_preview(std::string material_path_in);
	void database_re_init();
	void database_init();

	void create_default_texture();

	std::vector <material_show_plus> get_material_show_vector() {
		return material_show_vector;
	}

	Texture get_default_texture() {
		return LoadTextureFromImage(default_texture);
	}

	unsigned int size();

	~material_database();
};