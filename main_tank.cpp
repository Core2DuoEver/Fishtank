
#include "Bait.h";
#include "graphical.h"
#include "objects.h";

objectdatabase objdb;
materialdb TexturesDB;

int activeid = -1;

bool TextureReloadButton = false;

bool FileDropEditMode = false;
bool MaterialDropEditMode = false;

int FileDropActive = 0;
int MaterialDropActive = 0;

int ObjListScrollIndex = 0;
int ObjListActive = 0;

bool MeshAddBtnPressed = false;
bool EntAddBtnPressed = false;
bool MdlAddBtnPressed = false;
bool PolyMeshBtnPressed = false;
bool PlaneMeshBtnPressed = false;
bool CubeMeshBtnPressed = false;
bool CylinderMeshBtnPressed = false;
bool SphereMeshBtnPressed = false;
bool ConeMeshBtnPressed = false;
bool TorusMeshBtnPressed = false;
bool KnotMeshBtnPressed = false;
bool HalfSphereBtnPressed = false;


bool xtextboxbool = false;
bool ytextboxbool = false;
bool ztextboxbool = false;
char xtextbox[128] = "";
char ytextbox[128] = "";
char ztextbox[128] = "";

int chosen_map = 0;
bool mat_map_bool = false;

int choser_mod = 0;
bool choser_mod_bool = false;
int choser_mod_mesh = 0;
bool choser_mod_bool_mesh = false;

int chosen_wrap = 0;
bool mat_wrap_bool = false;

bool SidesTextEditMode = false;
char SidesTextText[128] = "1";
bool RadiusTextEditMode = false;
char RadiusTextText[128] = "1";
bool NameTextEditMode = false;
char NameTextText[128] = "";
bool texturePressed = false;

Color ColorPicker032Value = { 0, 0, 0, 0 };

bool ResYTextEditMode = false;
char ResYTextText[128] = "1";
bool NameBoxEditMode = false;
char NameBoxText[128] = "";
bool ResXTextEditMode = false;
char ResXTextText[128] = "1";

bool RadiusEditMode = false;
char RadiusText[128] = "1";
bool RingsEditMode = false;
char RingsText[128] = "1";
bool SlicesEditMode = false;
char SlicesText[128] = "3";
bool NameSphereEdit = false;
char NameSphereText[128] = "1";

bool RadiusCylinderEditMode = false;
char RadiusCylinderText[128] = "1";
bool HeightCylinderEditMode = false;
char HeightCylinderText[128] = "1";
bool SlicesCylinderEditMode = false;
char SlicesCylinderText[128] = "3";
bool NameCylinderEdit = false;
char NameCylinderText[128] = "1";

bool WidthEditMode = false;
char WidthText[128] = "1";
bool LengthEditMode = false;
char LengthText[128] = "1";
bool HeightEditMode = false;
char HeightText[128] = "1";
bool NameCubeEdit = false;
char NameCubeText[128] = "1";

bool LengthTextEditMode = false;
char LengthTextText[128] = "1";
bool WidthTextEditMode = false;
char WidthTextText[128] = "1";


bool TexturechooserActive = false;
bool SliderPageEditMode = false;
int SliderPageValue = 0;
bool TextureButton01Pressed = false;
bool TextureButton03Pressed = false;
bool TextureButton02Pressed = false;
bool TextureButton04Pressed = false;
bool TextureButton05Pressed = false;
bool TextureButton06Pressed = false;
bool TextureButton07Pressed = false;
bool TextureButton08Pressed = false;
bool TextureButton09Pressed = false;
bool Button056Pressed = false;

bool materialcreate = false;

bool spinner_bool_mat = false;
int spinner_int_mat = 0;

float colora = 255;

bool meshactive = false;
bool mdlactive = false;

int chosen_comp = 0;
bool chosen_comp_bool = false;

