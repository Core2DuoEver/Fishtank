#pragma once

#include "Bait.h"
#include "mesh_object.h"
#include "model_object.h"
class objects_database
{
private:
	//GUI List work.
	class entry_object {
	public:
		std::string name{}; //Displayed name.

		int unsigned id{}; //Index for the unique ID descibed in objects.

		int unsigned gui_list_id{}; //Index in the list

		unsigned char type = 255; //Type. 255 == Uninit
	};

	enum object_types {
		OBJECT_MESH = 1, OBJECT_MODEL = 2
	};

	//Containers
	std::vector<mesh_object> mesh_vector{};
	std::vector<model_object> model_vector{};

	std::string gui_list_string{}; //String for working with GuiListView.

	std::vector<entry_object> list_vector{}; //Entry objects vector.

	material_plus standart_mesh_texture; //Standart texture!

	unsigned int last_id = 0; //Used for giving unique ID's. Goes +1 when an object is added, never goes down.

public:
	void reload_gui_list(); //Reloads gui_list_string based on list_vector

	//Get from containers
	entry_object get_entry_from_index(unsigned int index_entry);

	mesh_object* get_mesh_object(objects_database::entry_object id_entry);
	model_object* get_model_object(objects_database::entry_object id_entry);
	
	//Basic getters
	std::vector<mesh_object> get_mesh_vector() {
		return(mesh_vector);
	}
	std::vector<model_object> get_model_vector() {
		return(model_vector);
	}

	//Container add functions
	void add_mesh_object(Mesh mesh_entry);

	void add_model_object(Model model_entry);

	//Container delete
	void remove_object(entry_object entry_index); //Removes objects using entry objects.

	//Container duplicate.
	void duplicate_object(entry_object entry_index); //Duplicates object

	objects_database(); //Constructor.
};

