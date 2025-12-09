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

		unsigned char type = OBJECT_DISABLED; //Type. NULL == Uninit
	};

	//Containers
	std::vector<mesh_object> mesh_vector{};
	std::vector<model_object> model_vector{};

	std::string gui_list_string{}; //String for working with GuiListView.
	std::vector<entry_object> list_vector{}; //Entry objects vector.

	Material standart_mesh_texture; //Standart texture!

	unsigned int last_id = 0; //Used for giving unique ID's. Goes +1 when an object is added, never goes down.

	unsigned int size = 0;
public:
	void save(std::string path_to_save);
	void load(std::string path_to_load);

	void reload_gui_list(); //Reloads gui_list_string based on list_vector

	json json_serialize_db();
	void json_deserialize_db(json json_to_load);
	//Get from containers
	entry_object get_entry_from_index(unsigned int index_entry);

	mesh_object* get_mesh_object(objects_database::entry_object id_entry);
	model_object* get_model_object(objects_database::entry_object id_entry);
	base_object* get_base_object(objects_database::entry_object id_entry);
	
	//Basic getters
	std::vector<mesh_object> get_mesh_vector() {
		return(mesh_vector);
	}
	std::vector<model_object> get_model_vector() {
		return(model_vector);
	}

	std::string get_gui_list_string(){
		return (gui_list_string);
	}

	//Container add functions
	void add_mesh_object(Mesh mesh_entry);
	void add_mesh_object(mesh_object mesh_object_entry);

	void add_model_object(std::string path_in);
	void add_model_object(model_object model_in);

	//Container delete
	void remove_object(entry_object entry_index); //Removes objects using entry objects.

	//Container duplicate.
	void duplicate_object(entry_object entry_index); //Duplicates object

	//Container change.
	void change_mesh_object_model(entry_object entry_index, Mesh changer_mesh_in);

	void change_model_object_mdl(entry_object entry_index, model_plus changer_model_in);

	unsigned int mesh_vaoid_uses(unsigned int mesh_vaoid);
	unsigned int model_vaoid_uses(unsigned int model_vaoid);

	unsigned int get_size();

	bool empty();

	objects_database(); //Constructor.

	~objects_database(); //Deconstructor.
};

