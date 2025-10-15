#pragma once


#include "raylib.h"; //Нужна для отображения графики
#include "raymath.h"; //Нужна для преобразований матрицы.

#include <cstdlib>;
#include <iostream>;
#include <vector>;

#include <fstream>;

class material_plus { //Refactored!
public:
	Material mat_main;
	std::string mat_path;
	std::string mat_name;
	Texture mat_preview;
};
class material_database {
public:
	std::vector<material_plus> material_vector;

	void database_init() {
			FilePathList material_paths = LoadDirectoryFiles("materials\\"); //fomo
			for (int path_index = 0; path_index < material_paths.capacity; path_index++) {  //poing
				if (IsFileExtension(material_paths.paths[path_index], ".Folder")) {

					material_plus material_temp; //newone

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

					short int shader_detector_value;

					binaryfile.read(reinterpret_cast<char*>(&shader_detector_value), sizeof(shader_detector_value));

					if (shader_detector_value == 1) {
						std::string material_shader_path;

						size_t material_shader_path_size; //Загружаем размер путя текстур.
						binaryfile.read(reinterpret_cast<char*>(&material_shader_path_size), sizeof(material_shader_path_size)); //Читаем размерчик.
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


	void database_re_init() {
		for (auto vector_texture_unload : material_vector) {
			UnloadMaterial(vector_texture_unload.mat_main);
			UnloadTexture(vector_texture_unload.mat_preview);
		}
		material_vector.clear(); 
	}
};

class meshobj { //Obj. Refactored!
private:
	Matrix mesh_matrix; //Positional matrix of the Mesh

public:
	
	Mesh mesh_model; //Model
	Mesh mesh_colision_mesh; //Colision model
	
	material_plus mesh_material; //Material
	
	std::vector<short unsigned int> object_modificators; //Possible modifcators
    
	std::string name = "Mesh";

	int object_id; //Object id 

	Matrix get_matrix() {
		return mesh_matrix;
	}
	Vector3 get_position() {
		return{};
	}
	Vector3 get_scale() {
		return{};
	}
	Vector3 get_angle() {
		return{};
	}
};

class modelobj { //Obj. 
private:
	Matrix model_matrix; //Positional matrix

public:
	Model model_mdl; //Model
	Mesh model_colision_mesh; //Colision model

	std::vector<short unsigned int> object_modificators; //Possible modifcators

	std::string path; //Path of the model. Those are stored in models//

	std::string name = "Model";

	int object_id;

	Matrix get_matrix() {
		return model_matrix;
	}
	Vector3 get_position() {
		return{};
	}
	Vector3 get_scale() {
		return{};
	}
	Vector3 get_angle() {
		return{};
	}

};

class objnaming {
public:
	std::string name;
	int indexnamed;
	int namindex;
	int type;
};

enum NavMod {
	nav_no_objects = 0,
	nav_solid = 1,
	nav_walkable = 2

};

class navvec {
public:
	Vector3 navec3;
	Vector3 angle;
	int effects;
	int mod = -1;
};

class Navmesh {
public:
	std::vector<navvec> navmesh;
};

enum ObjectsDB {
	obj_mesh = 1,
	obj_model = 2
};

enum ObjectsColission {
	col_null = 0,
	col_solid = 1,
	col_walkable = 2
};

class objectdatabase {
private:
	float dtr(float degrees) { //Градусы в радианы.
		auto to_return = degrees * (PI / 180);
		return(to_return);
	}
	float rtd(float radians) { //Радианы в градусы.
		return((radians / 180.0f) * PI);
	}
public:

	meshlist msdb;
	mdllist mdldb;

	bool deftext = false;
	Texture deftexture;

	std::string name = "Null";

	std::vector<objnaming> names;

	int namefunked;
	int meshfunked;

	int lastid = -1;


	objnaming getinfoobj(int idtofind) {
		if (idtofind == -1) {
			objnaming toret;
			toret.type = -1;
			return(toret);
		}
		return(names[idtofind]);

	}
	int getmeshobj(int idtofind) { //Возвращает byltrc lf.
		auto worker = names[idtofind];
		int aaf = 0;
		for (auto objj : msdb.MeshVec) {
			if (objj.uniqueid == worker.namindex) {
				return (aaf);
			}
			else {
				aaf++;
			}
		}
	}
	int getmodelobj(int idtofind) { //Возвращает byltrc lf.
		auto worker = names[idtofind];
		int aaf = 0;
		for (auto objj : mdldb.MdlVec) {
			if (objj.uniqueid == worker.namindex) {
				return (aaf);
			}
			else {
				aaf++;
			}
		}
	}
	int getnamemesh(meshobj in) { //Возвращает byltrc lf.
		int aaf = 0;

		for (auto objj : names) {
			if (objj.namindex == in.uniqueid) {
				return (aaf);
			}
			else {
				aaf++;
			}
		}
	}
	int getnamemodel(modelobj in) { //Возвращает byltrc lf.
		int aaf = 0;

		for (auto objj : names) {
			if (objj.namindex == in.uniqueid) {
				return (aaf);
			}
			else {
				aaf++;
			}
		}
	}

	void reloadnames() {


		name = "";
		if ((names.size() == 0) && (lastid == -1)) {
			name = names[0].name;
			return;
		}
		if ((names.size() == 0)) {
			name = "Null";
			return;
		}
		else {
			for (auto namf : names) {
				name += namf.name + ";";
			}
			name.erase(name.size() - 1);
		}
	}

	void deleteobj(int idtodelete) {
		auto to_del_name = names[idtodelete];
		if (to_del_name.type == obj_mesh) { //Удаляем мэш
			if (!msdb.MeshVec.empty()) {
				auto to_del_mesh = msdb.MeshVec[getmeshobj(idtodelete)];
				/*
				for (auto fok : names) {

					UnloadMesh(to_del_mesh.modelmesh);
				}*/
				msdb.MeshVec.erase(msdb.MeshVec.begin() + getmeshobj(idtodelete)); //Стёрли.
				names.erase(names.begin() + getnamemesh(to_del_mesh));

				reloadnames();

				return;
				//Теперь перестройка
			}
		}

		if (to_del_name.type == obj_model) { //Удаляем модель
			if (!mdldb.MdlVec.empty()) {
				auto to_del_model = mdldb.MdlVec[getmodelobj(idtodelete)];

				mdldb.MdlVec.erase(mdldb.MdlVec.begin() + getmodelobj(idtodelete)); //Стёрли.
			
				names.erase(names.begin() + getnamemodel(to_del_model));

			reloadnames();
			return;

			}


		}
	}
	void duplicateobj(int id) {
		if (lastid != -1) {
			auto to_dupl_name = names[id];
			if (to_dupl_name.type == obj_mesh) { //Дубликат мэша
				auto to_dupl_mesh = msdb.MeshVec[getmeshobj(id)]; //Что дубликируем

				

				lastid++;

				objnaming objnam;

				objnam.name = to_dupl_name.name;
				objnam.type = obj_mesh;
				objnam.indexnamed;
				objnam.namindex = lastid; //Записываем позицию для текста
				objnam.indexnamed = msdb.MeshVec.size(); //Записываем позицию для векторного мэша.

				Matrix matcool;

				Material cooolmaterial;
				cooolmaterial = LoadMaterialDefault();
				cooolmaterial.maps->texture = LoadTextureFromImage(LoadImageFromTexture(to_dupl_mesh.meshmaterial.maps->texture));
				cooolmaterial.maps->color = to_dupl_mesh.meshmaterial.maps->color;
				
				meshobj adder;

				
				objnam.namindex = lastid; //Уникальные айдишники.
				adder.uniqueid = lastid;
				adder.modelmesh = to_dupl_mesh.modelmesh;
				adder.id = to_dupl_mesh.id;
				adder.name = name;
				adder.meshmaterial = cooolmaterial;
				
				adder.meshscale = to_dupl_mesh.meshscale;
				adder.meshposition = to_dupl_mesh.meshposition;
				adder.meshrotaxis = to_dupl_mesh.meshrotaxis;
				adder.meshmatrix = to_dupl_mesh.meshmatrix;



				names.push_back(objnam);

				msdb.MeshVec.push_back(adder);

				reloadnames();


			}
			if (to_dupl_name.type == obj_model) {
				auto to_dupl_mesh = mdldb.MdlVec[getmodelobj(id)]; //Что дубликируем

				lastid++;

				objnaming objnam;

				objnam.name = to_dupl_name.name;
				objnam.type = obj_model;
				objnam.indexnamed;
				objnam.namindex = lastid; //Записываем позицию для текста
				objnam.indexnamed = mdldb.MdlVec.size(); //Записываем позицию для векторного мэша.

				Matrix matcool;

				modelobj adder;


				objnam.namindex = lastid; //Уникальные айдишники.
				adder.uniqueid = lastid;



				adder.modelmdl = to_dupl_mesh.modelmdl;
				adder.name = name;
				adder.modelscale = to_dupl_mesh.modelscale;
				adder.modelposition = to_dupl_mesh.modelposition;
				adder.modelrotaxis = to_dupl_mesh.modelrotaxis;
				adder.matrixmodel = to_dupl_mesh.matrixmodel;



				names.push_back(objnam);

				mdldb.MdlVec.push_back(adder);

				reloadnames();
			}
		}
	}

	void addmesh(Mesh meshtoadd, std::string nameadd, int subid) {

		if (!deftext) {
		
			 
			auto fol = LoadImage("textures/def.png");
			
			ImageFlipHorizontal(&fol);
			
			deftexture = LoadTextureFromImage(fol);

			UnloadImage(fol);

			deftext = true;
		}

		lastid++;

		objnaming objnam;

		objnam.name = nameadd;
		objnam.type = 1;
		objnam.namindex = lastid; //Записываем позицию для текста
		objnam.indexnamed = msdb.MeshVec.size(); //Записываем позицию для векторного мэша.

		Matrix matcool;

		Material cooolmaterial;
		cooolmaterial = LoadMaterialDefault();
		cooolmaterial.maps->texture = deftexture;
		cooolmaterial.maps->color = WHITE;

		meshobj adder;

		objnam.namindex = lastid; //Уникальные айдишники.
		adder.uniqueid = lastid;
		adder.modelmesh = meshtoadd;
		adder.id = subid;
		adder.name = nameadd;
		adder.meshmaterial = cooolmaterial;
		adder.meshscale = { 1,1,1 };
		adder.meshposition = { 0,0,0 };
		adder.meshrotaxis = { dtr(180),0,0 };
		adder.meshmatrix = MatrixRotateXYZ(adder.meshrotaxis);
		adder.modificators = 0;


		names.push_back(objnam);

		msdb.MeshVec.push_back(adder);

		reloadnames();
	}
	void addmodel(Model modelin, std::string name, std::string pather) {

		lastid++;



		modelobj modeltoadd;

		modeltoadd.modelmdl = modelin;

		Matrix toadd;

		toadd = MatrixIdentity();

		modeltoadd.matrixmodel = toadd;

		modeltoadd.modelscale = { 1,1,1 };
		modeltoadd.modelposition = { 0,0,0 };
		modeltoadd.modelrotaxis = { 0,0,0 };
		modeltoadd.uniqueid = lastid;
		modeltoadd.path = pather;
		modeltoadd.modificators = 0;


		objnaming objnam;

		objnam.namindex = lastid;
		objnam.indexnamed = mdldb.MdlVec.size(); //Записываем позицию для векторного мэша.

		objnam.name = name;
		objnam.type = obj_model;


		names.push_back(objnam);

		mdldb.MdlVec.push_back(modeltoadd);

		reloadnames();
	}
};
class savedb {
public:
	std::vector<savemesh> meshdbsave;
	std::vector<objnaming> namesave;
	std::string namesaver = "Null";
	int lastidsave = -1;

	savemesh meshtosave(meshobj meshconvert) {

		savemesh togiveback;

		togiveback.name = meshconvert.name;
		togiveback.id = meshconvert.id;
		togiveback.meshmatrix = meshconvert.meshmatrix;
		togiveback.meshposition = meshconvert.meshposition;
		togiveback.meshrotaxis = meshconvert.meshrotaxis;
		togiveback.meshscale = meshconvert.meshscale;
		togiveback.pathmdl = "";
		togiveback.modificator = meshconvert.modificators;
		togiveback.pathtxt = meshconvert.matpl.path;
		togiveback.uniqueid = meshconvert.uniqueid;
		togiveback.savecolor = meshconvert.meshmaterial.maps->color;

		return togiveback; 
	}
	savemodel modelsave(modelobj modelconvert) {

		savemodel togiveback;

		togiveback.matrixmodel = modelconvert.matrixmodel;
		togiveback.modelposition = modelconvert.modelposition;
		togiveback.modelrotaxis = modelconvert.modelrotaxis;
		togiveback.modelscale = modelconvert.modelscale;
		togiveback.modificator = modelconvert.modificators;
	//	togiveback.name = modelconvert.name;
		togiveback.path = modelconvert.path;
		togiveback.uniqueid = modelconvert.uniqueid;

		return togiveback;
	}
};

//public:
//	meshlist mshli;
//	mdllist mdlli;
//
//	std::string names = "Null";
//	std::vector < std::string> namesvec;
//	
//	
//	Texture defaultext;
//	int ids = -1;
//
//	void redoposmesh(int inid) {
//		auto fun = mshli.MeshVec.at(get_real_id(inid));
//		
//	}
//
//	void addmesh(Mesh added_mesh, std::string name, int type) {
//		/*
//		1 - Полигон
//
//
//
//
//		*/
//
//		defaultext = LoadTexture("textures/def.png");
//
//		if (ids == -1) {
//			names = name;
//			namesvec.push_back(name);
//
//		}
//		else {
//			namesvec.push_back(name);
//		}
//		ids++;
//
//		Matrix matcool;
//		Material cooolmaterial;
//		cooolmaterial = LoadMaterialDefault();
//		cooolmaterial.maps->texture = defaultext;
//		cooolmaterial.maps->color = WHITE;
//		//cooolmaterial.shader = LoadShader();
//		meshobj adder;
//
//		
//		matcool = MatrixIdentity(); //180 градусов. Так удобнее прост. 
//		adder.modelmesh = added_mesh;
//		adder.id = ids;
//		adder.name = name;
//		adder.meshmatrix = matcool;
//		adder.meshmaterial = cooolmaterial;
//		adder.meshscale = { 1,1,1 };
//		adder.meshrotaxis ={ dtr(180),0,0 };
//		adder.meshmatrix = MatrixRotateXYZ(adder.meshrotaxis);
//
//		auto BoundBoxForCoords = GetMeshBoundingBox(adder.modelmesh);
//		BoundBoxForCoords = {Vector3Transform(BoundBoxForCoords.min, adder.meshmatrix),Vector3Transform(BoundBoxForCoords.max, adder.meshmatrix) };
//
//		adder.boxer = BoundBoxForCoords;
//
//		adder.meshposition.x = ((BoundBoxForCoords.max.x + BoundBoxForCoords.min.x) / 2);
//		adder.meshposition.y = ((BoundBoxForCoords.max.y + BoundBoxForCoords.min.y) / 2);
//		adder.meshposition.z = ((BoundBoxForCoords.max.z + BoundBoxForCoords.min.z) / 2);
//
//		mshli.MeshIdVec.push_back(ids);
//		mshli.MeshVec.push_back(adder);
//		std::cout << "done";
//	}
//	void redomesh(int id) {
//
//	}
//
//	int get_obj_id(int id) {
//
//		/*
//		-1 Никакой тип
//		0 
//		1 Тип Мэша.
//		2 Тип Модельки.
//		
//		*/
//
//		if (ids == -1) {
//			return -1; //Ничего не добавлено лол.
//		}
//		int founder = 0;
//		for (auto finders : mshli.MeshIdVec) { //Проходим в поисках через мэши сначала.
//			if (finders == id) {
//				return (1); //Именно. Отдаём в формате 10 + что-то, не лучший выбор ну херли нам, вторая цифра является подтипом.
//			}
//			founder++;
//		}
//		founder = 0;
//		for (auto finders : mdlli.MdlIdVec) { //Через модели.
//			if (finders == id) {
//				return (2); //Именно
//			}
//			founder++;
//
//	}
//	}
//
//	void reloadnames() {
//		auto maxth = std::max(mshli.MeshVec.size(),mdlli.MdlVec.size());
//		for (int index = 0; index < maxth; index++) {
//			if ((mshli.MeshVec.size() < index)&&(mshli.MeshVec[index].id == index)) {
//
//			}
//			if ((mdlli.MdlVec.size() < index) && (mdlli.MdlVec[index].id == index)) {
//
//			}
//		}
//	}
//
//	int get_real_id(int id) {
//		int founder = 0;
//		for (int finders : mshli.MeshIdVec) { //Через модели
//			if (finders == id) {
//				return (founder); //Именнdо.
//			}
//			founder++;
//		}
//		}
//	void deleteobj(int id) {
//		int type = get_obj_id(id);
//		switch ((type))
//		{
//		case 1: //Удаление мэша. 
//			mshli.MeshVec[get_real_id(id)].boxer;
//			UnloadMaterial(mshli.MeshVec[get_real_id(id)].meshmaterial);
//			UnloadMesh(mshli.MeshVec[get_real_id(id)].modelmesh);
//			UnloadMesh(mshli.MeshVec[get_real_id(id)].colisionmesh);
//			mshli.MeshVec.erase(mshli.MeshVec.begin() + get_real_id(id), mshli.MeshVec.end() - get_real_id(id));
//			mshli.MeshIdVec.erase(mshli.MeshIdVec.begin() + get_real_id(id), mshli.MeshIdVec.end() - get_real_id(id));
//			ids--;
//
//			break;
//
//		default:
//			break;
//		} 
//	}
//	void duplicateobject(int id) {
//		int type = get_obj_id(id);
//		switch ((type))
//		{
//		case 1: //Удаление мэша. 
//
//			mshli.MeshVec.push_back(mshli.MeshVec[get_real_id(id)]);
//			mshli.MeshIdVec.push_back(ids);
//			mshli.MeshVec[get_real_id(id)].id = ids;
//			
//
//			break;
//
//		default:
//			break;
//		}
//	}