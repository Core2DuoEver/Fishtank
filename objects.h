#pragma once


#include "raylib.h"; //Нужна для отображения графики
#include "raymath.h"; //Нужна для преобразований матрицы.

#include <cstdlib>;
#include <iostream>;
#include <vector>;

#include <fstream>;

/*
class materialplus {
public:
	Material mat;
	std::string name;
	std::string path;
};
class materialdb {
public:
	std::vector<materialplus> matdb;
	std::vector<materialplus> active;
	std::vector<std::vector<materialplus>> matpages;
	std::string materialspath = "textures//";
	void initdb() {
		FilePathList fom;
		fom = LoadDirectoryFiles(materialspath.c_str());
		//fom = LoadDirectoryFilesEx(materialspath.c_str(), ".png", false);
		if (fom.capacity != 0) {

			for (auto lol : matdb) {
				UnloadMaterial(lol.mat);
			}
			matdb.clear();

			for (int poing = 0; poing < fom.capacity; poing++) {
				if (IsFileExtension(fom.paths[poing], ".png")) {
					materialplus pus;
					Image flipper;
					pus.mat = LoadMaterialDefault();
					flipper = LoadImage(fom.paths[poing]);
					//ImageFlipHorizontal(&flipper);
					//ImageFlipVertical(&flipper);
					//ImageRotate(&flipper, 180);
					
					pus.path = (fom.paths[poing]);
					pus.name = GetFileNameWithoutExt(fom.paths[poing]);
					pus.mat.maps->texture = LoadTextureFromImage(flipper);
					
					UnloadImage(flipper);

					matdb.push_back(pus);
				}
			}
		}
	}
	void addtexture(std::string name) {
		
	}
	void addshader() {

	}
	void addparam() {

	}
};
*/
class matplus {
public:
	std::string path;
	std::string name;
	Material mat;
	Texture preview;
};
class materialdb {
public:
	std::vector<matplus> db;

	bool is_init = false;

	void intdb() {
			auto fomo = LoadDirectoryFiles("materials\\");
			for (int poing = 0; poing < fomo.capacity; poing++) {
				if (IsFileExtension(fomo.paths[poing], ".Folder")) {
					matplus newone;
					newone.mat = LoadMaterialDefault();
					newone.path = fomo.paths[poing];
					newone.name = GetFileNameWithoutExt(fomo.paths[poing]);
					
					auto fumo = LoadDirectoryFiles(fomo.paths[poing]);

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

					std::vector<std::string> namesf = { "ALBEDO.png","METALNESS.png","NORMAL.png","ROUGHNESS.png","OCCLUSION.png","EMISSION.png","HEIGHT.png","CUBEMAP.png","IRRIDIANCE.png","PREFILTER.png","BRDF.png" };

					//if (hsh(std::string(GetFileName(fumo.paths[poing]))) == strds[0]) {

						
					for (int ind = 0; ind <= 10; ind++) {
						std::string tmp_name = fomo.paths[poing] + std::string("//") + namesf[ind];
						//Texture2D tmp_txt = LoadTexture(tmp_name.c_str());

						//if (tmp_txt.format != NULL) {

						SetMaterialTexture(&newone.mat, ind, LoadTexture(tmp_name.c_str()));

						//}

						}
					

					//}
				
			//		std::ifstream binaryfile((fumo.paths[poing] + std::string("mat.mati")).c_str(), std::ios::binary);
					auto lofff = fomo.paths[poing] + std::string("//mat.mati");
					std::ifstream binaryfile(lofff.c_str(), std::ios::binary);
					binaryfile.read(reinterpret_cast<char*>(&newone.mat.maps->value), sizeof(newone.mat.maps->value));

					short int togo;

					binaryfile.read(reinterpret_cast<char*>(&togo), sizeof(togo));
		//			binaryfile.read(reinterpret_cast<char*>(&togo), sizeof(togo));

					if (togo == 1) {
						std::string shd;

						size_t pathtxt_size; //Загружаем размер путя текстур.
						binaryfile.read(reinterpret_cast<char*>(&pathtxt_size), sizeof(pathtxt_size)); //Читаем размерчик.
						shd.resize(pathtxt_size);
						binaryfile.read(&shd[0], pathtxt_size);

						newone.mat.shader = LoadShader(NULL, shd.c_str());
					}
					if (togo != -1) {
						//lol no shader
					}


					//                    matinfo.write(reinterpret_cast<char*>(&mat_new.maps->value), sizeof(mat_new.maps->value)); //Сохраняем два!
// short int fuckoff = 1;
//					matinfo.write(reinterpret_cast<char*>(&fuckoff), sizeof(fuckoff)); //Сохраняем тот факт что шейдера есть.

					// matinfo.write(reinterpret_cast<char*>(&pathsize), sizeof(pathsize)); //Сохраняем раз!
					//matinfo.write(shadernam.c_str(), pathsize);

					std::string tmp2_name = fomo.paths[poing] + std::string("//PREVIEW.png");

					newone.preview = LoadTexture(tmp2_name.c_str());

					db.push_back(newone);

					binaryfile.close();

				}
			}
			is_init = true;

		}


	void redb() {
		for (auto clr : db) {
			UnloadMaterial(clr.mat);
			UnloadTexture(clr.preview);
		}
		db.clear();
		is_init = false;
	}
};

class savemesh {
public:
	std::string pathmdl;
	std::string pathtxt;
	std::string name;

	Color savecolor;

	Matrix meshmatrix; //Матрица 4х4 для позиции 

	Vector3 meshposition; //Названия говорят за себя.
	Vector3 meshrotaxis;
	Vector3 meshscale;

	int modificator;
	int uniqueid;
	int id; //Тип мэша.
};
class savemodel {
public:
	std::string path;
	std::string name;

	Vector3 modelposition; //Названия говорят за себя.
	Vector3 modelrotaxis;
	Vector3 modelscale;

	int uniqueid;
	int modificator;

	Matrix matrixmodel;
};


class meshobj { //Обьект мэша.
public:
	
	Mesh modelmesh; //Модель
	Mesh colisionmesh; //Модель колизии (если есть)
	
	matplus matpl;

	Material meshmaterial; //Материал
	Matrix meshmatrix; //Матрица 4х4 для позиции транспоцизззицизццидиалолаоплаопл
	
	//std::string texturepathnam = "textures//def.png";

	int modificators =0; //Для дополнительных свойств.

	bool active = false;
	//10 - Загружена.
	//
	//
	std::string commentary; //Для комментариев и другого мусора.
	std::string name = "Mesh";

	int uniqueid;

	Vector3 meshposition; //Названия говорят за себя.
	Vector3 meshrotaxis;
	Vector3 meshscale;

	int id; //Тип мэша.

};

class modelobj { //Обьект мэша.
public:
	Model modelmdl; //Модуль ага.
	Mesh colisionmesh; //Модель колизии (если есть)

	//short int id; //Тип модели.

	int uniqueid;

	Vector3 modelposition; //Названия говорят за себя.
	Vector3 modelrotaxis;
	Vector3 modelscale;
	
	Matrix matrixmodel;

	std::string path;

	int modificators = 0; //Для дополнительных свойств.
	std::string commentary; //Для комментариев и другого мусора.

	std::string name = "Model";
};

class meshlist {
public:
	std::vector<meshobj> MeshVec; //Список мешей.
};
class mdllist {
public:
	std::vector<modelobj> MdlVec; //Список мешей.
};
class objnaming {
public:
	std::string name;
	int indexnamed;
	int namindex;
	int type;
	//New thing?
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