Material mat_new;
std::vector<Texture2D> mat_materials;

 void MeshAddBtn(){
 }

 void EntAddBtn() {

 }

 void MdlAddBtn() {

     std::string winname = "Save";
     std::string folder = std::string(GetWorkingDirectory()) + "\\models\\";
     const char* filters[] = { "*.obj" };  // Маски файлов

    // auto pathfor = tinyfd_saveFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Wavefront model (*.obj)");

     auto pathfor = tinyfd_openFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Wavefront model (*.obj)", 1);
     if (pathfor != NULL) {
         objdb.addmodel((LoadModel(pathfor)), GetFileNameWithoutExt(pathfor), pathfor);
     }
 }
 void FileBtn(int in) {
     switch (in) { 
     case 0: break; //nufin happens
     case 1: { //сохранение


         std::string winname = "Save";
         std::string folder = std::string(GetWorkingDirectory()) + "\\mapsave.zip";
         const char* filters[] = { "*.zip" };  // Маски файлов

         auto pathfor = tinyfd_saveFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Map save (*.zip)");
         
         if (pathfor != NULL) {
             fs::remove_all("save_tmp");

             
             savedb realsaver;
                
             fs::path panher = "save_tmp";
             fs::create_directories(panher);
             //ZIP и сохранение 
             int err;
             zip_t* zip_archive = zip_open(pathfor, ZIP_CREATE | ZIP_TRUNCATE, &err);


             

             fs::path identyi = "save_tmp\\map.dummy"; //Пустой файл.
             std::ofstream idenfile(identyi.string(), std::ios::binary);
             idenfile.close();

             zip_source* ss = zip_source_file(zip_archive,identyi.string().c_str(), 0, 0);
             int indexx = zip_file_add(zip_archive, std::string("map.dummy").c_str(), ss, ZIP_FL_OVERWRITE); //Сохраняем модель.
             time_t xnow = time(nullptr);
             zip_file_set_mtime(zip_archive, indexx, xnow, 0);

             int saveind = 0;
             for (auto coolaid : objdb.msdb.MeshVec) {

                 std::string meshsavename = "save_tmp\\mesh" + std::to_string(saveind) + ".obj";
                 ExportMesh(coolaid.modelmesh, meshsavename.c_str());


                 auto mst = realsaver.meshtosave(coolaid);
                 //лол
                 fs::path fileobj = "save_tmp\\meshdata" + std::to_string(saveind) + ".meshbin";
                 std::ofstream mshdata(fileobj.string(), std::ios::binary); //Создаём файл.
                 mst.pathmdl = meshsavename;

                 size_t pathsize = mst.pathmdl.size();
                 mshdata.write(reinterpret_cast<char*>(&pathsize), sizeof(pathsize)); //Сохраняем раз!
                 mshdata.write(mst.pathmdl.c_str(), pathsize);

                 size_t texturesize = mst.pathtxt.size();
                 mshdata.write(reinterpret_cast<char*>(&texturesize), sizeof(texturesize)); //Сохраняем два!
                 mshdata.write(mst.pathtxt.c_str(), texturesize);

                 mshdata.write(reinterpret_cast<char*>(&mst.savecolor), sizeof(Color)); //Сохраняем два!

                 mshdata.write(reinterpret_cast<char*>(&mst.id), sizeof(int)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.meshmatrix), sizeof(Matrix)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.meshposition), sizeof(Vector3)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.meshrotaxis), sizeof(Vector3)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.meshscale), sizeof(Vector3)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.uniqueid), sizeof(int)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.modificator), sizeof(int)); //Сохраняем два!

                 size_t namesize = mst.name.size();
                 mshdata.write(reinterpret_cast<char*>(&namesize), sizeof(size_t)); //Сохраняем два!
                 mshdata.write(mst.name.c_str(), namesize);


                 mshdata.close();

                 zip_source* s = zip_source_file(zip_archive, meshsavename.c_str(), 0, 0);
                 int index = zip_file_add(zip_archive, ("mesh" + std::to_string(saveind) + ".obj").c_str(), s, ZIP_FL_OVERWRITE); //Сохраняем модель.
                 time_t now = time(nullptr);
                 zip_file_set_mtime(zip_archive, index, now, 0);

                 s = zip_source_file(zip_archive, fileobj.string().c_str(), 0, 0);
                 index = zip_file_add(zip_archive, ("meshdata" + std::to_string(saveind) + ".meshbin").c_str(), s, ZIP_FL_OVERWRITE); //Сохраняем модель.
                 zip_file_set_mtime(zip_archive, index, now, 0);



                 saveind++;
             }
             for (auto coolaid : objdb.mdldb.MdlVec) {

                //std::string modelsa = "save_tmp\\mesh" + std::to_string(saveind) + ".obj";
                // ExportMesh(coolaid.modelmesh, meshsavename.c_str());


                 auto mst = realsaver.modelsave(coolaid);
                 //лол
                 fs::path fileobj = "save_tmp\\modeldata" + std::to_string(saveind) + ".modelbin";
                 std::ofstream mshdata(fileobj.string(), std::ios::binary); //Создаём файл.

                 size_t pathsize = mst.path.size();
                 mshdata.write(reinterpret_cast<char*>(&pathsize), sizeof(pathsize)); //Сохраняем раз!
                 mshdata.write(mst.path.c_str(), pathsize);

                
                 mshdata.write(reinterpret_cast<char*>(&mst.matrixmodel), sizeof(Matrix)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.modelposition), sizeof(Vector3)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.modelrotaxis), sizeof(Vector3)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.modelscale), sizeof(Vector3)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.uniqueid), sizeof(int)); //Сохраняем два!
                 mshdata.write(reinterpret_cast<char*>(&mst.modificator), sizeof(int)); //Сохраняем два!

                 size_t namesize = mst.name.size();
                 mshdata.write(reinterpret_cast<char*>(&namesize), sizeof(size_t)); //Сохраняем два!
                 mshdata.write(mst.name.c_str(), namesize);


                 mshdata.close();

                 zip_source* s = zip_source_file(zip_archive, fileobj.string().c_str(), 0, 0);
                 int index = zip_file_add(zip_archive, ("modeldata" + std::to_string(saveind) + ".modelbin").c_str(), s, ZIP_FL_OVERWRITE); //Сохраняем модель.
                 time_t now = time(nullptr);
                 zip_file_set_mtime(zip_archive, index, now, 0);


                 saveind++;
             }

             fs::path fileobj = "save_tmp\\namedata.namebin";
             std::ofstream namers(fileobj.string(), std::ios::binary); //Создаём файл.

             int sizeff = objdb.names.size();

             namers.write(reinterpret_cast<char*>(&sizeff), sizeof(int)); //Записываем количество, размер вектора.

             for (auto oo : objdb.names) {

                 size_t namemain = oo.name.size();
                 namers.write(reinterpret_cast<char*>(&namemain), sizeof(namemain));
                 namers.write(oo.name.c_str(), namemain);

                 namers.write(reinterpret_cast<char*>(&oo.indexnamed), sizeof(int)); //Сохраняем два!
                 namers.write(reinterpret_cast<char*>(&oo.namindex), sizeof(int)); //Сохраняем два!
                 namers.write(reinterpret_cast<char*>(&oo.type), sizeof(int)); //Сохраняем два!

             }

             namers.write(reinterpret_cast<char*>(&objdb.lastid), sizeof(int)); //Сохраняем два!

             namers.close(); //Закрываем имена.

             zip_source* s = zip_source_file(zip_archive, fileobj.string().c_str(), 0, 0);
             int index = zip_file_add(zip_archive, std::string("namedata.namebin").c_str(), s, ZIP_FL_OVERWRITE); //Сохраняем модель.
             time_t now = time(nullptr);
             zip_file_set_mtime(zip_archive, index, now, 0);

             

             auto fun = zip_close(zip_archive);

             fs::remove_all("save_tmp"); //Удаляем всё из TMP
         }
         //std::cout << fun;
     }
         break;

     case 2: { //Загрузка
        

         std::string winname = "Save";
         std::string folder = std::string(GetWorkingDirectory()) + "\\mapsave.zip";
         const char* filters[] = { "*.zip" };  // Маски файлов

         auto forl = tinyfd_openFileDialog(winname.c_str(),folder.c_str(),1,filters,"Map save (*.zip)",0);

         if (forl != NULL) {
             int error;
             zip_t* zip_archive = zip_open(forl, ZIP_RDONLY, &error); //Открыаем архив.

             if (zip_archive) { //Архив и вправду открылся
                 fs::remove_all("save_tmp");
                 fs::create_directories("save_tmp");

                 zip_int64_t numFiles = zip_get_num_entries(zip_archive, 0); //количество файлов.

                 std::vector<std::string> filenames;

                 if (numFiles > 2) { //Если внутри больше двух файлов (ИДЕНТИФИКАТОРА И ИМЁН)

                         for (zip_int64_t ind = 0; ind < numFiles; ind++) {

                             zip_stat_t fileInfo;

                             zip_stat_init(&fileInfo);

                             zip_stat_index(zip_archive, ind, 0, &fileInfo);



                             fs::path filer = fs::path("save_tmp") / fileInfo.name;

                             filenames.push_back(fileInfo.name); //Записываем имена и пути файлов Так удобнее пройтись по каждому.

                             zip_file_t* file = zip_fopen_index(zip_archive, ind, 0);
                             if (!file) {
                                 std::cout << "ZIP FILE ERROR";
                             }
                             std::ofstream outFile(filer.string(), std::ios::binary);

                             std::vector<char> buffer(1024 * 16); //На 16 килобайт буффер.

                             zip_int64_t bytesRead;
                             while ((bytesRead = zip_fread(file, buffer.data(), buffer.size())) > 0) {
                                 outFile.write(buffer.data(), bytesRead);
                             }
                             outFile.close();
                             zip_fclose(file);

                         }
                     zip_close(zip_archive);
                     //ЕЕЕЕ распокавали.
                     //ОЧИСТКА БАЗ.

                     int fol = 0;
                     for (int inx = 0; inx < objdb.msdb.MeshVec.size(); inx++) {
                      
                         UnloadMesh(objdb.msdb.MeshVec[inx].modelmesh);
                         UnloadMaterial (objdb.msdb.MeshVec[inx].meshmaterial);
                         

                       //  objdb.msdb.MeshVec.erase(objdb.msdb.MeshVec.begin() + inx); //Стёрли.
                     }
                     for (int inx = 0; inx < objdb.mdldb.MdlVec.size(); inx++) {

                         if (objdb.mdldb.MdlVec[inx].modelmdl.meshes->vaoId != 0xdddddddd) {

                             UnloadModel(objdb.mdldb.MdlVec[inx].modelmdl);
                            // objdb.mdldb.MdlVec.erase(objdb.mdldb.MdlVec.begin() + inx); //Стёрли.

                         }
                     }
                     objdb.mdldb.MdlVec.clear();
                     objdb.msdb.MeshVec.clear();

                     fol = 0;
                     
                     objdb.name = "Null";
                     objdb.names.clear();
                     objdb.lastid = -1;


                     for (auto to_load : filenames) { //Проходим через каждый файл.
                            
                         auto extname = GetFileExtension(to_load.c_str());
                         
                         auto exhash = std::hash<std::string>{}(extname);

                         

                       //  std::cout << exhash << " " << extname << "\n";

                         if (exhash == std::hash<std::string>{}(".meshbin")) {
                             objdb.lastid = objdb.lastid + 1;

                             meshobj msh;

                             fs::path bintoload = "save_tmp//" + to_load; //Делаем норм путь.

                             std::ifstream binaryfile(bintoload.string(), std::ios::binary);

                             size_t pathmdl_size; //Загружаем размер путя.
                             binaryfile.read(reinterpret_cast<char*>(&pathmdl_size), sizeof(size_t)); //Читаем размерчик.

                             std::string mdlpath;

                             mdlpath.resize(pathmdl_size); //Разжимаем до нужного
                             binaryfile.read(&mdlpath[0], pathmdl_size);

                             Model shoot;
                             shoot = LoadModel(mdlpath.c_str());
                             msh.modelmesh = shoot.meshes[0]; //Просто копируем сюда)
                             //НЕ АНЛОАДАЕМ!

                             size_t pathtxt_size; //Загружаем размер путя текстур.
                             binaryfile.read(reinterpret_cast<char*>(&pathtxt_size), sizeof(pathtxt_size)); //Читаем размерчик.
                             msh.matpl.path.resize(pathtxt_size);
                             binaryfile.read(&msh.matpl.path[0], pathtxt_size);


                             matplus newone;
                             newone.mat = LoadMaterialDefault();


                             auto lofff = msh.matpl.path + std::string("//mat.mati");

                             std::vector<std::string> namesf = { "ALBEDO.png","METALNESS.png","NORMAL.png","ROUGHNESS.png","OCCLUSION.png","EMISSION.png","HEIGHT.png","CUBEMAP.png","IRRIDIANCE.png","PREFILTER.png","BRDF.png" };


                             for (int ind = 0; ind <= 10; ind++) {
                                 std::string tmp_name = msh.matpl.path + std::string("//") + namesf[ind];

                                 Image to_flip = LoadImage(tmp_name.c_str());

                                 ImageFlipVertical(&to_flip);

                                 SetMaterialTexture(&newone.mat, ind, LoadTextureFromImage(to_flip));

                                 UnloadImage(to_flip);

                             }

                             std::ifstream bifile(lofff.c_str(), std::ios::binary);
                             bifile.read(reinterpret_cast<char*>(&newone.mat.maps->value), sizeof(newone.mat.maps->value));

                             short int togo;

                             bifile.read(reinterpret_cast<char*>(&togo), sizeof(togo));

                             if (togo == 1) {
                                 std::string shd;

                                 size_t pathtxt_size; //Загружаем размер путя текстур.
                                 bifile.read(reinterpret_cast<char*>(&pathtxt_size), sizeof(pathtxt_size)); //Читаем размерчик.
                                 shd.resize(pathtxt_size);
                                 bifile.read(&shd[0], pathtxt_size);

                                 newone.mat.shader = LoadShader(NULL, shd.c_str());
                             }
                             if (togo != -1) {
                                 //lol no shader
                             }

                             bifile.close();

                             std::string tmp2_name = msh.matpl.path + std::string("//PREVIEW.png");

                             Image to_flip = LoadImage(tmp2_name.c_str());

                             //  ImageFlipVertical(&to_flip);

                             newone.preview = LoadTextureFromImage(to_flip);

                             UnloadImage(to_flip);

                             Color tocolor;

                             msh.meshmaterial = newone.mat;

                             msh.matpl = newone;

                             binaryfile.read(reinterpret_cast<char*>(&tocolor), sizeof(Color));

                             msh.meshmaterial.maps->color = tocolor;

                             binaryfile.read(reinterpret_cast<char*>(&msh.id), sizeof(int));
                             binaryfile.read(reinterpret_cast<char*>(&msh.meshmatrix), sizeof(Matrix));
                             binaryfile.read(reinterpret_cast<char*>(&msh.meshposition), sizeof(Vector3));
                             binaryfile.read(reinterpret_cast<char*>(&msh.meshrotaxis), sizeof(Vector3));
                             binaryfile.read(reinterpret_cast<char*>(&msh.meshscale), sizeof(Vector3));
                             binaryfile.read(reinterpret_cast<char*>(&msh.uniqueid), sizeof(int));
                             binaryfile.read(reinterpret_cast<char*>(&msh.modificators), sizeof(int));

                             objnaming objnam;

                             size_t name_size; //Загружаем размер путя текстур.
                             binaryfile.read(reinterpret_cast<char*>(&name_size), sizeof(name_size)); //Читаем размерчик.

                             std::string naml;

                             naml.resize(name_size);
                             binaryfile.read(&naml[0], name_size);

                             objdb.addmesh(msh.modelmesh, naml, msh.id);

                             objdb.msdb.MeshVec[objdb.msdb.MeshVec.size() - 1].meshmaterial = msh.meshmaterial;
                             objdb.msdb.MeshVec[objdb.msdb.MeshVec.size() - 1].meshmatrix = msh.meshmatrix;
                             objdb.msdb.MeshVec[objdb.msdb.MeshVec.size() - 1].meshposition = msh.meshposition;
                             objdb.msdb.MeshVec[objdb.msdb.MeshVec.size() - 1].meshscale = msh.meshscale;
                             objdb.msdb.MeshVec[objdb.msdb.MeshVec.size() - 1].meshrotaxis = msh.meshrotaxis;

                             /*
                             objnam.name = naml;
                             objnam.type = obj_mesh;
                             objnam.namindex = objdb.lastid; //Записываем позицию для текста
                             objnam.indexnamed = objdb.msdb.MeshVec.size(); //Записываем позицию для векторного мэша.

                             msh.modificators = 10; //Загрузили вне.

                             objdb.names.push_back(objnam);
                             
                             objdb.msdb.MeshVec.push_back(msh); //Добавляем в вектор;
                             */
                             

                             binaryfile.close(); //Закрываем файл.

                            // objdb.reloadnames();
                         }
                         if (exhash == std::hash<std::string>{}(".modelbin")) {
                             objdb.lastid = objdb.lastid + 1;

                             modelobj toadd;

                             fs::path bintoload = "save_tmp//" + to_load; //Делаем норм путь.

                             std::ifstream binaryfile(bintoload.string(), std::ios::binary);

                             size_t pathmdl_size; //Загружаем размер путя.
                             binaryfile.read(reinterpret_cast<char*>(&pathmdl_size), sizeof(size_t)); //Читаем размерчик.

                             std::string mdlpath;

                             mdlpath.resize(pathmdl_size); //Разжимаем до нужного
                             binaryfile.read(&mdlpath[0], pathmdl_size);

                             binaryfile.read(reinterpret_cast<char*>(&toadd.matrixmodel), sizeof(Matrix));
                             binaryfile.read(reinterpret_cast<char*>(&toadd.modelposition), sizeof(Vector3));
                             binaryfile.read(reinterpret_cast<char*>(&toadd.modelrotaxis), sizeof(Vector3));
                             binaryfile.read(reinterpret_cast<char*>(&toadd.modelscale), sizeof(Vector3));
                             binaryfile.read(reinterpret_cast<char*>(&toadd.uniqueid), sizeof(int));
                             binaryfile.read(reinterpret_cast<char*>(&toadd.modificators), sizeof(int));

                             pathmdl_size; //Загружаем размер путя.
                             binaryfile.read(reinterpret_cast<char*>(&pathmdl_size), sizeof(size_t)); //Читаем размерчик.

                             toadd.name.resize(pathmdl_size); //Разжимаем до нужного
                             binaryfile.read(&toadd.name[0], pathmdl_size);

                             binaryfile.close();

                             objdb.addmodel(LoadModel(mdlpath.c_str()), "Toadd", mdlpath);

                             objdb.mdldb.MdlVec[objdb.mdldb.MdlVec.size() - 1].matrixmodel = toadd.matrixmodel;
                             objdb.mdldb.MdlVec[objdb.mdldb.MdlVec.size() - 1].modelposition = toadd.modelposition;
                             objdb.mdldb.MdlVec[objdb.mdldb.MdlVec.size() - 1].modelrotaxis = toadd.modelrotaxis;
                             objdb.mdldb.MdlVec[objdb.mdldb.MdlVec.size() - 1].modelscale = toadd.modelscale;
                          //   objdb.mdldb.MdlVec[objdb.mdldb.MdlVec.size() - 1].uniqueid = toadd.uniqueid;

                             //objnaming objnam;
                             /*
                             objnam.name = "Loadedup";
                             objnam.type = obj_mesh;
                             objnam.namindex = objdb.lastid; //Записываем позицию для текста
                             objnam.indexnamed = objdb.mdldb.MdlVec.size(); //Записываем позицию для векторного мэша.
                             */
                             //objdb.names.push_back(objnam);

                             //objdb.mdldb.MdlVec.push_back(toadd); //Добавляем в вектор;

                             //objdb.reloadnames();

                         }
                         
                     }

                     fs::remove_all("save_tmp");

                     ObjListActive = -1;

                 }

             }

         }
         if (forl == NULL) {
             std::cout << "ZIP OPEN ERROR";
         }

         }
           break;
     }
 }
 void PolyMeshBtn() {
     
}
void PlaneMeshBtn(){
}
void CubeMeshBtn() {

}
void CylinderMeshBtn() {

}
void SphereMeshBtn() {

}
void ConeMeshBtn() {

}
void TorusMeshBtn(){
}
void KnotMeshBtn() {

}
void HalfSphereBtn(){

}

