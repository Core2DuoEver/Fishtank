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

    /*        BeginTextureMode(DevScreen); //��� �Ĩ� ��������� 3� ����


        ClearBackground(BLACK); //������ �� � �����.

        BeginMode3D(camera); //Yasss 3�


        DrawGrid(16, 5.0f); //������ ����� (���� ������ ���

        if (!objdb.msdb.MeshVec.empty()) {
            for (auto meshview : objdb.msdb.MeshVec) { //����������� ������� ����
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

        EndMode3D(); //����������� � 3�*/


    //����������� � ����������.
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

