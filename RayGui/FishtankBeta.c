/*******************************************************************************************
*
*   FishtankBeta v0.3 - 
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 NO. All Rights Reserved.
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

    InitWindow(screenWidth, screenHeight, "FishtankBeta");

    // FishtankBeta: controls initialization
    //----------------------------------------------------------------------------------
    // Define controls variables
    bool HelpButtonPressed = false;            // Button: HelpButton
    bool ObjectToggle1Active = true;            // Toggle: ObjectToggle1
    bool ObjectToggle2Active = true;            // Toggle: ObjectToggle2
    bool ObjectToggle3Active = true;            // Toggle: ObjectToggle3
    bool ObjectToggle4Active = true;            // Toggle: ObjectToggle4
    bool FilterDropdownEditMode = false;
    int FilterDropdownActive = 0;            // DropdownBox: FilterDropdown
    int ObjectListScrollIndex = 0;
    int ObjectListActive = 0;            // ListView: ObjectList
    bool MeshToolToggleActive = true;            // Toggle: MeshToolToggle
    bool ModelToolToggleActive = true;            // Toggle: ModelToolToggle
    bool EntityToolButtonActive = true;            // Toggle: EntityToolButton
    bool FileDropdownEditMode = false;
    int FileDropdownActive = 0;            // DropdownBox: FileDropdown
    bool ModelDropdownEditMode = false;
    int ModelDropdownActive = 0;            // DropdownBox: ModelDropdown
    bool MaterialDropdownEditMode = false;
    int MaterialDropdownActive = 0;            // DropdownBox: MaterialDropdown
    bool MapdropdownEditMode = false;
    int MapdropdownActive = 0;            // DropdownBox: Mapdropdown
    bool RunDropdownEditMode = false;
    int RunDropdownActive = 0;            // DropdownBox: RunDropdown
    bool NameTextBoxEditMode = false;
    char NameTextBoxText[128] = "";            // TextBox: NameTextBox
    bool XLabelPressed = false;            // LabelButton: XLabel
    bool YLabelPressed = false;            // LabelButton: YLabel
    bool ZLabelPressed = false;            // LabelButton: ZLabel
    bool PositionXTextBoxEditMode = false;
    char PositionXTextBoxText[128] = "";            // TextBox: PositionXTextBox
    bool PositionYTextBoxEditMode = false;
    char PositionYTextBoxText[128] = "";            // TextBox: PositionYTextBox
    bool PositionZTextBoxEditMode = false;
    char PositionZTextBoxText[128] = "";            // TextBox: PositionZTextBox
    bool ScaleXTextBoxEditMode = false;
    char ScaleXTextBoxText[128] = "";            // TextBox: ScaleXTextBox
    bool ScaleYTextBoxEditMode = false;
    char ScaleYTextBoxText[128] = "";            // TextBox: ScaleYTextBox
    bool ScaleZTextBoxEditMode = false;
    char ScaleZTextBoxText[128] = "";            // TextBox: ScaleZTextBox
    bool AngleXTextBoxEditMode = false;
    char AngleXTextBoxText[128] = "";            // TextBox: AngleXTextBox
    bool AngleYTextBoxEditMode = false;
    char AngleYTextBoxText[128] = "";            // TextBox: AngleYTextBox
    bool AngleZTextBoxEditMode = false;
    char AngleZTextBoxText[128] = "";            // TextBox: AngleZTextBox
    bool MeshTypeDropboxEditMode = false;
    int MeshTypeDropboxActive = 0;            // DropdownBox: MeshTypeDropbox
    bool ParamTextBox1EditMode = false;
    char ParamTextBox1Text[128] = "";            // TextBox: ParamTextBox1
    bool Param2TextBoxEditMode = false;
    char Param2TextBoxText[128] = "";            // TextBox: Param2TextBox
    bool DropdownBox055EditMode = false;
    int DropdownBox055Active = 0;            // DropdownBox: DropdownBox055
    bool HideObjectRadioButtonChecked = false;            // CheckBoxEx: HideObjectRadioButton
    bool AddLogicButtonPressed = false;            // Button: AddLogicButton
    bool RemoveLogicButtonPressed = false;            // Button: RemoveLogicButton
    bool LogicTextBoxEditMode = false;
    char LogicTextBoxText[128] = "";            // TextBox: LogicTextBox
    int LogicListViewScrollIndex = 0;
    int LogicListViewActive = 0;            // ListView: LogicListView
    bool MaterialChangeButtonPressed = false;            // Button: MaterialChangeButton
    bool Rotate90ButtonPressed = false;            // Button: Rotate90Button
    bool MirrorHorButtonPressed = false;            // Button: MirrorHorButton
    bool MirrorVerticalButtonPressed = false;            // Button: MirrorVerticalButton
    bool CreateButtonCollisionsPressed = false;            // Button: CreateButtonCollisions
    bool ColiderSettingsDropBoxEditMode = false;
    int ColiderSettingsDropBoxActive = 0;            // DropdownBox: ColiderSettingsDropBox
    bool Button073Pressed = false;            // Button: Button073
    bool ChooseShaderEditMode = false;
    int ChooseShaderActive = 0;            // DropdownBox: ChooseShader
    bool ShaderSettingsDropdownBoxEditMode = false;
    int ShaderSettingsDropdownBoxActive = 0;            // DropdownBox: ShaderSettingsDropdownBox
    bool EditMode = false;
    char Text[128] = "ModelShaderSettingsTextBox";            // TextBox: 
    bool CreditsWindowActive = true;            // WindowBox: CreditsWindow
    bool MELabelPressed = false;            // LabelButton: MELabel
    bool GithubLabelButtonPressed = false;            // LabelButton: GithubLabelButton
    bool WindowBox079Active = true;            // WindowBox: WindowBox079
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
            // Draw controls
            if (FilterDropdownEditMode || FileDropdownEditMode || ModelDropdownEditMode || MaterialDropdownEditMode || MapdropdownEditMode || RunDropdownEditMode || MeshTypeDropboxEditMode || DropdownBox055EditMode || ColiderSettingsDropBoxEditMode || ChooseShaderEditMode || ShaderSettingsDropdownBoxEditMode) GuiLock();

            if (CreditsWindowActive)
            {
                CreditsWindowActive = !GuiWindowBox((Rectangle){ 24, 456, 336, 168 }, "Credits");
                GuiLabel((Rectangle){ 24, 528, 328, 24 }, "Opensource : Raylib, Raygui, ZIP, tinyfiledialogs, boost ");
            }
            if (WindowBox079Active)
            {
                WindowBox079Active = !GuiWindowBox((Rectangle){ 384, 456, 216, 328 }, "Help");
            }
            GuiPanel((Rectangle){ 0, 0, 768, 432 }, NULL);
            GuiPanel((Rectangle){ -8, 0, 776, 24 }, NULL);
            GuiPanel((Rectangle){ 576, 0, 192, 24 }, NULL);
            HelpButtonPressed = GuiButton((Rectangle){ 744, 0, 24, 24 }, "?"); 
            GuiPanel((Rectangle){ 576, 24, 192, 192 }, NULL);
            GuiPanel((Rectangle){ 0, 24, 24, 408 }, NULL);
            GuiPanel((Rectangle){ 576, 216, 192, 216 }, NULL);
            GuiToggle((Rectangle){ 576, 24, 48, 24 }, "SAMPLE TEXT", &ObjectToggle1Active);
            GuiToggle((Rectangle){ 624, 24, 48, 24 }, "SAMPLE TEXT", &ObjectToggle2Active);
            GuiToggle((Rectangle){ 672, 24, 48, 24 }, "SAMPLE TEXT", &ObjectToggle3Active);
            GuiToggle((Rectangle){ 720, 24, 48, 24 }, "SAMPLE TEXT", &ObjectToggle4Active);
            GuiPanel((Rectangle){ 576, 216, 96, 24 }, NULL);
            GuiLabel((Rectangle){ 576, 216, 96, 24 }, "Objects");
            GuiListView((Rectangle){ 576, 240, 192, 192 }, "No objects", &ObjectListScrollIndex, &ObjectListActive);
            GuiToggle((Rectangle){ 0, 24, 24, 24 }, "M", &MeshToolToggleActive);
            GuiToggle((Rectangle){ 0, 48, 24, 24 }, ".M", &ModelToolToggleActive);
            GuiToggle((Rectangle){ 0, 72, 24, 24 }, "E", &EntityToolButtonActive);
            GuiPanel((Rectangle){ 792, 48, 192, 168 }, NULL);
            GuiPanel((Rectangle){ 1008, 48, 192, 168 }, NULL);
            GuiPanel((Rectangle){ 1008, 240, 192, 168 }, NULL);
            GuiPanel((Rectangle){ 1224, 48, 192, 168 }, NULL);
            GuiPanel((Rectangle){ 1440, 48, 192, 168 }, NULL);
            GuiPanel((Rectangle){ 1440, 240, 192, 168 }, NULL);
            GuiLabel((Rectangle){ 800, 56, 40, 24 }, "Name :");
            if (GuiTextBox((Rectangle){ 840, 56, 144, 24 }, NameTextBoxText, 128, NameTextBoxEditMode)) NameTextBoxEditMode = !NameTextBoxEditMode;
            GuiLabel((Rectangle){ 808, 144, 32, 24 }, "Ang :");
            XLabelPressed = GuiLabelButton((Rectangle){ 840, 80, 24, 16 }, "X");
            YLabelPressed = GuiLabelButton((Rectangle){ 888, 80, 24, 16 }, "Y");
            ZLabelPressed = GuiLabelButton((Rectangle){ 936, 80, 24, 16 }, "Z");
            if (GuiTextBox((Rectangle){ 840, 96, 48, 24 }, PositionXTextBoxText, 128, PositionXTextBoxEditMode)) PositionXTextBoxEditMode = !PositionXTextBoxEditMode;
            if (GuiTextBox((Rectangle){ 888, 96, 48, 24 }, PositionYTextBoxText, 128, PositionYTextBoxEditMode)) PositionYTextBoxEditMode = !PositionYTextBoxEditMode;
            if (GuiTextBox((Rectangle){ 936, 96, 48, 24 }, PositionZTextBoxText, 128, PositionZTextBoxEditMode)) PositionZTextBoxEditMode = !PositionZTextBoxEditMode;
            if (GuiTextBox((Rectangle){ 840, 120, 48, 24 }, ScaleXTextBoxText, 128, ScaleXTextBoxEditMode)) ScaleXTextBoxEditMode = !ScaleXTextBoxEditMode;
            if (GuiTextBox((Rectangle){ 888, 120, 48, 24 }, ScaleYTextBoxText, 128, ScaleYTextBoxEditMode)) ScaleYTextBoxEditMode = !ScaleYTextBoxEditMode;
            if (GuiTextBox((Rectangle){ 936, 120, 48, 24 }, ScaleZTextBoxText, 128, ScaleZTextBoxEditMode)) ScaleZTextBoxEditMode = !ScaleZTextBoxEditMode;
            if (GuiTextBox((Rectangle){ 840, 144, 48, 24 }, AngleXTextBoxText, 128, AngleXTextBoxEditMode)) AngleXTextBoxEditMode = !AngleXTextBoxEditMode;
            if (GuiTextBox((Rectangle){ 888, 144, 48, 24 }, AngleYTextBoxText, 128, AngleYTextBoxEditMode)) AngleYTextBoxEditMode = !AngleYTextBoxEditMode;
            if (GuiTextBox((Rectangle){ 936, 144, 48, 24 }, AngleZTextBoxText, 128, AngleZTextBoxEditMode)) AngleZTextBoxEditMode = !AngleZTextBoxEditMode;
            GuiLabel((Rectangle){ 808, 120, 32, 24 }, "Scl :");
            GuiLabel((Rectangle){ 808, 96, 32, 24 }, "Pos :");
            GuiLabel((Rectangle){ 808, 176, 80, 12 }, "Object ID :");
            GuiLabel((Rectangle){ 1016, 56, 40, 24 }, "Mesh :");
            GuiLabel((Rectangle){ 1024, 96, 32, 24 }, "1");
            GuiLabel((Rectangle){ 1024, 120, 32, 24 }, "2");
            if (GuiTextBox((Rectangle){ 1056, 96, 144, 24 }, ParamTextBox1Text, 128, ParamTextBox1EditMode)) ParamTextBox1EditMode = !ParamTextBox1EditMode;
            if (GuiTextBox((Rectangle){ 1056, 120, 144, 24 }, Param2TextBoxText, 128, Param2TextBoxEditMode)) Param2TextBoxEditMode = !Param2TextBoxEditMode;
            GuiCheckBox((Rectangle){ 960, 168, 24, 24 }, NULL, &HideObjectRadioButtonChecked);
            GuiLabel((Rectangle){ 936, 176, 32, 12 }, "Hide:");
            AddLogicButtonPressed = GuiButton((Rectangle){ 1224, 72, 96, 24 }, "Add"); 
            RemoveLogicButtonPressed = GuiButton((Rectangle){ 1320, 72, 96, 24 }, "Remove"); 
            if (GuiTextBox((Rectangle){ 1224, 48, 192, 24 }, LogicTextBoxText, 128, LogicTextBoxEditMode)) LogicTextBoxEditMode = !LogicTextBoxEditMode;
            GuiListView((Rectangle){ 1224, 96, 192, 120 }, "No logic", &LogicListViewScrollIndex, &LogicListViewActive);
            GuiPanel((Rectangle){ 1440, 48, 144, 144 }, NULL);
            MaterialChangeButtonPressed = GuiButton((Rectangle){ 1440, 192, 192, 24 }, "Change material"); 
            Rotate90ButtonPressed = GuiButton((Rectangle){ 1584, 48, 48, 24 }, "R90"); 
            MirrorHorButtonPressed = GuiButton((Rectangle){ 1584, 96, 48, 24 }, "MRH"); 
            MirrorVerticalButtonPressed = GuiButton((Rectangle){ 1584, 144, 48, 24 }, "MRV"); 
            GuiLabel((Rectangle){ 1584, 72, 48, 24 }, "Rotate");
            GuiLabel((Rectangle){ 1584, 120, 48, 24 }, "Mirror");
            CreateButtonCollisionsPressed = GuiButton((Rectangle){ 1032, 272, 144, 24 }, "Create collision mesh"); 
            GuiLabel((Rectangle){ 1096, 304, 24, 24 }, "Or");
            GuiLabel((Rectangle){ 1040, 328, 128, 12 }, "Choose colider settings");
            Button073Pressed = GuiButton((Rectangle){ 1032, 232, 144, 24 }, "Remove collision mesh"); 
            if (GuiTextBox((Rectangle){ 1536, 288, 96, 24 }, Text, 128, EditMode)) EditMode = !EditMode;
            MELabelPressed = GuiLabelButton((Rectangle){ 24, 480, 240, 24 }, "Program by : Core2DuoEver");
            GithubLabelButtonPressed = GuiLabelButton((Rectangle){ 24, 504, 240, 24 }, "https://github.com/Core2DuoEver/Fishtank");
            if (GuiDropdownBox((Rectangle){ 672, 216, 96, 24 }, "Filter; Meshe; Model; Entity", &FilterDropdownActive, FilterDropdownEditMode)) FilterDropdownEditMode = !FilterDropdownEditMode;
            if (GuiDropdownBox((Rectangle){ 0, 0, 96, 24 }, "File;Save;Load;Settings;Exit", &FileDropdownActive, FileDropdownEditMode)) FileDropdownEditMode = !FileDropdownEditMode;
            if (GuiDropdownBox((Rectangle){ 96, 0, 96, 24 }, "Model;Add model;Manage modelsl", &ModelDropdownActive, ModelDropdownEditMode)) ModelDropdownEditMode = !ModelDropdownEditMode;
            if (GuiDropdownBox((Rectangle){ 192, 0, 96, 24 }, "Material;Add material;Manage materials", &MaterialDropdownActive, MaterialDropdownEditMode)) MaterialDropdownEditMode = !MaterialDropdownEditMode;
            if (GuiDropdownBox((Rectangle){ 288, 0, 96, 24 }, "Map; Edit map settings; Compile collisions; Export map", &MapdropdownActive, MapdropdownEditMode)) MapdropdownEditMode = !MapdropdownEditMode;
            if (GuiDropdownBox((Rectangle){ 576, 0, 96, 24 }, "Run;  Run settings", &RunDropdownActive, RunDropdownEditMode)) RunDropdownEditMode = !RunDropdownEditMode;
            if (GuiDropdownBox((Rectangle){ 1056, 56, 144, 24 }, "Poly", &MeshTypeDropboxActive, MeshTypeDropboxEditMode)) MeshTypeDropboxEditMode = !MeshTypeDropboxEditMode;
            if (GuiDropdownBox((Rectangle){ 1056, 168, 144, 24 }, "No collision", &DropdownBox055Active, DropdownBox055EditMode)) DropdownBox055EditMode = !DropdownBox055EditMode;
            if (GuiDropdownBox((Rectangle){ 1032, 344, 144, 24 }, "No collision; Collides; Walkable", &ColiderSettingsDropBoxActive, ColiderSettingsDropBoxEditMode)) ColiderSettingsDropBoxEditMode = !ColiderSettingsDropBoxEditMode;
            if (GuiDropdownBox((Rectangle){ 1440, 240, 192, 24 }, NULL, &ChooseShaderActive, ChooseShaderEditMode)) ChooseShaderEditMode = !ChooseShaderEditMode;
            if (GuiDropdownBox((Rectangle){ 1440, 288, 96, 24 }, NULL, &ShaderSettingsDropdownBoxActive, ShaderSettingsDropdownBoxEditMode)) ShaderSettingsDropdownBoxEditMode = !ShaderSettingsDropdownBoxEditMode;
            
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