void createpolymesh() {
    objdb.addmesh(GenMeshPoly(1, 1), "Poly",1);
}
void createplanemesh() {
    objdb.addmesh(GenMeshPlane(1, 1, 1, 1), "Plane",2);
}
void creatcubemesh() {
    objdb.addmesh(GenMeshCube(1, 1, 1), "Cube",3);
}
void createspheremesh() {
    objdb.addmesh(GenMeshSphere(1, 1, 1), "Sphere",4);
}
void createconermesh() {
    objdb.addmesh(GenMeshCone(1, 1, 1), "Cone",6);
}
void createtorusmesh() {
    objdb.addmesh(GenMeshTorus(1, 1, 1, 1), "Torus",7);
}
void createknotmesh() {
    objdb.addmesh(GenMeshKnot(1.0f, 2.0f, 16, 128), "Knot",8);
}
void createhalfspheremesh() {
    objdb.addmesh(GenMeshHemiSphere(2, 16, 16), "Half-sphere",9);
}
void createcylinder() {
    objdb.addmesh(GenMeshCylinder(1, 1,1), "Cylinder",5);
}
float dtr(float degrees) { //Градусы в радианы.
    auto to_return = degrees * (PI / 180);
    return(to_return);
}
float rtd(float radians) { //Радианы в градусы.
    return((radians / 180.0f) * PI);
}

void materialbtn(int in) {

    switch (in)
    {
    case 0: break;
    case 1: {



        materialcreate = true;

    }
          break;

    case 2: {




    }
          break;
    }

}
void compilebtn(int in) {



    switch (in)
    {
    case 0: break;
    case 1: {
        bool no_kooler = false;

        if (!objdb.msdb.MeshVec.empty()) {
            for (auto obd : objdb.msdb.MeshVec) {
                if (obd.modificators == nav_walkable) {
                    no_kooler = true;
                }
            }
            if (!no_kooler) {
                std::cout << "No walkable meshes! \n";
            }
        }

        if (no_kooler) {

            std::vector<meshobj> colvec;

            for (auto loag : objdb.msdb.MeshVec) {
                if (loag.modificators == col_solid) {
                    colvec.push_back(loag);
                }
            }

            std::vector<Vector3> verticespoints;

            for (auto goal : objdb.msdb.MeshVec) {
                //std::cout << goal.modelmesh.vertexCount;
                if (goal.modificators == col_walkable) {
                    Matrix normalMatrix = MatrixTranspose(MatrixInvert(goal.meshmatrix));
                    const Vector3 worldUp = { 0, 1, 0 };
                    for (int a = 0; a < goal.modelmesh.vertexCount; a++) {

                        Vector3 normal = {
                             goal.modelmesh.normals[a * 3],     // X
                             goal.modelmesh.normals[a * 3 + 1], // Y
                             goal.modelmesh.normals[a * 3 + 2]  // Z
                        };
                        Vector3 worldNormal = TransformNormal(normal, goal.meshmatrix);
                        worldNormal = Vector3Normalize(worldNormal);
                        //change!

                        // Проверка направления
                        float dot = Vector3DotProduct(worldNormal, worldUp);

                        if (dot > 0.75) {

                            Vector3 vertex = {
                                goal.modelmesh.vertices[a * 3],
                                goal.modelmesh.vertices[a * 3 + 1],
                                goal.modelmesh.vertices[a * 3 + 2]
                            };
                            Vector3 worldVertex = Vector3Transform(vertex, goal.meshmatrix);
                            /*
                            bool iscolided = true;
                            for (auto testing : colvec) {

                                Vector3 worldvertef = worldVertex;
                                worldvertef.y += fabs(testing.meshposition.y)+100;
                                Ray raycheck = {worldVertex,worldvertef};
                                if (GetRayCollisionMesh(raycheck, testing.modelmesh, testing.meshmatrix).hit) {
                                    iscolided = false;
                                }

                            }
                            */
                            //   if (iscolided) {
                            verticespoints.push_back(worldVertex);
                            //std::cout << worldVertex.x << " " << worldVertex.y << " " << worldVertex.z << "\n";
                            // }



                        }
                    }
                }
            }
            std::cout << "\n";

            float max_x = fabs(verticespoints[0].x);
            float max_z = fabs(verticespoints[0].z);
            float min_x = fabs(verticespoints[0].x);
            float min_z = fabs(verticespoints[0].z);


            float max_y = (verticespoints[0].y);
            float min_y = (verticespoints[0].y);


            for (auto findrad : verticespoints) {

                if (findrad.x > max_x) {
                    max_x = (findrad.x);
                }
                if (findrad.z > max_z) {
                    max_z = (findrad.z);
                }
                if (findrad.x < min_x) {
                    min_x = (findrad.x);
                }
                if (findrad.z < min_z) {
                    min_z = (findrad.z);
                }
            }
            
            std::vector<std::vector<navvec>> xandzvecs;
            for (float x = min_x; x < max_x; x = x + colision_precision) {
                std::vector<navvec> zvec;
                for (float z = (min_z); z < max_z; z = z + colision_precision) {

                    Ray raychock;
                    Ray rayup;
                   
                    raychock.position.x = x;
                    raychock.position.z = z;
                    raychock.position.y = max_y+100;

                    raychock.direction.x = 0;
                    raychock.direction.z = 0;
                    raychock.direction.y = -1;

                    rayup.position.x = x;
                    rayup.position.z = z;
                    rayup.position.y = -1;

                    rayup.direction.x = 0;
                    rayup.direction.z = 0;
                    rayup.direction.y = 1;

                    bool solid = false;
                    bool walk = false;
                    RayCollision los;

                    for (auto co : objdb.msdb.MeshVec) {
                        //Проверяем что не затронули.
                        if (co.modificators == col_walkable) {
                            los = GetRayCollisionMesh(raychock, co.modelmesh, co.meshmatrix);
                            if (los.hit) {
                                walk = true;
                                for (auto cols : colvec) {
                                    if (cols.modificators == col_solid) {
                                        RayCollision lost = GetRayCollisionMesh(rayup, cols.modelmesh, cols.meshmatrix);
                                        if (lost.hit) {
                                            solid = true;
                                        }
                                    }
                                }
                            }
                        }

                    }

                    if (solid) {
                        navvec s;
                        s.navec3 = { x,max_y,z };
                        s.mod = nav_solid;
                        zvec.push_back(s);
                    }
                    else if (walk) {
                        navvec s;
                        s.navec3 = { x,max_y-los.distance,z };
                        s.mod = nav_walkable;
                        zvec.push_back(s);
                    }
                    else {
                        navvec s;
                        s.navec3 = { x,0,z };
                        s.mod = nav_no_objects;
                        zvec.push_back(s);
                    }


                }
                xandzvecs.push_back(zvec);
            }

            for (auto la : xandzvecs) {
                for (auto lo : la) {
                    if (lo.mod == nav_walkable) {
                        //SetColor(32);
                        std::cout << lo.mod << " ";
                        //ResetColor;
                    }
                    if (lo.mod == nav_solid) {
                        //SetColor(31);
                        std::cout << lo.mod << " ";
                       // ResetColor;
                    }
                    if (lo.mod == nav_no_objects) {
                        std::cout << lo.mod << " ";
                    }
                }
                std::cout << "\n";
            }
            std::cout << "\n";
            std::cout << "\n";


        }
    }
          break;

    case 2: {




    }
          break;
    }
}

