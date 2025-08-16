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
    bool ResXTextEditMode = false;
    char ResXTextText[128] = "";
    bool ChoosePressed = false;
    Color ColorPicker032Value = { 0, 0, 0, 0 };
    bool ResYTextEditMode = false;
    char ResYTextText[128] = "";
    bool NameBoxEditMode = false;
    char NameBoxText[128] = "";
    bool Texture chooserActive = true;
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

            if (Texture chooserActive)
            {
                Texture chooserActive = !GuiWindowBox((Rectangle){ 536, 104, 272, 456 }, "TexturePicker");
                if (GuiSpinner((Rectangle){ 536, 440, 272, 16 }, NULL, &SliderPageValue, 0, 100, SliderPageEditMode)) SliderPageEditMode = !SliderPageEditMode;
                TextureButton01Pressed = GuiLabelButton((Rectangle){ 544, 136, 80, 80 }, NULL);
                GuiLabel((Rectangle){ 544, 216, 72, 16 }, "TextureName");
                TextureButton03Pressed = GuiLabelButton((Rectangle){ 720, 136, 80, 80 }, NULL);
                TextureButton02Pressed = GuiLabelButton((Rectangle){ 632, 136, 80, 80 }, NULL);
                GuiLabel((Rectangle){ 632, 216, 72, 16 }, "TextureName");
                GuiLabel((Rectangle){ 720, 216, 72, 16 }, "TextureName");
                TextureButton05Pressed = GuiLabelButton((Rectangle){ 632, 232, 80, 80 }, NULL);
                TextureButton06Pressed = GuiLabelButton((Rectangle){ 720, 232, 80, 80 }, NULL);
                GuiLabel((Rectangle){ 544, 312, 64, 12 }, "TextureName");
                GuiLabel((Rectangle){ 632, 312, 72, 16 }, "TextureName");
                GuiLabel((Rectangle){ 720, 312, 72, 16 }, "TextureName");
                TextureButton07Pressed = GuiLabelButton((Rectangle){ 544, 336, 80, 80 }, NULL);
                TextureButton08Pressed = GuiLabelButton((Rectangle){ 632, 336, 80, 80 }, NULL);
                TextureButton09Pressed = GuiLabelButton((Rectangle){ 720, 336, 80, 80 }, NULL);
                GuiLabel((Rectangle){ 544, 416, 64, 12 }, "TextureName");
                GuiLabel((Rectangle){ 632, 416, 64, 12 }, "TextureName");
                GuiLabel((Rectangle){ 720, 416, 64, 12 }, "TextureName");
                GuiPanel((Rectangle){ 544, 464, 256, 88 }, "Dropbox");
            }
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
            GuiGroupBox((Rectangle){ 1080, 32, 184, 32 }, "Width");
            GuiGroupBox((Rectangle){ 1080, 80, 184, 32 }, "Length");
            if (GuiTextBox((Rectangle){ 1088, 40, 160, 16 }, SidesTextText, 128, SidesTextEditMode)) SidesTextEditMode = !SidesTextEditMode;
            if (GuiTextBox((Rectangle){ 1088, 88, 160, 16 }, RadiusTextText, 128, RadiusTextEditMode)) RadiusTextEditMode = !RadiusTextEditMode;
            GuiGroupBox((Rectangle){ 1080, 128, 184, 32 }, "Res X");
            if (GuiTextBox((Rectangle){ 1088, 136, 160, 16 }, ResXTextText, 128, ResXTextEditMode)) ResXTextEditMode = !ResXTextEditMode;
            GuiLabel((Rectangle){ 616, 648, 120, 24 }, "X:");
            GuiLabel((Rectangle){ 736, 648, 120, 24 }, "Y:");
            GuiLabel((Rectangle){ 864, 648, 120, 24 }, "Z:");
            GuiPanel((Rectangle){ 1112, 312, 200, 200 }, NULL);
            ChoosePressed = GuiButton((Rectangle){ 0, 0, 0, 0 }, NULL); 
            GuiColorPicker((Rectangle){ 1072, 504, 176, 136 }, NULL, &ColorPicker032Value);
            GuiGroupBox((Rectangle){ 1080, 176, 184, 32 }, "Res Y");
            GuiGroupBox((Rectangle){ 1080, 216, 184, 32 }, "Name");
            if (GuiTextBox((Rectangle){ 1088, 184, 160, 16 }, ResYTextText, 128, ResYTextEditMode)) ResYTextEditMode = !ResYTextEditMode;
            if (GuiTextBox((Rectangle){ 1088, 224, 160, 16 }, NameBoxText, 128, NameBoxEditMode)) NameBoxEditMode = !NameBoxEditMode;
            TextureButton04Pressed = GuiLabelButton((Rectangle){ 1336, 232, 80, 80 }, NULL);
            Button056Pressed = GuiButton((Rectangle){ 1072, 480, 200, 16 }, "Shader"); 
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

