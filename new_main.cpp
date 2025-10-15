//Refactored version of main_tank.cpp

//Includes

#include "Bait.h"

void init() {
    //Init's
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(standart_screen_width, standart_screen_height, window_name);
    RenderTexture dev_Screen = LoadRenderTexture(800, 600);
    SetTargetFPS(target_fps); 
    SetWindowMinSize(minimal_resolution_width, minimal_resolution_height);
    SetWindowMaxSize(maximum_resolution_width, maximum_resolution_height);
}

void update_position() {

}

void draw_world(){

    /*        BeginTextureMode(DevScreen); //ТУТ ИДЁТ ОТРИСОВКА 3Д МИРА


        ClearBackground(BLACK); //Красим БГ в чёрни.

        BeginMode3D(camera); //Yasss 3д


        DrawGrid(16, 5.0f); //Рисуем сетку (пока просто так

        if (!objdb.msdb.MeshVec.empty()) {
            for (auto meshview : objdb.msdb.MeshVec) { //Отображение каждого мэша
                DrawMesh(meshview.modelmesh, meshview.meshmaterial, meshview.meshmatrix);
                
                if ((activeid == meshview.uniqueid)&&(activeid != -1))
                {
                                       


                }
                
            }
        }
        if (!objdb.mdldb.MdlVec.empty()) {
            for (auto md : objdb.mdldb.MdlVec) {

                DrawModelPro(md.modelmdl, md.matrixmodel);


          }
        }

        EndMode3D(); //Заканчиваем с 3д*/


    //Переместить в управление.
    /*
    if (IsKeyPressed(KEY_DELETE) && ((meshactive || mdlactive))) {
        objdb.deleteobj(ObjListActive);
        if (ObjListActive == objdb.names.size()) {
            ObjListActive--;
        }

        //ObjListActive = 0;
    }
    if (IsKeyPressed(KEY_G) && ((meshactive || mdlactive))) {
        objdb.duplicateobj(ObjListActive);
    }*/



}

int main() {

    init();

    bool exit_signal = false;

    while (!exit_signal) {



    }

}