int notmain() {


    InitWindow(screen_width, screen_height, window_name.c_str());
    RenderTexture DevScreen = LoadRenderTexture(800, 600);
    RenderTexture PreviewScreen = LoadRenderTexture(200, 200);

   // TexturesDB.intdb();

    Mesh stdmesh = GenMeshCube(5, 5, 5);

    Camera3D precamera = { 0 };
    precamera.position = { 5.0f, 5.0f, 5.0f }; // Camera position
    precamera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    precamera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    precamera.fovy = 90.0f;                                // Camera field-of-view Y
    precamera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    std::string shadernam = "";

    char save_name[128] = "Default";
    bool save_bool = false;

    Camera3D camera = { 0 };
    camera.position = { 5.0f, 5.0f, 5.0f }; // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    ColorPicker032Value.r = 'я';
    ColorPicker032Value.g = 'я';
    ColorPicker032Value.b = 'я';

    Rectangle panelrect = { 256, 40, 800, 600 };
    bool lockthemouse = false;

    bool toggle_mesh_create = false;

    meshobj meshthingy;

    mat_new = LoadMaterialDefault();

    // Mesh ArrowCubeMesh;

    bool lockmouseX = false;
    bool lockmouseY = false;
    bool lockmouseZ = false;

    bool texturesloaded = false;
    
    float aqur = 0.1f;
    int lastone = -1;

    Texture2D def_texture = LoadTexture("textur");

   // objdb.addmodel(LoadModel("models//gnome.obj"),"Gnome");




    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Управление камерой. Контроль этого
        


        if (IsKeyPressed(KEY_END) || lockthemouse) { //Проверяем, нажата ли ЛКМ
            if ((CheckCollisionPointRec(GetMousePosition(), panelrect)) || lockthemouse) { //В зоне //Или булинг.
                //  DisableCursor();
                if (!lockthemouse) {
                    //HideCursor(); //Не работает Show, пока будет бесить.
                    lockthemouse = true; //Включаем лок
                }
                UpdateCamera(&camera, CAMERA_FREE); //Обновляем камеру.
            }
        }
        if (IsKeyPressed(KEY_HOME)) { //Если нажмём на
            lockthemouse = false;
        }

        //3Д МИР

        BeginTextureMode(DevScreen); //ТУТ ИДЁТ ОТРИСОВКА 3Д МИРА


        ClearBackground(BLACK); //Красим БГ в чёрни.

        BeginMode3D(camera); //Yasss 3д


        DrawGrid(16, 5.0f); //Рисуем сетку (пока просто так



        if(IsKeyPressed(KEY_DELETE) && ((meshactive || mdlactive)) ) {
                objdb.deleteobj(ObjListActive);
                if (ObjListActive == objdb.names.size()) {
                    ObjListActive--;
                }
           
            //ObjListActive = 0;
        }
        if (IsKeyPressed(KEY_G) && ((meshactive || mdlactive))) {
            objdb.duplicateobj(ObjListActive);
        }

        if (!objdb.msdb.MeshVec.empty()) {
            for (auto meshview : objdb.msdb.MeshVec) { //Отображение каждого мэша
                DrawMesh(meshview.modelmesh, meshview.meshmaterial, meshview.meshmatrix);
                
                if ((activeid == meshview.uniqueid)&&(activeid != -1))
                {
                                       
                   //сюда шейдер ёбнуть.


                }
                
            }
        }
        if (!objdb.mdldb.MdlVec.empty()) {
            for (auto md : objdb.mdldb.MdlVec) {

                DrawModelPro(md.modelmdl, md.matrixmodel);


          }
        }

        EndMode3D(); //Заканчиваем с 3д



        if (((meshactive|| mdlactive) && (ObjListActive != -1))) {
            if (IsKeyDown(KEY_X)) {
                if (IsKeyDown(KEY_LEFT_SHIFT)) {
                    DrawText("Scroll scale on X", 10, 10, 15, RED);

                    auto isit = objdb.getinfoobj(ObjListActive);

                    if (isit.type == obj_mesh) {
                        auto& obj = objdb.msdb.MeshVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.meshscale.x += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.meshscale.x -= 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.meshscale.x += 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.meshscale.x = 1;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.meshscale.x, obj.meshscale.y, obj.meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.meshrotaxis);
                        Matrix Positi = MatrixTranslate(obj.meshposition.x, obj.meshposition.y, obj.meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.meshmatrix = newone;
                    }
                    if (isit.type == obj_model) {
                        auto& obj = objdb.mdldb.MdlVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.modelscale.x += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.modelscale.x -= 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.modelscale.x += 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.modelscale.x = 1;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.modelscale.x, obj.modelscale.y, obj.modelscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.modelrotaxis);
                        Matrix Positi = MatrixTranslate(obj.modelposition.x, obj.modelposition.y, obj.modelposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.matrixmodel = newone;
                    }
                }
                else if (IsKeyDown(KEY_LEFT_ALT)) {
                    DrawText("Scroll rotate on X", 10, 10, 15, RED);

                    auto isit = objdb.getinfoobj(ObjListActive);

                    if (isit.type == obj_mesh) {

                        auto& obj = objdb.msdb.MeshVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.meshrotaxis.x += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.meshrotaxis.x += dtr(90);
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.meshrotaxis.x -= dtr(90);

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.meshrotaxis.x = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.meshscale.x, obj.meshscale.y, obj.meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.meshrotaxis);
                        Matrix Positi = MatrixTranslate(obj.meshposition.x, obj.meshposition.y, obj.meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.meshmatrix = newone;
                    }
                    if (isit.type == obj_model) {

                        auto& obj = objdb.mdldb.MdlVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.modelrotaxis.x += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.modelrotaxis.x += dtr(90);
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.modelrotaxis.x -= dtr(90);

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.modelrotaxis.x = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.modelscale.x, obj.modelscale.y, obj.modelscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.modelrotaxis);
                        Matrix Positi = MatrixTranslate(obj.modelposition.x, obj.modelposition.y, obj.modelposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.matrixmodel = newone;
                    }
                }
                else {
                    DrawText("Scroll move on X", 10, 10, 15, RED);

                    auto isit = objdb.getinfoobj(ObjListActive);

                    if (isit.type == obj_mesh) {
                        auto& obj = objdb.msdb.MeshVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.meshposition.x += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.meshposition.x += 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.meshposition.x -= 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.meshposition.x = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.meshscale.x, obj.meshscale.y, obj.meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.meshrotaxis);
                        Matrix Positi = MatrixTranslate(obj.meshposition.x, obj.meshposition.y, obj.meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.meshmatrix = newone;

                    }
                    if (isit.type == obj_model) {
                        auto& obj = objdb.mdldb.MdlVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.modelposition.x += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.modelposition.x += 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.modelposition.x -= 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.modelposition.x = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.modelscale.x, obj.modelscale.y, obj.modelscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.modelrotaxis);
                        Matrix Positi = MatrixTranslate(obj.modelposition.x, obj.modelposition.y, obj.modelposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.matrixmodel = newone;
                    }
                }
            }
            if (IsKeyDown(KEY_C)) {
                if (IsKeyDown(KEY_LEFT_SHIFT)) {
                    DrawText("Scroll scale on Y", 10, 25, 15, RED);

                    auto isit = objdb.getinfoobj(ObjListActive);

                    if (isit.type == obj_mesh) {
                        auto& obj = objdb.msdb.MeshVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.meshscale.y += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.meshscale.y -= 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.meshscale.y += 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.meshscale.y = 1;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.meshscale.x, obj.meshscale.y, obj.meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.meshrotaxis);
                        Matrix Positi = MatrixTranslate(obj.meshposition.x, obj.meshposition.y, obj.meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.meshmatrix = newone;
                    }
                    if (isit.type == obj_model) {
                        auto& obj = objdb.mdldb.MdlVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.modelscale.y += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.modelscale.y -= 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.modelscale.y += 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.modelscale.y = 1;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.modelscale.x, obj.modelscale.y, obj.modelscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.modelrotaxis);
                        Matrix Positi = MatrixTranslate(obj.modelposition.x, obj.modelposition.y, obj.modelposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.matrixmodel = newone;
                    }
                }
                else if (IsKeyDown(KEY_LEFT_ALT)) {
                    DrawText("Scroll rotate on Y", 10, 25, 15, RED);

                    auto isit = objdb.getinfoobj(ObjListActive);

                    if (isit.type == obj_mesh) {

                        auto& obj = objdb.msdb.MeshVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.meshrotaxis.y += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.meshrotaxis.y += dtr(90);
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.meshrotaxis.y -= dtr(90);

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.meshrotaxis.y = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.meshscale.x, obj.meshscale.y, obj.meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.meshrotaxis);
                        Matrix Positi = MatrixTranslate(obj.meshposition.x, obj.meshposition.y, obj.meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.meshmatrix = newone;
                    }
                    if (isit.type == obj_model) {

                        auto& obj = objdb.mdldb.MdlVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.modelrotaxis.y += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.modelrotaxis.y += dtr(90);
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.modelrotaxis.y -= dtr(90);

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.modelrotaxis.y = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.modelscale.x, obj.modelscale.y, obj.modelscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.modelrotaxis);
                        Matrix Positi = MatrixTranslate(obj.modelposition.x, obj.modelposition.y, obj.modelposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.matrixmodel = newone;
                    }
                }
                else {
                    DrawText("Scroll move on Y", 10, 25, 15, RED);

                    auto isit = objdb.getinfoobj(ObjListActive);

                    if (isit.type == obj_mesh) {
                        auto& obj = objdb.msdb.MeshVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.meshposition.y += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.meshposition.y += 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.meshposition.y -= 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.meshposition.y = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.meshscale.x, obj.meshscale.y, obj.meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.meshrotaxis);
                        Matrix Positi = MatrixTranslate(obj.meshposition.x, obj.meshposition.y, obj.meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.meshmatrix = newone;

                    }
                    if (isit.type == obj_model) {
                        auto& obj = objdb.mdldb.MdlVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.modelposition.y += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.modelposition.y += 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.modelposition.y -= 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.modelposition.y = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.modelscale.x, obj.modelscale.y, obj.modelscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.modelrotaxis);
                        Matrix Positi = MatrixTranslate(obj.modelposition.x, obj.modelposition.y, obj.modelposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.matrixmodel = newone;
                    }
                }
            }
            if (IsKeyDown(KEY_Z)) {
                if (IsKeyDown(KEY_LEFT_SHIFT)) {
                    DrawText("Scroll scale on Z", 10, 40, 15, RED);

                    auto isit = objdb.getinfoobj(ObjListActive);
                    
                    if (isit.type == obj_mesh) {
                        auto& obj = objdb.msdb.MeshVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.meshscale.z += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.meshscale.z -= 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.meshscale.z += 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.meshscale.z = 1;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.meshscale.x, obj.meshscale.y, obj.meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.meshrotaxis);
                        Matrix Positi = MatrixTranslate(obj.meshposition.x, obj.meshposition.y, obj.meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.meshmatrix = newone;
                    }
                    if (isit.type == obj_model) {
                        auto& obj = objdb.mdldb.MdlVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.modelscale.z += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.modelscale.z -= 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.modelscale.z += 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.modelscale.z = 1;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.modelscale.x, obj.modelscale.y, obj.modelscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.modelrotaxis);
                        Matrix Positi = MatrixTranslate(obj.modelposition.x, obj.modelposition.y, obj.modelposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.matrixmodel = newone;
                    }
                }
                else if (IsKeyDown(KEY_LEFT_ALT)) {
                    DrawText("Scroll rotate on Z", 10, 40, 15, RED);

                    auto isit = objdb.getinfoobj(ObjListActive);

                    if (isit.type == obj_mesh) {

                        auto& obj = objdb.msdb.MeshVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.meshrotaxis.z += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.meshrotaxis.z += dtr(90);
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.meshrotaxis.z -= dtr(90);

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.meshrotaxis.z = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.meshscale.x, obj.meshscale.y, obj.meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.meshrotaxis);
                        Matrix Positi = MatrixTranslate(obj.meshposition.x, obj.meshposition.y, obj.meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.meshmatrix = newone;
                    }
                    if (isit.type == obj_model) {

                        auto& obj = objdb.mdldb.MdlVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.modelrotaxis.z += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.modelrotaxis.z += dtr(90);
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.modelrotaxis.z -= dtr(90);

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.modelrotaxis.z = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.modelscale.x, obj.modelscale.y, obj.modelscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.modelrotaxis);
                        Matrix Positi = MatrixTranslate(obj.modelposition.x, obj.modelposition.y, obj.modelposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.matrixmodel = newone;
                    }
                }
                else {
                    DrawText("Scroll move on Z", 10, 40, 15, RED);

                    auto isit = objdb.getinfoobj(ObjListActive);

                    if (isit.type == obj_mesh) {
                        auto& obj = objdb.msdb.MeshVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.meshposition.z += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.meshposition.z += 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.meshposition.z -= 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.meshposition.z = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.meshscale.x, obj.meshscale.y, obj.meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.meshrotaxis);
                        Matrix Positi = MatrixTranslate(obj.meshposition.x, obj.meshposition.y, obj.meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.meshmatrix = newone;

                    }
                    if (isit.type == obj_model) {
                        auto& obj = objdb.mdldb.MdlVec[isit.indexnamed];
                        if (GetMouseWheelMove() != 0) {
                            obj.modelposition.z += GetMouseWheelMove() * aqur;
                        }
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            obj.modelposition.z += 1;
                        }

                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                            obj.modelposition.z -= 1;

                        }
                        if (IsKeyPressed(KEY_ZERO)) {
                            obj.modelposition.z = 0;
                        }
                        Matrix newone;

                        Matrix Scl = MatrixScale(obj.modelscale.x, obj.modelscale.y, obj.modelscale.z);
                        Matrix Rotate = MatrixRotateXYZ(obj.modelrotaxis);
                        Matrix Positi = MatrixTranslate(obj.modelposition.x, obj.modelposition.y, obj.modelposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        obj.matrixmodel = newone;
                    }
                }
            }
        }

        EndTextureMode();//Текстурами





        //Отрисовка GUI. А также обработка 



        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));


        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        if (FileDropEditMode) GuiLock();
        int bullcrap = 0;
        GuiGroupBox({ 0, 8, 248, 632 }, "Objects"); //Косметика
        GuiPanel({ 256, 40, 800, 600 }, NULL); //Ненужна панелька лол
        //DrawTexture(DevScreen.texture, 256,40,WHITE); //Отрисовка 3д мира.

        
        DrawTexturePro(DevScreen.texture, { 0,0,float(DevScreen.texture.width),float(DevScreen.texture.height*-1) }, { 256, 40, 800, 600 }, { 0,0 }, 0, WHITE);

        if (materialcreate) { //Создаём материал
            
            if (mat_materials.empty()) {
                for (int ind = 0; ind <= 10; ind++) {
                    mat_materials.push_back(def_texture);
                }
            }
           
           
            materialcreate = !GuiWindowBox({ 256,40,440,400 }, "Material creation");

            GuiPanel({ 262,72,200,200 }, NULL);

            DrawTexturePro(mat_materials[chosen_map], { 0,0,float(mat_materials[chosen_map].width),float(mat_materials[chosen_map].height) }, { 262,72,200,200 }, { 0,0, }, 0, WHITE);

            if (GuiDropdownBox({ 262,272,120,20 }, "Albedo;Metalness;Normal;Roughness;Occlusion;Emission;Heightmap;Cubemap;Irrdaiance;Prefilter;Brdf", &chosen_map, mat_map_bool)) {
                mat_map_bool = !mat_map_bool;
            }


            /*
            typedef enum {
                MATERIAL_MAP_ALBEDO = 0,        // Albedo material (same as: MATERIAL_MAP_DIFFUSE) 0
                MATERIAL_MAP_METALNESS,         // Metalness material (same as: MATERIAL_MAP_SPECULAR) 1
                MATERIAL_MAP_NORMAL,            // Normal material2
                MATERIAL_MAP_ROUGHNESS,         // Roughness material 3
                MATERIAL_MAP_OCCLUSION,         // Ambient occlusion material 4
                MATERIAL_MAP_EMISSION,          // Emission material5
                MATERIAL_MAP_HEIGHT,            // Heightmap material6
                MATERIAL_MAP_CUBEMAP,           // Cubemap material (N7OTE: Uses GL_TEXTURE_CUBE_MAP)
                MATERIAL_MAP_IRRADIANCE,        // Irradiance material 8(NOTE: Uses GL_TEXTURE_CUBE_MAP)
                MATERIAL_MAP_PREFILTER,         // Prefilter material (N9OTE: Uses GL_TEXTURE_CUBE_MAP)
                MATERIAL_MAP_BRDF               // Brdf material10
            } MaterialMapIndex;
*/


            if (GuiButton({ 382,272,80,20 }, "Browse")) { //Выбор текстуры
                std::string winname = "Browse a texture";
                std::string folder = std::string(GetWorkingDirectory()) + "\\textures\\";
                const char* filters[] = { "*.png" };  // Маски файло

                auto pathfor = tinyfd_openFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Texture (*.png)", 1);

                if (pathfor != NULL) {
                    mat_materials[chosen_map] = LoadTexture(pathfor);
                
                    switch (chosen_map)
                    {
                    case 0: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_ALBEDO, mat_materials[chosen_map]);
                    }
                        break;
                    case 1: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_METALNESS, mat_materials[chosen_map]);

                    }
                          break;
                    case 2: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_NORMAL, mat_materials[chosen_map]);

                    }
                          break;
                    case 3: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_ROUGHNESS, mat_materials[chosen_map]);

                    }
                          break;
                    case 4: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_OCCLUSION, mat_materials[chosen_map]);

                    }
                          break;
                    case 5: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_EMISSION, mat_materials[chosen_map]);

                    }
                          break;
                    case 6: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_HEIGHT, mat_materials[chosen_map]);

                    }
                          break;
                    case 7: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_CUBEMAP, mat_materials[chosen_map]);

                    }
                          break;
                    case 8: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_IRRADIANCE, mat_materials[chosen_map]);

                    }
                          break;
                    case 9: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_PREFILTER, mat_materials[chosen_map]);

                    }
                          break;
                    case 10: {
                        SetMaterialTexture(&mat_new, MATERIAL_MAP_BRDF, mat_materials[chosen_map]);

                    }
                          break;
                    default:
                        break;
                    }
                }

                

            }
            
            GuiPanel({ 490,72,200,200 }, NULL);
            

            BeginTextureMode(PreviewScreen); //ТУТ ИДЁТ ОТРИСОВКА 3Д МИР
            ClearBackground(BLACK); //Красим БГ в чёрни
            BeginMode3D(precamera); //Yasss 3д        // Camera projection type
            
            DrawGrid(100, 10);
            
           

            DrawMesh(stdmesh, mat_new, MatrixIdentity());


            EndMode3D();
            EndTextureMode();

            DrawTexture(PreviewScreen.texture, 490, 72, WHITE);            
            GuiLabel({ 568,56,47,23 }, "Preview");


            if (GuiDropdownBox({ 490,272,120,20 }, "Repeat;Clamp;Mirror repeat;Mirror clamp", &chosen_wrap, mat_wrap_bool)) {
                mat_wrap_bool = !mat_wrap_bool;
                if (!mat_wrap_bool) {
                    switch (chosen_wrap)
                    {
                    case(0): {

                    mat_new.maps->value = TEXTURE_WRAP_REPEAT;


                    }break;
                    case(1):{

                    mat_new.maps->value = TEXTURE_WRAP_CLAMP;

                    
                    }break;
                    case(2):{

                    mat_new.maps->value = TEXTURE_WRAP_MIRROR_REPEAT;


                    }break;
                    case(3):{

                    mat_new.maps->value = TEXTURE_WRAP_MIRROR_CLAMP;


                    }break;
                    default:
                        break;
                    }
                }
            }

            if (GuiButton({ 490,292,200,26 }, "Browse shader")) {
                std::string winname = "Browse a shader";
                std::string folder = std::string(GetWorkingDirectory()) + "\\shaders\\";
                const char* filters[] = { "*.fs" };  // Маски файло

                auto pathfor = tinyfd_openFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Fragment shaders (*.fs)", 1);

                if (pathfor != NULL) {
                
                    mat_new.shader = LoadShader(NULL, pathfor);
                    shadernam = pathfor;

                }


            }

            if (GuiButton({ 626,400,50,30 }, "Save")) {

                fs::path zipath = "materials\\";
                std::string winname = "Save";
                std::string folder = zipath.string();
                const char* filters[] = { "Folder" };  // Маски файлов

                auto pathfor = tinyfd_saveFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Material save (*Folder)");

                if (pathfor != NULL) {
                   
                    std::vector<std::string> namesf = { "ALBEDO.png","METALNESS.png","NORMAL.png","ROUGHNESS.png","OCCLUSION.png","EMISSION.png","HEIGHT.png","CUBEMAP.png","IRRIDIANCE.png","PREFILTER.png","BRDF.png" };


                  //  fs::remove_all("save_tmp");
                    fs::create_directories(pathfor);

                    for (int ind = 0; ind <= 10; ind++) {
                        if (mat_materials[ind].format != NULL) { //Если существует.
                            auto forsave = LoadImageFromTexture(mat_materials[ind]);
                            auto tosave = pathfor + std::string("//") + namesf[ind];
                            ExportImage((forsave), (tosave).c_str());
                            UnloadImage(forsave);


                        }

                    }


                    precamera.position = { 5.0f,0.0f,0.0f };
                    BeginTextureMode(PreviewScreen);
                    BeginMode3D(precamera);

                    DrawMesh(stdmesh, mat_new, MatrixIdentity());

                    EndMode3D();
                    EndTextureMode();

                    auto forsave = LoadImageFromTexture(PreviewScreen.texture);
                    auto tosavefff = (pathfor + std::string("//PREVIEW.png"));
                   
                    ExportImage(forsave, tosavefff.c_str());
                    UnloadImage(forsave);

/*
                    fs::path identyi = pathfor+ std::string("\\mat.dummy"); //Пустой файл.
                    std::ofstream idenfile(identyi.string(), std::ios::binary);
                    idenfile.close();
                    */

                    fs::path identyi = pathfor + std::string("\\mat.mati");

                    std::ofstream matinfo(identyi.string(), std::ios::binary);

                    matinfo.write(reinterpret_cast<char*>(&mat_new.maps->value), sizeof(mat_new.maps->value)); //Сохраняем два!

                    if (shadernam.size() > 1) {


                        short int fuckoff = 1;
                        matinfo.write(reinterpret_cast<char*>(&fuckoff), sizeof(fuckoff)); //Сохраняем тот факт что шейдера есть.

                        size_t pathsize = shadernam.size();
                        matinfo.write(reinterpret_cast<char*>(&pathsize), sizeof(pathsize)); //Сохраняем раз!
                        matinfo.write(shadernam.c_str(), pathsize);



                    }
                    else {
                        short int fuckoff = -1;

                        matinfo.write(reinterpret_cast<char*>(&fuckoff), sizeof(fuckoff)); //Сохраняем тот факт что шейдера нет.
                    }

                    matinfo.close();

                    precamera.position = {5,5,5};

//                    zip_close(zip_archive);


                 //   fs::remove_all("save_tmp");
                }
            }

        }


        //DrawTexture()
        GuiGroupBox({ 1072, 16, 200, 700 }, "Details"); //Косметика куда вставляются детали каждого обьекта.
        GuiListView({ 8, 16, 232, 616 }, objdb.name.c_str(), &ObjListScrollIndex, &ObjListActive); //Лист обьектов.




        //с другой стороны ObjListActive уже решает эту проблему.
      //  GuiLine({ 0, 640, 1064, 12 }, NULL); //Косметика
        if (GuiButton({ 8, 648, 72, 24 }, "MESH")) { MeshAddBtn(); toggle_mesh_create = !toggle_mesh_create; }//Кнопка создания мешей 

        if (GuiButton({ 176, 648, 80, 24 }, "ENTITY")) EntAddBtn(); //Энтити
        if (GuiButton({ 88, 648, 80, 24 }, "MODEL")) MdlAddBtn();  //Моделей
        if (GuiDropdownBox({ 256, 8, 104, 24 }, "File;Save;Load", &FileDropActive, FileDropEditMode)) { FileDropEditMode = !FileDropEditMode;  FileBtn(FileDropActive); FileDropActive = 0; } //Dropdown штука. FileDropActive = 0 для того чтобы работало как я хотел :)
        if (GuiDropdownBox({ 376, 8, 104, 24 }, "Material;Create", &MaterialDropActive, MaterialDropEditMode)) { MaterialDropEditMode = !MaterialDropEditMode;  materialbtn(MaterialDropActive); MaterialDropActive = 0; } //Dropdown штука. FileDropActive = 0 для того чтобы работало как я хотел :)


        if (GuiDropdownBox({ 496,8,104,24 }, "Compiling;Compile colision/nav mesh", &chosen_comp, chosen_comp_bool)) {
            chosen_comp_bool = !chosen_comp_bool;
           
            compilebtn(chosen_comp);
            chosen_comp = 0;
        }


        if (lockthemouse) { //Предупреждение что мышка взялась.
            DrawText("Mouse locked home to exit", 300, 600, 24, RED); //Сама преда
            if (!(CheckCollisionPointRec(GetMousePosition(), panelrect))) { //Проверка того что мышка не выходит за края
                SetMousePosition(1280 / 2, 720 / 2); //Если выходит то в центр. 
            } 
        }

        if (ObjListActive == -1) {

            meshactive = false;
            mdlactive = false;

        }


        if ((toggle_mesh_create) && (ObjListActive >= 0)) { //Если раскрыто создание мэша И вообще что-то выбрано.

            GuiPanel({ 8, 688, 568, 24 }, NULL);
            if (GuiButton({ 8, 688, 56, 24 }, "Poly")) {
                PolyMeshBtn(); //Нажимаем на создание полигона
                createpolymesh();
            }
            if (GuiButton({ 72, 688, 56, 24 }, "Plane")) {
                PlaneMeshBtn();
                createplanemesh();
            }
            if (GuiButton({ 136, 688, 56, 24 }, "Cube")) {
                CubeMeshBtn();
                creatcubemesh();
            }
            if (GuiButton({ 264, 688, 56, 24 }, "Cylind")) {
                CylinderMeshBtn();
                createcylinder();
            }
            if (GuiButton({ 200, 688, 56, 24 }, "Sphere")) {
                SphereMeshBtn();
                createspheremesh();
            }
            if (GuiButton({ 328, 688, 56, 24 }, "Cone")) {
                ConeMeshBtn();
                createconermesh();
            }
            if (GuiButton({ 392, 688, 56, 24 }, "Torus")) {
                TorusMeshBtn();
                createtorusmesh();
            }
            if (GuiButton({ 456, 688, 56, 24 }, "Knot")) {
                KnotMeshBtn();
                createknotmesh();
            }
            if (GuiButton({ 520, 688, 56, 24 }, "HalfSph")) {
                HalfSphereBtn();
                createhalfspheremesh();
            }

            //Общие настройки для мэшей

           
        }
        if ((!objdb.msdb.MeshVec.empty()) || (!objdb.mdldb.MdlVec.empty())) {

            auto isit = objdb.getinfoobj(ObjListActive);

            switch (isit.type) {
            case obj_mesh: {

                meshactive = true;
                mdlactive = false;

            }break;

            case obj_model: {

                meshactive = false;
                mdlactive = true;


            }break;

            case -1: {
                meshactive = false;
                mdlactive = false;

            }break;

            }



        }

        if (meshactive) { //Перепроверка что всё создалось уже
    
                meshthingy = objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)];

                activeid = meshthingy.uniqueid;
                
                ColorPicker032Value = meshthingy.meshmaterial.maps->color;

                std::string xtype = std::to_string(meshthingy.meshposition.x);
                std::string ytype = std::to_string(meshthingy.meshposition.y);
                std::string ztype = std::to_string(meshthingy.meshposition.z);



                if (!xtextboxbool) {
                    strcpy_s(xtextbox, xtype.c_str());
                }
                if (!ytextboxbool) {
                    strcpy_s(ytextbox, ytype.c_str());
                }
                if (!ztextboxbool) {
                    strcpy_s(ztextbox, ztype.c_str());
                }
                GuiLabel({ 1080, 584, 120, 24 }, "X: ");
                if (GuiTextBox({ 1091,584,77,12 }, xtextbox, 128, xtextboxbool)) {
                    xtextboxbool = !xtextboxbool;
                    if (!xtextboxbool) {
                        objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.x = std::stof(xtextbox);

                        Matrix newone;

                        Matrix Scl = MatrixScale(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshscale.x, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshscale.y, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshrotaxis);
                        Matrix Positi = MatrixTranslate(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.x, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.y, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmatrix = newone;

                    }
                }
                GuiLabel({ 1080, 600, 120, 24 }, "Y: ");
                if (GuiTextBox({ 1091,600,77,12 }, ytextbox, 128, ytextboxbool)) {
                    ytextboxbool = !ytextboxbool;
                    if (!ytextboxbool) {
                        objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.y = std::stof(ytextbox);

                        Matrix newone;

                        Matrix Scl = MatrixScale(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshscale.x, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshscale.y, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshrotaxis);
                        Matrix Positi = MatrixTranslate(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.x, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.y, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmatrix = newone;

                    }
                }
                GuiLabel({ 1080, 616, 120, 24 }, "Z: ");
                if (GuiTextBox({ 1091,616,77,12 }, ztextbox, 128, ztextboxbool)) {
                    ztextboxbool = !ztextboxbool;
                    if (!ztextboxbool) {
                        objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.z = std::stof(ztextbox);

                        Matrix newone;

                        Matrix Scl = MatrixScale(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshscale.x, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshscale.y, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshscale.z);
                        Matrix Rotate = MatrixRotateXYZ(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshrotaxis);
                        Matrix Positi = MatrixTranslate(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.x, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.y, objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshposition.z);

                        newone = MatrixMultiply(Scl, Rotate);
                        newone = MatrixMultiply(newone, Positi);
                        objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmatrix = newone;

                    }
                }

                GuiPanel({ 1072, 248, 200, 200 }, NULL);
                texturePressed = GuiButton({ 1072, 448, 200, 16 }, "Texture");
                if (texturePressed) {
                    TexturechooserActive = true;
                }


                choser_mod_mesh = objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modificators;
                if (GuiDropdownBox({ 1080,632,120,10 }, "No colision;Solid;Walkable", &choser_mod_mesh, choser_mod_bool_mesh)) {
                    choser_mod_bool_mesh = !choser_mod_bool_mesh;
                    if (!choser_mod_bool) {
                        choser_mod = objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modificators = choser_mod_mesh;
                    }
                }

                //                    GuiLabel({ 1080, 208, 120, 24 }, xtype.c_str());

                /*
                switch (meshthingy.modificators)
                {
                case(10): {
                    DrawTexturePro(meshthingy.meshmaterial.maps->texture, { 0,0,float(meshthingy.meshmaterial.maps->texture.width ),float(meshthingy.meshmaterial.maps->texture.height*-1) }, { 1072, 248, 200, 200 }, { 0,0 }, 0, WHITE);
                }
                    break;

                case(11): {
                    DrawTexturePro(meshthingy.meshmaterial.maps->texture, { 0,0,float(meshthingy.meshmaterial.maps->texture.width ),float(meshthingy.meshmaterial.maps->texture.height*-1) }, { 1072, 248, 200, 200 }, { 0,0 }, 0, WHITE);
                }
                    break;

                default: {
                    DrawTexturePro(meshthingy.meshmaterial.maps->texture, { 0,0,float(meshthingy.meshmaterial.maps->texture.width ),float(meshthingy.meshmaterial.maps->texture.height) }, { 1072, 248, 200, 200 }, { 0,0 }, 0, WHITE);
                }
                    break;

                }
                */
                if (!meshthingy.matpl.path.empty()) {
                    DrawTexturePro(meshthingy.matpl.preview, { 0,0,float(meshthingy.matpl.preview.width),float(meshthingy.matpl.preview.height) }, { 1072, 248, 200, 200 }, { 0,0 }, 0, WHITE);
                }
                else {
                    DrawTexturePro(meshthingy.meshmaterial.maps->texture, { 0,0,float(meshthingy.meshmaterial.maps->texture.width),float(meshthingy.meshmaterial.maps->texture.height) }, { 1072, 248, 200, 200 }, { 0,0 }, 0, WHITE);
                }

                colora = ColorPicker032Value.a;

                GuiColorPicker({ 1080, 496, 56, 56 }, NULL, &ColorPicker032Value);                
                GuiSliderBar({ 1080,560,80,16 }, NULL, NULL, &colora, 0,255);

                ColorPicker032Value.a = int(colora);
                



                //  std::cout << meshthingy.modelmesh.vertices << " \n";

                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->color = ColorPicker032Value;
               // objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->color= ColorPicker032Value;
                
                //meshpoint = &meshpointderef;


                //Дополнительные вкладки для изменения.

                switch (meshthingy.id) { //Создание вкладки ПОЛИГОНА.
                case 1:
                    GuiGroupBox({ 1080, 32, 184, 32 }, "Sides");
                    GuiGroupBox({ 1080, 80, 184, 32 }, "Raduis");
                    if (GuiTextBox({ 1088, 40, 160, 16 }, SidesTextText, 128, SidesTextEditMode)) {
                        SidesTextEditMode = !SidesTextEditMode;
                        if (!SidesTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshPoly(std::stoi(SidesTextText), std::stoi(RadiusTextText));
                        }
                    }
                    if (GuiTextBox({ 1088, 88, 160, 16 }, RadiusTextText, 128, RadiusTextEditMode)) {
                        RadiusTextEditMode = !RadiusTextEditMode;
                        if (!RadiusTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshPoly(std::stoi(SidesTextText), std::stoi(RadiusTextText));
                        }
                    }
                    GuiGroupBox({ 1080, 128, 184, 32 }, "Name");
                    if (GuiTextBox({ 1088, 136, 160, 16 }, NameTextText, 128, NameTextEditMode)) {
                        NameTextEditMode = !NameTextEditMode;
                        if (!NameTextEditMode) {
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].name = NameTextText;
                        }
                    }
                    break;


                case 2:
                    GuiGroupBox({ 1080, 32, 184, 32 }, "Width");
                    if (GuiTextBox({ 1088, 40, 160, 16 }, WidthTextText, 128, WidthTextEditMode)) {
                        WidthTextEditMode = !WidthTextEditMode;
                        if (!WidthTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshPlane(std::stoi(WidthTextText), std::stoi(LengthTextText), std::stoi(ResXTextText), std::stoi(ResYTextText));
                        }
                    }
                    GuiGroupBox({ 1080, 80, 184, 32 }, "Length");
                    if (GuiTextBox({ 1088, 88, 160, 16 }, LengthTextText, 128, LengthTextEditMode)) {
                        LengthTextEditMode = !LengthTextEditMode;
                        if (!LengthTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshPlane(std::stoi(WidthTextText), std::stoi(LengthTextText), std::stoi(ResXTextText), std::stoi(ResYTextText));
                        }
                    }
                    GuiGroupBox({ 1080, 128, 184, 32 }, "Res X");
                    if (GuiTextBox({ 1088, 136, 160, 16 }, ResXTextText, 128, ResXTextEditMode)) {
                        ResXTextEditMode = !ResXTextEditMode;
                        if (!ResXTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshPlane(std::stoi(WidthTextText), std::stoi(LengthTextText), std::stoi(ResXTextText), std::stoi(ResYTextText));
                        }
                    }
                    GuiGroupBox({ 1080, 176, 184, 32 }, "Res Y");
                    if (GuiTextBox({ 1088, 184, 160, 16 }, ResYTextText, 128, ResYTextEditMode)) {
                        ResYTextEditMode = !ResYTextEditMode;
                        if (!ResYTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshPlane(std::stoi(WidthTextText), std::stoi(LengthTextText), std::stoi(ResXTextText), std::stoi(ResYTextText));
                        }
                    }
                    GuiGroupBox({ 1080, 216, 184, 32 }, "Name");
                    if (GuiTextBox({ 1088, 224, 160, 16 }, NameBoxText, 128, NameBoxEditMode)) {
                        NameBoxEditMode = !NameBoxEditMode;
                        if (!NameBoxEditMode) {
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].name = NameCubeText;
                        }
                    }
                    break;

                case 3:
                    GuiGroupBox({ 1080, 32, 184, 32 }, "Width");
                    if (GuiTextBox({ 1088, 40, 160, 16 }, WidthText, 128, WidthEditMode)) {
                        WidthEditMode = !WidthEditMode;
                        if (!SidesTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshCube(std::stof(WidthText), std::stof(HeightText),std::stof(LengthText));
                        }
                    }
                    GuiGroupBox({ 1080, 80, 184, 32 }, "Height");
                    if (GuiTextBox({ 1088, 88, 160, 16 }, HeightText, 128, HeightEditMode)) {
                        HeightEditMode = !HeightEditMode;
                        if (!RadiusTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshCube(std::stof(WidthText), std::stof(HeightText), std::stof(LengthText));
                        }
                    }
                    GuiGroupBox({ 1080, 128, 184, 32 }, "Length");
                    if (GuiTextBox({ 1088, 136, 160, 16 }, LengthText, 128, LengthEditMode)) {
                        LengthEditMode = !LengthEditMode;
                        if (!NameTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshCube(std::stof(WidthText), std::stof(HeightText), std::stof(LengthText));
                        }
                    }
                    GuiGroupBox({ 1080, 176, 184, 32 }, "Name");
                    if (GuiTextBox({ 1088, 184, 160, 16 }, NameCubeText, 128, NameBoxEditMode)) {
                        NameBoxEditMode = !NameBoxEditMode;
                        if (!NameBoxEditMode) {
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].name = NameCubeText;
                        }
                    }
                    break;
                case 4:
                    GuiGroupBox({ 1080, 32, 184, 32 }, "Radius");
                    if (GuiTextBox({ 1088, 40, 160, 16 }, RadiusText, 128, RadiusEditMode)) {
                        RadiusEditMode = !RadiusEditMode;
                        if (!RadiusTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshSphere(std::stof(RadiusText), std::stof(RingsText), std::stof(SlicesText));
                        }
                    }
                    GuiGroupBox({ 1080, 80, 184, 32 }, "Rings");
                    if (GuiTextBox({ 1088, 88, 160, 16 }, RingsText, 128, RingsEditMode)) {
                        RingsEditMode = !RingsEditMode;
                        if (!RingsEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshSphere(std::stof(RadiusText), std::stof(RingsText), std::stof(SlicesText));
                        }
                    }
                    GuiGroupBox({ 1080, 128, 184, 32 }, "Slices");
                    if (GuiTextBox({ 1088, 136, 160, 16 }, SlicesText, 128, SlicesEditMode)) {
                        SlicesEditMode = !SlicesEditMode;
                        if (!SlicesEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshSphere(std::stof(RadiusText), std::stof(RingsText), std::stof(SlicesText));
                        }
                    }
                    GuiGroupBox({ 1080, 176, 184, 32 }, "Name");
                    if (GuiTextBox({ 1088, 184, 160, 16 }, NameSphereText, 128, NameSphereEdit)) {
                        NameSphereEdit = !NameSphereEdit;
                        if (!NameSphereEdit) {
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].name = NameSphereText;
                        }
                    }
                    break;

                case 5:
                    GuiGroupBox({ 1080, 32, 184, 32 }, "Radius");
                    if (GuiTextBox({ 1088, 40, 160, 16 }, RadiusCylinderText, 128, RadiusCylinderEditMode)) {
                        RadiusCylinderEditMode = !RadiusCylinderEditMode;
                        if (!RadiusCylinderEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshCylinder(std::stof(RadiusCylinderText), std::stof(HeightCylinderText), std::stof(SlicesCylinderText));
                        }
                    }
                    GuiGroupBox({ 1080, 80, 184, 32 }, "Height");
                    if (GuiTextBox({ 1088, 88, 160, 16 }, HeightCylinderText, 128, HeightCylinderEditMode)) {
                        HeightCylinderEditMode = !HeightCylinderEditMode;
                        if (!HeightCylinderEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshCylinder(std::stof(RadiusCylinderText), std::stof(HeightCylinderText), std::stof(SlicesCylinderText));
                        }
                    }
                    GuiGroupBox({ 1080, 128, 184, 32 }, "Slices");
                    if (GuiTextBox({ 1088, 136, 160, 16 }, SlicesCylinderText, 128, SlicesCylinderEditMode)) {
                        SlicesCylinderEditMode = !SlicesCylinderEditMode;
                        if (!NameTextEditMode) {
                            UnloadMesh(objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh);
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].modelmesh = GenMeshCylinder(std::stof(RadiusCylinderText), std::stof(HeightCylinderText), std::stof(SlicesCylinderText));
                        }
                    }
                    GuiGroupBox({ 1080, 176, 184, 32 }, "Name");
                    if (GuiTextBox({ 1088, 184, 160, 16 }, NameCylinderText, 128, NameCylinderEdit)) {
                        NameCylinderEdit = !NameCylinderEdit;
                        if (!NameCylinderEdit) {
                            objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].name = NameCylinderText;
                        }
                    }


                    break;
                }
                
                if (TexturechooserActive)
                {             
                    if (!TexturesDB.is_init) {
                        TexturesDB.intdb();
                        std::cout << "DB initialised!";

                    }

                    TexturechooserActive = !(GuiWindowBox({ 256,490,800,150 }, "Materials"));

                    std::vector<matplus> textureselector;

                    spinner_bool_mat = GuiSpinner({ 256,640,800,20 }, NULL, &spinner_int_mat, 0, TexturesDB.db.size(), spinner_bool_mat);

                    if (GuiButton({ 1010,492,20,20 }, "RLD")) {
                        TexturesDB.redb();
                        TexturesDB.intdb();

                    }


                    int forin = spinner_int_mat + 6;

                    for (int imat = spinner_int_mat; forin > imat; imat++) {
                        if (imat >= TexturesDB.db.size()) {
                            break;
                        }
                        else {
                            textureselector.push_back(TexturesDB.db[imat]);
                        }
                    }

                    int pos = 0;
                    for (auto textsel : textureselector) {
                            
                        GuiLabel({ float(266 + (120 * pos)),505,110,10 }, textsel.name.c_str());

                            if (GuiLabelButton({ float(266 + (120 * pos)),520,110,110 }, "NULL")) {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial = textsel.mat;
                              //  objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = textsel.path;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].matpl = textsel;
                                
                            }

                            DrawTexturePro(textsel.preview, { 0,0,float(textsel.preview.width),float(textsel.preview.height)}, {float(266 + (120 * pos)),520,110,110}, {0,0}, 0, WHITE);
                            
                            

                        pos++;

                    }


                    //for (int indmat = 0; indmat < TexturesDB.db.size(); indmat++) {

                      //  if ((TexturesDB.db.size() - 1) < indmat) {
                         //   DrawTexturePro(TexturesDB.db[indmat].preview, { 0,0,float(TexturesDB.db[indmat].preview.width),float(TexturesDB.db[indmat].preview.height) }, { float(256+(110*indmat)+10),520,110,110}, {0,0}, 0, WHITE);
                        //}
                   // }


                    }







                /*
                    if (!texturesloaded) {
                        TexturesDB.initdb();
                        texturesloaded = true;
                    }

                    TexturechooserActive = !GuiWindowBox( { 536, 104, 272, 456 }, "TexturePicker");

                    if (GuiSpinner({ 536, 440, 272, 16 }, NULL, & SliderPageValue, 0, 100, SliderPageEditMode)) SliderPageEditMode = !SliderPageEditMode;
                    if (SliderPageEditMode) {

                    }

                    TextureReloadButton = GuiButton({ 536,480,40,20 }, "Reload");
                    if (TextureReloadButton) {
                        TextureReloadButton = !TextureReloadButton;
                        TexturesDB.initdb();
                    }

                    if (TexturesDB.matdb.size() >= 1) {
                        Texture tf1 = TexturesDB.matdb[0].mat.maps->texture;

                        std::string tf1name = TexturesDB.matdb[0].name;
                        DrawTexturePro(tf1, { 0,0,float(tf1.width * -1),float(tf1.height) }, { 544, 136, 80, 80 }, { 0,0 }, 0, WHITE);
                        TextureButton01Pressed = GuiLabelButton({ 544, 136, 80, 80 }, NULL);
                        if (TextureButton01Pressed) {
                            int indr = 0;
                            switch (meshthingy.modificators)
                            {
                            case(10): {
                                Image flipper = LoadImageFromTexture(TexturesDB.matdb[indr].mat.maps->texture);
                                ImageFlipVertical(&flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = LoadTextureFromImage(flipper);
                                UnloadImage(flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                    break;

                            default: {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = TexturesDB.matdb[indr].mat.maps->texture;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                   break;
                            }
                        }
                        GuiLabel({ 544, 216, 72, 16 }, tf1name.c_str());
                    }
                    if (TexturesDB.matdb.size() >= 2) {
                        Texture tf2 = TexturesDB.matdb[1].mat.maps->texture;
                        std::string tf2name = TexturesDB.matdb[1].name;
                        DrawTexturePro(tf2, { 0,0,float(tf2.width * -1),float(tf2.height) }, { 632, 136, 80, 80 }, { 0,0 }, 0, WHITE);
                        TextureButton02Pressed = GuiLabelButton({ 632, 136, 80, 80 }, NULL);
                        if (TextureButton02Pressed) {
                            int indr = 1;
                            switch (meshthingy.modificators)
                            {
                            case(10): {
                                Image flipper = LoadImageFromTexture(TexturesDB.matdb[indr].mat.maps->texture);
                                ImageFlipVertical(&flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = LoadTextureFromImage(flipper);
                                UnloadImage(flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                    break;

                            default: {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = TexturesDB.matdb[indr].mat.maps->texture;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                   break;
                            }
                        }
                        GuiLabel({ 632, 216, 72, 16 }, tf2name.c_str());
                    }
                    if (TexturesDB.matdb.size() >= 3) {
                        Texture tf3 = TexturesDB.matdb[2].mat.maps->texture;
                        std::string tf3name = TexturesDB.matdb[2].name;
                        DrawTexturePro(tf3, { 0,0,float(tf3.width * -1),float(tf3.height) }, { 720, 136, 80, 80 }, { 0,0 }, 0, WHITE);
                        TextureButton03Pressed = GuiLabelButton({ 720, 136, 80, 80 }, NULL);
                        if (TextureButton03Pressed) {
                            int indr = 2;
                            switch (meshthingy.modificators)
                            {
                            case(10): {
                                Image flipper = LoadImageFromTexture(TexturesDB.matdb[indr].mat.maps->texture);
                                ImageFlipVertical(&flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = LoadTextureFromImage(flipper);
                                UnloadImage(flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                    break;

                            default: {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = TexturesDB.matdb[indr].mat.maps->texture;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                   break;
                            }
                        }
                        GuiLabel({ 720, 216, 72, 16 }, tf3name.c_str());
                    }
                    if (TexturesDB.matdb.size() >= 4) {
                        Texture tf4 = TexturesDB.matdb[3].mat.maps->texture;
                        std::string tf4name = TexturesDB.matdb[3].name;
                        DrawTexturePro(tf4, { 0,0,float(tf4.width * -1),float(tf4.height) }, { 544, 232, 80, 80 }, { 0,0 }, 0, WHITE);
                        TextureButton04Pressed = GuiLabelButton({ 544, 232, 80, 80 }, NULL);
                        if (TextureButton04Pressed) {
                            int indr = 3;
                            switch (meshthingy.modificators)
                            {
                            case(10): {
                                Image flipper = LoadImageFromTexture(TexturesDB.matdb[indr].mat.maps->texture);
                                ImageFlipVertical(&flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = LoadTextureFromImage(flipper);
                                UnloadImage(flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                    break;

                            default: {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = TexturesDB.matdb[indr].mat.maps->texture;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                   break;
                            }
                        }
                        GuiLabel({ 544, 312, 64, 12 }, tf4name.c_str());
                    }
                    if (TexturesDB.matdb.size() >= 5) {
                        Texture tf5 = TexturesDB.matdb[4].mat.maps->texture;
                        std::string tf5name = TexturesDB.matdb[4].name;
                        DrawTexturePro(tf5, { 0,0,float(tf5.width * -1),float(tf5.height) }, { 632, 232, 80, 80 }, { 0,0 }, 0, WHITE);
                        TextureButton05Pressed = GuiLabelButton({ 632, 232, 80, 80 }, NULL);
                        if (TextureButton05Pressed) {
                            int indr = 4;
                            switch (meshthingy.modificators)
                            {
                            case(10): {
                                Image flipper = LoadImageFromTexture(TexturesDB.matdb[indr].mat.maps->texture);
                                ImageFlipVertical(&flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = LoadTextureFromImage(flipper);
                                UnloadImage(flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                    break;

                            default: {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = TexturesDB.matdb[indr].mat.maps->texture;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                   break;
                            }
                        }
                        GuiLabel({ 632, 312, 72, 16 }, tf5name.c_str());
                    }
                    if (TexturesDB.matdb.size() >= 6) {
                        Texture tf6 = TexturesDB.matdb[5].mat.maps->texture;
                        std::string tf6name = TexturesDB.matdb[5].name;
                        DrawTexturePro(tf6, { 0,0,float(tf6.width * -1),float(tf6.height) }, { 720, 232, 80, 80 }, { 0,0 }, 0, WHITE);
                        TextureButton06Pressed = GuiLabelButton({ 720, 232, 80, 80 }, NULL);
                        if (TextureButton06Pressed) {
                            int indr = 5;
                            switch (meshthingy.modificators)
                            {
                            case(10): {
                                Image flipper = LoadImageFromTexture(TexturesDB.matdb[indr].mat.maps->texture);
                                ImageFlipVertical(&flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = LoadTextureFromImage(flipper);
                                UnloadImage(flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                    break;

                            default: {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = TexturesDB.matdb[indr].mat.maps->texture;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                   break;
                            }
                        }
                        GuiLabel({ 720, 312, 72, 16 }, tf6name.c_str());
                    }
                    if (TexturesDB.matdb.size() >= 7) {
                        Texture tf7 = TexturesDB.matdb[6].mat.maps->texture;
                        std::string tf7name = TexturesDB.matdb[6].name;
                        DrawTexturePro(tf7, { 0,0,float(tf7.width * -1),float(tf7.height) }, { 544, 336, 80, 80 }, { 0,0 }, 0, WHITE);
                        TextureButton07Pressed = GuiLabelButton({ 544, 336, 80, 80 }, NULL);
                        if (TextureButton07Pressed) {
                            int indr = 6;
                            switch (meshthingy.modificators)
                            {
                            case(10): {
                                Image flipper = LoadImageFromTexture(TexturesDB.matdb[indr].mat.maps->texture);
                                ImageFlipVertical(&flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = LoadTextureFromImage(flipper);
                                UnloadImage(flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                    break;

                            default: {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = TexturesDB.matdb[indr].mat.maps->texture;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                   break;
                            }
                        }
                        GuiLabel({ 544, 416, 64, 12 }, tf7name.c_str());
                    }
                    if (TexturesDB.matdb.size() >= 8) {
                        Texture tf8 = TexturesDB.matdb[7].mat.maps->texture;
                        std::string tf8name = TexturesDB.matdb[7].name;
                        DrawTexturePro(tf8, { 0,0,float(tf8.width * -1),float(tf8.height) }, { 632, 336, 80, 80 }, { 0,0 }, 0, WHITE);
                        TextureButton08Pressed = GuiLabelButton({ 632, 336, 80, 80 }, NULL);
                        if (TextureButton08Pressed) {
                            int indr = 7;
                            switch (meshthingy.modificators)
                            {
                            case(10): {
                                Image flipper = LoadImageFromTexture(TexturesDB.matdb[indr].mat.maps->texture);
                                ImageFlipVertical(&flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = LoadTextureFromImage(flipper);
                                UnloadImage(flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                    break;

                            default: {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = TexturesDB.matdb[indr].mat.maps->texture;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                   break;
                            }
                        }
                        GuiLabel({ 632, 416, 64, 12 }, tf8name.c_str());
                    }
                    if (TexturesDB.matdb.size() >= 9) {
                        Texture tf9 = TexturesDB.matdb[8].mat.maps->texture;
                        std::string tf9name = TexturesDB.matdb[8].name;
                        DrawTexturePro(tf9, { 0,0,float(tf9.width * -1),float(tf9.height) }, { 720, 336, 80, 80 }, { 0,0 }, 0, WHITE);
                        TextureButton09Pressed = GuiLabelButton({ 720, 336, 80, 80 }, NULL);
                        if (TextureButton09Pressed) {
                            int indr = 8;
                            switch (meshthingy.modificators)
                            {
                            case(10): {
                                Image flipper = LoadImageFromTexture(TexturesDB.matdb[indr].mat.maps->texture);
                                ImageFlipVertical(&flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = LoadTextureFromImage(flipper);
                                UnloadImage(flipper);
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                    break;

                            default: {
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].meshmaterial.maps->texture = TexturesDB.matdb[indr].mat.maps->texture;
                                objdb.msdb.MeshVec[objdb.getmeshobj(ObjListActive)].texturepathnam = TexturesDB.matdb[indr].path;

                            }
                                   break;
                            }
                        }
                        GuiLabel({ 720, 416, 64, 12 }, tf9name.c_str());
                    }

                               
                }
                */
            }
        if  (mdlactive) {


            modelobj modelthingy = objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)];

            activeid = modelthingy.uniqueid;

            std::string xtype = std::to_string(modelthingy.modelposition.x);
            std::string ytype = std::to_string(modelthingy.modelposition.y);
            std::string ztype = std::to_string(modelthingy.modelposition.z);

            if (!xtextboxbool) {
                strcpy_s(xtextbox, xtype.c_str());
            }
            if (!ytextboxbool) {
                strcpy_s(ytextbox, ytype.c_str());
            }
            if (!ztextboxbool) {
                strcpy_s(ztextbox, ztype.c_str());
            }
            GuiLabel({ 1080, 584, 120, 24 }, "X: ");
            if (GuiTextBox({ 1091,584,77,12 }, xtextbox, 128, xtextboxbool)) {
                xtextboxbool = !xtextboxbool;
                if (!xtextboxbool) {
                    objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)].modelposition.x = std::stof(xtextbox);
                    modelthingy = objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)];


                    Matrix newone;

                    Matrix Scl = MatrixScale(modelthingy.modelscale.x, modelthingy.modelscale.y, modelthingy.modelscale.z);
                    Matrix Rotate = MatrixRotateXYZ(modelthingy.modelrotaxis);
                    Matrix Positi = MatrixTranslate(modelthingy.modelposition.x, modelthingy.modelposition.y, modelthingy.modelposition.z);

                    newone = MatrixMultiply(Scl, Rotate);
                    newone = MatrixMultiply(newone, Positi);
                    objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)].matrixmodel = newone;

                }
            }
            GuiLabel({ 1080, 600, 120, 24 }, "Y: ");
            if (GuiTextBox({ 1091,600,77,12 }, ytextbox, 128, ytextboxbool)) {
                ytextboxbool = !ytextboxbool;
                if (!ytextboxbool) {
                    objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)].modelposition.y = std::stof(ytextbox);
                    modelthingy = objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)];

                    Matrix newone;

                    Matrix Scl = MatrixScale(modelthingy.modelscale.x, modelthingy.modelscale.y, modelthingy.modelscale.z);
                    Matrix Rotate = MatrixRotateXYZ(modelthingy.modelrotaxis);
                    Matrix Positi = MatrixTranslate(modelthingy.modelposition.x, modelthingy.modelposition.y, modelthingy.modelposition.z);

                    newone = MatrixMultiply(Scl, Rotate);
                    newone = MatrixMultiply(newone, Positi);
                    objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)].matrixmodel = newone;

                }
            }
            GuiLabel({ 1080, 616, 120, 24 }, "Z: ");
            if (GuiTextBox({ 1091,616,77,12 }, ztextbox, 128, ztextboxbool)) {
                ztextboxbool = !ztextboxbool;
                if (!ztextboxbool) {
                    objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)].modelposition.z = std::stof(ztextbox);
                    modelthingy = objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)];
                    Matrix newone;

                    Matrix Scl = MatrixScale(modelthingy.modelscale.x, modelthingy.modelscale.y, modelthingy.modelscale.z);
                    Matrix Rotate = MatrixRotateXYZ(modelthingy.modelrotaxis);
                    Matrix Positi = MatrixTranslate(modelthingy.modelposition.x, modelthingy.modelposition.y, modelthingy.modelposition.z);

                    newone = MatrixMultiply(Scl, Rotate);
                    newone = MatrixMultiply(newone, Positi);
                    objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)].matrixmodel = newone;

                }
            }

            choser_mod = objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)].modificators;
            if (GuiDropdownBox({ 1080,632,120,10 }, "No colision;Solid;", &choser_mod, choser_mod_bool)) {
                choser_mod_bool = !choser_mod_bool;
                if (!choser_mod_bool) {
                    objdb.mdldb.MdlVec[objdb.getmodelobj(ObjListActive)].modificators = choser_mod;
                }
            }


        }
        GuiUnlock();
        //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------

        return 0;


}
