/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    bool FileDropEditMode = false;
    int FileDropActive = 0;
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
    bool SidesTextEditMode = false;
    char SidesTextText[128] = "4";
    bool RadiusTextEditMode = false;
    char RadiusTextText[128] = "1";
    bool NameTextEditMode = false;
    char NameTextText[128] = "";
    bool texturePressed = false;
    Color ColorPicker032Value = { 0, 0, 0, 0 };
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (FileDropEditMode) GuiLock();

            GuiPanel((Rectangle){ 0, 0, 1280, 720 }, NULL);
            GuiGroupBox((Rectangle){ 8, 8, 248, 632 }, "Objects");
            GuiPanel((Rectangle){ 264, 40, 800, 600 }, NULL);
            GuiGroupBox((Rectangle){ 1072, 16, 200, 624 }, "Details");
            GuiListView((Rectangle){ 16, 16, 232, 616 }, NULL, &ObjListScrollIndex, &ObjListActive);
            GuiLine((Rectangle){ 0, 640, 1280, 12 }, NULL);
            MeshAddBtnPressed = GuiButton((Rectangle){ 8, 656, 72, 24 }, "MESH"); 
            EntAddBtnPressed = GuiButton((Rectangle){ 176, 656, 80, 24 }, "ENTITY"); 
            MdlAddBtnPressed = GuiButton((Rectangle){ 88, 656, 80, 24 }, "MODEL"); 
            GuiPanel((Rectangle){ 8, 688, 568, 24 }, NULL);
            PolyMeshBtnPressed = GuiButton((Rectangle){ 8, 688, 56, 24 }, "Poly"); 
            PlaneMeshBtnPressed = GuiButton((Rectangle){ 72, 688, 56, 24 }, "Plane"); 
            CubeMeshBtnPressed = GuiButton((Rectangle){ 136, 688, 56, 24 }, "Cube"); 
            CylinderMeshBtnPressed = GuiButton((Rectangle){ 264, 688, 56, 24 }, "Cylind"); 
            SphereMeshBtnPressed = GuiButton((Rectangle){ 200, 688, 56, 24 }, "Sphere"); 
            ConeMeshBtnPressed = GuiButton((Rectangle){ 328, 688, 56, 24 }, "Cone"); 
            TorusMeshBtnPressed = GuiButton((Rectangle){ 392, 688, 56, 24 }, "Torus"); 
            KnotMeshBtnPressed = GuiButton((Rectangle){ 456, 688, 56, 24 }, "Knot"); 
            HalfSphereBtnPressed = GuiButton((Rectangle){ 520, 688, 56, 24 }, "HalfSph"); 
            GuiGroupBox((Rectangle){ 1080, 32, 184, 32 }, "Sides");
            GuiGroupBox((Rectangle){ 1080, 80, 184, 32 }, "Raduis");
            if (GuiTextBox((Rectangle){ 1088, 40, 160, 16 }, SidesTextText, 128, SidesTextEditMode)) SidesTextEditMode = !SidesTextEditMode;
            if (GuiTextBox((Rectangle){ 1088, 88, 160, 16 }, RadiusTextText, 128, RadiusTextEditMode)) RadiusTextEditMode = !RadiusTextEditMode;
            GuiGroupBox((Rectangle){ 1080, 128, 184, 32 }, "Name");
            if (GuiTextBox((Rectangle){ 1088, 136, 160, 16 }, NameTextText, 128, NameTextEditMode)) NameTextEditMode = !NameTextEditMode;
            GuiLabel((Rectangle){ 1080, 160, 120, 24 }, "X:");
            GuiLabel((Rectangle){ 1080, 176, 120, 24 }, "Y:");
            GuiLabel((Rectangle){ 1080, 192, 120, 24 }, "Z:");
            GuiLabel((Rectangle){ 1080, 208, 120, 24 }, "M:");
            GuiPanel((Rectangle){ 1072, 248, 200, 200 }, NULL);
            texturePressed = GuiButton((Rectangle){ 1072, 448, 200, 16 }, "Texture"); 
            GuiColorPicker((Rectangle){ 1072, 472, 168, 160 }, NULL, &ColorPicker032Value);
            if (GuiDropdownBox((Rectangle){ 264, 8, 104, 24 }, "File", &FileDropActive, FileDropEditMode)) FileDropEditMode = !FileDropEditMode;
            
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

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------

