//Refactored version of main_tank.cpp

//Includes

#include "Bait.h"

#include "material_database.h"
#include "model_database.h"
#include "objects_database.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"; 

#include "rcamera_blender.h" //https://github.com/grplyler/raylib-blender-camera

#ifdef _WIN32
#ifndef DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //Disables CL on non-debug builds.
#endif 
#endif

//global vars

float CurrentWindowWidth = STANDART_RESOLUTION_WIDTH;
float CurrentWindowHeight = STANDART_RESOLUTION_HEIGHT;

bool exit_signal = false;

//Bases
material_database mat_db;
objects_database obj_db;
model_database mod_db;

base_object* current_object;

void draw_splash_art(std::string loading_text, Texture splash_texture) {

    BeginDrawing();

        DrawTexture(splash_texture, 0, 0, WHITE);

//Right left corner text handling
#ifdef DEBUG
        DrawText("Debug build from " __DATE__, 500 - (MeasureText("Debug build from " __DATE__, SPLASH_ART_TEXTSIZE)+ SPLASH_ART_BORDERSIZE), 15, SPLASH_ART_TEXTSIZE, RED);
 // DEBUG
#else// Release
        DrawText("Release build from " __DATE__, 500 - (MeasureText("Release build from " __DATE__, SPLASH_ART_TEXTSIZE) + SPLASH_ART_BORDERSIZE), 15, SPLASH_ART_TEXTSIZE, BLACK);
#endif 

        DrawText(loading_text.c_str(), SPLASH_ART_BORDERSIZE + 1, splash_texture.height - (15), SPLASH_ART_TEXTSIZE, BLACK);
    
    EndDrawing();
}

Rectangle texture_to_rec(Texture texture_in) {
    Rectangle rectangle_return;
    rectangle_return = { 0,0,float(texture_in.height),float(texture_in.width) };
    return(rectangle_return);
}

struct GUIState {
    struct ObjectPanel { //Manages objects.
        bool previousStates[4] = {false,false,false,false};
        bool toggles[4] = { false, false, false, false };

        int lastActiveToggle = 0;
        int listScrollIndex = 0;

        char previous_type = OBJECT_DISABLED;

        int previous_ListActive = -1;
        int listActive = -1;
        int filterDropdownActive = 0;
        bool filterDropdownEditMode = false;

        std::string GuiToggle1Text = "";
        std::string GuiToggle2Text = "";
        std::string GuiToggle3Text = "";
        std::string GuiToggle4Text = "";
    };
    struct ToolsPanel {
        bool meshToolActive = false;
        bool modelToolActive = false;
        bool entityToolActive = false;
    };
    struct ObjectTogglePanel {
    bool hideCheckBox = false;
    bool NameTextBoxEditMode = false;
    char NameTextBoxText[128] = "";            // TextBox: NameTextBox
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
    };
    struct MeshObjectTogglePanel {
    bool MeshTypeDropboxEditMode = false;
    int MeshTypeDropboxActive = 0;            // DropdownBox: MeshTypeDropbox
    bool Param1TextBoxEditMode = false;
    char Param1TextBoxText[128] = "";            // TextBox: ParamTextBox1
    bool Param2TextBoxEditMode = false;
    char Param2TextBoxText[128] = "";            // TextBox: Param2TextBox

    std::string param1label = "";
    std::string param2label = "";

    bool DropdownBox055EditMode = false;
    int DropdownBox055Active = 0;            // DropdownBox: DropdownBox055
    };
    struct LogicObjectTogglePanel {
    bool AddLogicButtonPressed = false;            // Button: AddLogicButton
    bool RemoveLogicButtonPressed = false;            // Button: RemoveLogicButton
    bool LogicTextBoxEditMode = false;
    char LogicTextBoxText[128] = "";            // TextBox: LogicTextBox
    int LogicListViewScrollIndex = 0;
    int LogicListViewActive = 0;            // ListView: LogicListView
    };
    struct MeshMaterialTogglePanel {
    bool MaterialChangeButtonPressed = false;            // Button: MaterialChangeButton
    bool Rotate90ButtonPressed = false;            // Button: Rotate90Button
    bool MirrorHorButtonPressed = false;            // Button: MirrorHorButton
    bool MirrorVerticalButtonPressed = false;            // Button: MirrorVerticalButton
    Texture current_preview;

    std::vector<std::pair<Texture,std::string>> current_material_list; //Texture is for holding the texture, while the string is for the paths.

    float scroll_index = 0;
    unsigned int previous_scroll_index = 0;

    unsigned int current_ceil_height = ceil((CurrentWindowHeight - 24) / 104);

    };
    struct ModelCollisionTogglePanel {
    bool CreateButtonCollisionsPressed = false;            // Button: CreateButtonCollisions
    bool ColiderSettingsDropBoxEditMode = false;
    int ColiderSettingsDropBoxActive = 0;            // DropdownBox: ColiderSettingsDropBox
    };
    struct ModelShaderTogglePanel {
    bool ChooseShaderEditMode = false;
    int ChooseShaderActive = 0;            // DropdownBox: ChooseShader
    bool ShaderSettingsDropdownBoxEditMode = false;
    int ShaderSettingsDropdownBoxActive = 0;            // DropdownBox: ShaderSettingsDropdownBox
    bool ShaderParamEditMode = false;
    char ShaderParamText[128] = "";            // TextBox: 
    };
    struct CreditsWindow {
    bool CreditsWindowActive = false;            // WindowBox: WindowBox079
    };
    struct HelpWindow {
        bool HelpWindowActive = false;            // WindowBox: WindowBox079
    };
    struct Dropdowns {
        struct DropdownState {
            int active = 0;
            bool editMode = false;
        };

        DropdownState file = { 0, false };
        DropdownState model = { 0, false };
        DropdownState material = { 0, false };
        DropdownState map = { 0, false };
        DropdownState run = { 0, false };
    };
    struct object_state {
        bool mesh_active = false;
        bool model_active = false;
        bool entity_active = false;
        bool disabled = true;
    };
    struct material_add_window {
        bool material_window_state = false;
        bool material_dropdown_bool = false;
        int material_dropdown_index = 0;
        int material_chosen_wrap = 0;
        bool material_wrap_bool = false;
        
        RenderTexture material_texture_preview;
        
        std::vector <std::pair<Texture, std::string>> vec_mat; //Holds textures for the material

        Camera preview_camera = { {6.0f, 6.0f, 6.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, CAMERA_PERSPECTIVE };

        Material mat_create;

        Mesh std_mesh;

        std::string shader_path;
    };
    
    object_state current_object_state;
    MeshMaterialTogglePanel meshmaterialtoggle;
    ModelCollisionTogglePanel modelcollisiontoggle;
    ModelShaderTogglePanel modelshadertoggle;
    CreditsWindow credit;
    LogicObjectTogglePanel logictoggle;
    MeshObjectTogglePanel meshtoggle;
    ObjectPanel objects;
    ToolsPanel tools;
    Dropdowns dropdowns;
    ObjectTogglePanel objecttoggle;
    HelpWindow hwindow;
    material_add_window MaterialWindow;

    bool helpButtonPressed = false;
    bool CreditsWindowActive = true;            // WindowBox: CreditsWindow

};

void init(GUIState& gui_state_in) {
    //Init's
    
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(500, 250, WINDOW_NAME);
    
    Texture splash_art_texture = LoadTexture("resources/GuiElements/SplashART/splash.png");

    std::future<void> material_init_async = std::async(std::launch::async, []() {
        mat_db.database_init();
    });
 
    
    bool thread_working = true;

    while (thread_working) {
        if (material_init_async.wait_for(std::chrono::milliseconds(16)) == std::future_status::ready) {
            thread_working = false;
        }

        draw_splash_art("Initalising textures database", splash_art_texture);
        
    }

    draw_splash_art("Initalising GUI", splash_art_texture);

    draw_splash_art("Initalising textures database", splash_art_texture);


    UnloadTexture(splash_art_texture);

    CloseWindow();

   // SetTargetFPS(TARGET_FPS);


}

void draw_gui_and_world(GUIState& gui_state, RenderTexture texture_world) {
    BeginDrawing();

    GuiUnlock();

//    if (FilterDropdownEditMode || FileDropdownEditMode || ModelDropdownEditMode || MaterialDropdownEditMode || MapdropdownEditMode || RunDropdownEditMode || MeshTypeDropboxEditMode || DropdownBox055EditMode || ColiderSettingsDropBoxEditMode || ChooseShaderEditMode || ShaderSettingsDropdownBoxEditMode) GuiLock();

    GuiPanel({ 0, 0, CurrentWindowWidth, CurrentWindowHeight }, NULL); //Panel BG main

    DrawTexturePro(texture_world.texture, { 0, 0, (float)texture_world.texture.width, (float)-texture_world.texture.height }, { 24, 24, (float)texture_world.texture.width, (float)texture_world.texture.height }, { 0, 0 }, 0, WHITE); //Renders Vetically mirroed because RenderTexture is vertically mirrored from TextureMode

    GuiPanel({ 0, 0, CurrentWindowWidth, 24 }, NULL); //Panel tools dropdowns
    GuiPanel({ CurrentWindowWidth * float(0.75), 0, CurrentWindowWidth - CurrentWindowWidth * float(0.75), 24 }, NULL); //Decorative panel over RUN and ?
    GuiPanel({ CurrentWindowWidth * float(0.75), 24, CurrentWindowWidth - CurrentWindowWidth * float(0.75), 192 }, NULL); //Decorative panel over obejct buttons
    GuiPanel({ 0, 24, 24, CurrentWindowHeight }, NULL); //Tools panel
    GuiPanel({ CurrentWindowWidth * float(0.75), 216, CurrentWindowWidth * float(0.875) - CurrentWindowWidth * float(0.75), 24 }, NULL); //Objects label BG

    if (GuiButton({ CurrentWindowWidth - 24, 0, 24, 24 }, "?")) {
        gui_state.helpButtonPressed = !gui_state.helpButtonPressed;
    } //Help button. -24 cuz its at the edge of the screen.

    //Toggle logic.
    for (int i = 0; i < 4; i++) {
        gui_state.objects.previousStates[i] = gui_state.objects.toggles[i];
    }
    if (!obj_db.get_gui_list_string().empty()) {
        GuiListView({ CurrentWindowWidth * float(0.75), 240, CurrentWindowWidth - (CurrentWindowWidth * float(0.75)) - 1, CurrentWindowHeight - 241 }, obj_db.get_gui_list_string().c_str(), &gui_state.objects.listScrollIndex, &gui_state.objects.listActive); //Objects list
    }
    if (gui_state.current_object_state.disabled) {
        GuiLock(); //Locking some interface features if list is empty.
    }

    GuiToggle({ CurrentWindowWidth * float(0.75), 24, (CurrentWindowWidth * float(0.8125) - CurrentWindowWidth * float(0.75)), 24 }, gui_state.objects.GuiToggle1Text.c_str(), &gui_state.objects.toggles[0]); //Object button 1
    GuiToggle({ CurrentWindowWidth * float(0.8125), 24, (CurrentWindowWidth * float(0.875) - CurrentWindowWidth * float(0.8125)), 24 }, gui_state.objects.GuiToggle2Text.c_str(), &gui_state.objects.toggles[1]);//Object button 2
    GuiToggle({ CurrentWindowWidth * float(0.875), 24, (CurrentWindowWidth * float(0.9375) - CurrentWindowWidth * float(0.875)), 24 }, gui_state.objects.GuiToggle3Text.c_str(), &gui_state.objects.toggles[2]);//Object button 3
    GuiToggle({ CurrentWindowWidth * float(0.9375)  , 24, (CurrentWindowWidth - CurrentWindowWidth * float(0.9375)), 24 }, gui_state.objects.GuiToggle4Text.c_str(), &gui_state.objects.toggles[3]);//Object button 4

    if (gui_state.current_object_state.disabled) { //Unlocking it back.
        GuiUnlock();
    }

    //Code for handling Toggles. Only ONE can live.

    for (int i = 0; i < 4; i++) {
        if (gui_state.objects.toggles[i] && !gui_state.objects.previousStates[i]) {
            for (int j = 0; j < 4; j++) {
                if (j != i) {
                    gui_state.objects.toggles[j] = false;
                }
            }
            gui_state.objects.lastActiveToggle = i;
            break;
        }
    }

    GuiLabel({ CurrentWindowWidth * float(0.75), 216, 96, 24 }, "Objects"); //Objects label

    gui_state.tools.meshToolActive = GuiButton({ 0, 24, 24, 24 }, "M");
    gui_state.tools.modelToolActive = GuiButton({ 0, 48, 24, 24 }, ".M");
//    gui_state.tools.entityToolActive = GuiButton({ 0, 72, 24, 24 }, "E");

    if (GuiDropdownBox({ CurrentWindowWidth * float(0.875), 216, CurrentWindowWidth - CurrentWindowWidth * float(0.875), 24 }, "Filter; Meshe; Model; Entity", &gui_state.objects.filterDropdownActive, gui_state.objects.filterDropdownEditMode)) gui_state.objects.filterDropdownEditMode = !gui_state.objects.filterDropdownEditMode;
    if (GuiDropdownBox({ 0, 0, 96, 24 }, "File;Save;Load;About;Exit", &gui_state.dropdowns.file.active, gui_state.dropdowns.file.editMode)) gui_state.dropdowns.file.editMode = !gui_state.dropdowns.file.editMode;
    if (GuiDropdownBox({ 96, 0, 96, 24 }, "Material;Add material", &gui_state.dropdowns.material.active, gui_state.dropdowns.material.editMode)) gui_state.dropdowns.material.editMode = !gui_state.dropdowns.material.editMode;
//    if (GuiDropdownBox({ 192, 0, 96, 24 }, "Map; Edit map settings;Compile collisions;Export map", &gui_state.dropdowns.map.active, gui_state.dropdowns.map.editMode)) gui_state.dropdowns.map.editMode = !gui_state.dropdowns.map.editMode;
    if (GuiDropdownBox({ CurrentWindowWidth * float(0.75), 0, 96, 24 }, "Run;Coming soon!", &gui_state.dropdowns.run.active, gui_state.dropdowns.run.editMode)) gui_state.dropdowns.run.editMode = !gui_state.dropdowns.run.editMode;

    if (gui_state.credit.CreditsWindowActive) {
        gui_state.credit.CreditsWindowActive = !GuiWindowBox({ 30, 34, 336, 168 }, "Credits");
        GuiLabel({ 40, 60, 240, 24 }, "Program by : Core2DuoEver");
        if (GuiLabelButton({ 40, 84, 240, 24 }, "https://github.com/Core2DuoEver/Fishtank")) {
            OpenURL("https://github.com/Core2DuoEver/Fishtank");
        }
        GuiLabel({ 40, 108, 328, 24 }, "Opensource : RayLib, RayGui, ZIP, tinyfiledialogs, \nboost, nlohmann/Json, rcamera Blender");
    }

    if (gui_state.helpButtonPressed) {
        gui_state.helpButtonPressed = !GuiWindowBox({ 168, 72, 400, 250 }, "Help");

        GuiLabel({ 176,104,400,24 }, "'X/Z/C' - Control the X/Z/Y position of an object, scroll/click to move");
        GuiLabel({ 176,128,400,24 }, "'SHIFT + X/Z/C' - Control the scale of an object, scroll/click to scale");
        GuiLabel({ 176,152,400,24 }, "'ALT + X/Z/C' - Control the angle of an object, scroll/click to rotate");
        GuiLabel({ 176,176,400,24 }, "'DELETE' - Delete selected object");
        GuiLabel({ 176,200,400,24 }, "'CTRL+D' - Duplicate selected object");
        GuiLabel({ 176,224,400,24 }, "'Central mouse button' - Control camera");
        GuiLabel({ 176,248,400,24 }, "'CTRL+F' - Change camera mode");

    }
    
    //Add textures, change to empty label buttons before that.
    if (!gui_state.current_object_state.disabled) { //IF not disabled.
        if (gui_state.objects.toggles[0]) {
            float panelX = CurrentWindowWidth * 0.75f;
            float textBoxWidth = (CurrentWindowWidth - panelX) * 0.1875f; //6/32 seems to be the max to be visible.
            float startX = panelX + 60;

            if (GuiTextBox({ startX, 56, (CurrentWindowWidth - panelX) - 72, 24 }, gui_state.objecttoggle.NameTextBoxText, 128, gui_state.objecttoggle.NameTextBoxEditMode)) {
                gui_state.objecttoggle.NameTextBoxEditMode = !gui_state.objecttoggle.NameTextBoxEditMode;
                if (!gui_state.objecttoggle.NameTextBoxEditMode) {
                    current_object->set_object_name(gui_state.objecttoggle.NameTextBoxText);
                    obj_db.reload_gui_list();
                }
            }
            if (!gui_state.objecttoggle.NameTextBoxEditMode) {
                strcpy_s(gui_state.objecttoggle.NameTextBoxText, sizeof(gui_state.objecttoggle.NameTextBoxText), current_object->get_object_name().c_str());
            }

            if (GuiTextBox({ startX, 96, textBoxWidth, 24 }, gui_state.objecttoggle.PositionXTextBoxText, 128, gui_state.objecttoggle.PositionXTextBoxEditMode)) {
                gui_state.objecttoggle.PositionXTextBoxEditMode = !gui_state.objecttoggle.PositionXTextBoxEditMode;
                if (!gui_state.objecttoggle.PositionXTextBoxEditMode) {
                    Vector3 temp_toggle = current_object->get_position();
                    try {
                        current_object->set_position(std::stof(gui_state.objecttoggle.PositionXTextBoxText), MATRIX_CHANGE_X); //Try to set the position using STOF, 
                    }
                    catch (const std::invalid_argument&) {
                        current_object->set_position(temp_toggle);
                    }
                    catch (const std::out_of_range&) {
                        current_object->set_position(temp_toggle);
                    }
                }
            }
            if (!gui_state.objecttoggle.PositionXTextBoxEditMode) {
                strcpy_s(gui_state.objecttoggle.PositionXTextBoxText, sizeof(gui_state.objecttoggle.PositionXTextBoxText), std::to_string(current_object->get_position().x).c_str());
            }

            // Position Y
            if (GuiTextBox({ startX + textBoxWidth, 96, textBoxWidth, 24 }, gui_state.objecttoggle.PositionYTextBoxText, 128, gui_state.objecttoggle.PositionYTextBoxEditMode)) {
                gui_state.objecttoggle.PositionYTextBoxEditMode = !gui_state.objecttoggle.PositionYTextBoxEditMode;
                if (!gui_state.objecttoggle.PositionYTextBoxEditMode) {
                    Vector3 temp_toggle = current_object->get_position();
                    try {
                        current_object->set_position(std::stof(gui_state.objecttoggle.PositionYTextBoxText), MATRIX_CHANGE_Y);
                    }
                    catch (const std::invalid_argument&) {
                        current_object->set_position(temp_toggle);
                    }
                    catch (const std::out_of_range&) {
                        current_object->set_position(temp_toggle);
                    }
                }
            }
            if (!gui_state.objecttoggle.PositionYTextBoxEditMode) {
                strcpy_s(gui_state.objecttoggle.PositionYTextBoxText, sizeof(gui_state.objecttoggle.PositionYTextBoxText), std::to_string(current_object->get_position().y).c_str());
            }

            // Position Z
            if (GuiTextBox({ startX + 2 * textBoxWidth, 96, textBoxWidth, 24 }, gui_state.objecttoggle.PositionZTextBoxText, 128, gui_state.objecttoggle.PositionZTextBoxEditMode)) {
                gui_state.objecttoggle.PositionZTextBoxEditMode = !gui_state.objecttoggle.PositionZTextBoxEditMode;
                if (!gui_state.objecttoggle.PositionZTextBoxEditMode) {
                    Vector3 temp_toggle = current_object->get_position();
                    try {
                        current_object->set_position(std::stof(gui_state.objecttoggle.PositionZTextBoxText), MATRIX_CHANGE_Z);
                    }
                    catch (const std::invalid_argument&) {
                        current_object->set_position(temp_toggle);
                    }
                    catch (const std::out_of_range&) {
                        current_object->set_position(temp_toggle);
                    }
                }
            }
            if (!gui_state.objecttoggle.PositionZTextBoxEditMode) {
                strcpy_s(gui_state.objecttoggle.PositionZTextBoxText, sizeof(gui_state.objecttoggle.PositionZTextBoxText), std::to_string(current_object->get_position().z).c_str());
            }

            // Scale X
            if (GuiTextBox({ startX, 120, textBoxWidth, 24 }, gui_state.objecttoggle.ScaleXTextBoxText, 128, gui_state.objecttoggle.ScaleXTextBoxEditMode)) {
                gui_state.objecttoggle.ScaleXTextBoxEditMode = !gui_state.objecttoggle.ScaleXTextBoxEditMode;
                if (!gui_state.objecttoggle.ScaleXTextBoxEditMode) {
                    Vector3 temp_toggle = current_object->get_scale();
                    try {
                        current_object->set_scale(std::stof(gui_state.objecttoggle.ScaleXTextBoxText), MATRIX_CHANGE_X);
                    }
                    catch (const std::invalid_argument&) {
                        current_object->set_scale(temp_toggle);
                    }
                    catch (const std::out_of_range&) {
                        current_object->set_scale(temp_toggle);
                    }
                }
            }
            if (!gui_state.objecttoggle.ScaleXTextBoxEditMode) {
                strcpy_s(gui_state.objecttoggle.ScaleXTextBoxText, sizeof(gui_state.objecttoggle.ScaleXTextBoxText), std::to_string(current_object->get_scale().x).c_str());
            }

            // Scale Y
            if (GuiTextBox({ startX + textBoxWidth, 120, textBoxWidth, 24 }, gui_state.objecttoggle.ScaleYTextBoxText, 128, gui_state.objecttoggle.ScaleYTextBoxEditMode)) {
                gui_state.objecttoggle.ScaleYTextBoxEditMode = !gui_state.objecttoggle.ScaleYTextBoxEditMode;
                if (!gui_state.objecttoggle.ScaleYTextBoxEditMode) {
                    Vector3 temp_toggle = current_object->get_scale();
                    try {
                        current_object->set_scale(std::stof(gui_state.objecttoggle.ScaleYTextBoxText), MATRIX_CHANGE_Y);
                    }
                    catch (const std::invalid_argument&) {
                        current_object->set_scale(temp_toggle);
                    }
                    catch (const std::out_of_range&) {
                        current_object->set_scale(temp_toggle);
                    }
                }
            }
            if (!gui_state.objecttoggle.ScaleYTextBoxEditMode) {
                strcpy_s(gui_state.objecttoggle.ScaleYTextBoxText, sizeof(gui_state.objecttoggle.ScaleYTextBoxText), std::to_string(current_object->get_scale().y).c_str());
            }

            // Scale Z
            if (GuiTextBox({ startX + 2 * textBoxWidth, 120, textBoxWidth, 24 }, gui_state.objecttoggle.ScaleZTextBoxText, 128, gui_state.objecttoggle.ScaleZTextBoxEditMode)) {
                gui_state.objecttoggle.ScaleZTextBoxEditMode = !gui_state.objecttoggle.ScaleZTextBoxEditMode;
                if (!gui_state.objecttoggle.ScaleZTextBoxEditMode) {
                    Vector3 temp_toggle = current_object->get_scale();
                    try {
                        current_object->set_scale(std::stof(gui_state.objecttoggle.ScaleZTextBoxText), MATRIX_CHANGE_Z);
                    }
                    catch (const std::invalid_argument&) {
                        current_object->set_scale(temp_toggle);
                    }
                    catch (const std::out_of_range&) {
                        current_object->set_scale(temp_toggle);
                    }
                }
            }
            if (!gui_state.objecttoggle.ScaleZTextBoxEditMode) {
                strcpy_s(gui_state.objecttoggle.ScaleZTextBoxText, sizeof(gui_state.objecttoggle.ScaleZTextBoxText), std::to_string(current_object->get_scale().z).c_str());
            }

            // Angle X
            if (GuiTextBox({ startX, 144, textBoxWidth, 24 }, gui_state.objecttoggle.AngleXTextBoxText, 128, gui_state.objecttoggle.AngleXTextBoxEditMode)) {
                gui_state.objecttoggle.AngleXTextBoxEditMode = !gui_state.objecttoggle.AngleXTextBoxEditMode;
                if (!gui_state.objecttoggle.AngleXTextBoxEditMode) {
                    // Для углов нужно сохранять текущий угол и восстанавливать при ошибке
                    Vector3 temp_toggle = current_object->get_angle();
                    try {
                        current_object->set_angle(std::stof(gui_state.objecttoggle.AngleXTextBoxText), MATRIX_CHANGE_X);
                    }
                    catch (const std::invalid_argument&) {
                        current_object->set_angle(temp_toggle);
                    }
                    catch (const std::out_of_range&) {
                        current_object->set_angle(temp_toggle);
                    }
                }
            }
            if (!gui_state.objecttoggle.AngleXTextBoxEditMode) {
                strcpy_s(gui_state.objecttoggle.AngleXTextBoxText, sizeof(gui_state.objecttoggle.AngleXTextBoxText), std::to_string(current_object->get_angle().x).c_str());
            }

            // Angle Y
            if (GuiTextBox({ startX + textBoxWidth, 144, textBoxWidth, 24 }, gui_state.objecttoggle.AngleYTextBoxText, 128, gui_state.objecttoggle.AngleYTextBoxEditMode)) {
                gui_state.objecttoggle.AngleYTextBoxEditMode = !gui_state.objecttoggle.AngleYTextBoxEditMode;
                if (!gui_state.objecttoggle.AngleYTextBoxEditMode) {
                    Vector3 temp_toggle = current_object->get_angle();
                    try {
                        current_object->set_angle(std::stof(gui_state.objecttoggle.AngleYTextBoxText), MATRIX_CHANGE_Y);
                    }
                    catch (const std::invalid_argument&) {
                        current_object->set_angle(temp_toggle);
                    }
                    catch (const std::out_of_range&) {
                        current_object->set_angle(temp_toggle);
                    }
                }
            }
            if (!gui_state.objecttoggle.AngleYTextBoxEditMode) {
                // Vector3 euler_angles = quaternion_to_euler(current_object->get_angle());
                strcpy_s(gui_state.objecttoggle.AngleYTextBoxText, sizeof(gui_state.objecttoggle.AngleYTextBoxText), std::to_string(current_object->get_angle().y).c_str());
            }

            // Angle Z
            if (GuiTextBox({ startX + 2 * textBoxWidth, 144, textBoxWidth, 24 }, gui_state.objecttoggle.AngleZTextBoxText, 128, gui_state.objecttoggle.AngleZTextBoxEditMode)) {
                gui_state.objecttoggle.AngleZTextBoxEditMode = !gui_state.objecttoggle.AngleZTextBoxEditMode;
                if (!gui_state.objecttoggle.AngleZTextBoxEditMode) {
                    Vector3 temp_toggle = current_object->get_angle();
                    try {
                        current_object->set_angle(std::stof(gui_state.objecttoggle.AngleZTextBoxText), MATRIX_CHANGE_Z);
                    }
                    catch (const std::invalid_argument&) {
                        current_object->set_angle(temp_toggle);
                    }
                    catch (const std::out_of_range&) {
                        current_object->set_angle(temp_toggle);
                    }
                }
            }
            if (!gui_state.objecttoggle.AngleZTextBoxEditMode) {
                // Vector3 euler_angles = quaternion_to_euler(current_object->get_angle());
                strcpy_s(gui_state.objecttoggle.AngleZTextBoxText, sizeof(gui_state.objecttoggle.AngleZTextBoxText), std::to_string(current_object->get_angle().z).c_str());
            }

            GuiLabel({ panelX, 96, 32, 24 }, "Pos :");
            GuiLabel({ panelX, 120, 32, 24 }, "Scl :");
            GuiLabel({ panelX, 144, 32, 24 }, "Ang :");

            GuiLabel({ panelX, 176, 80, 12 }, "Object ID :");
            GuiLabel({ startX, 80, textBoxWidth, 24 }, "X");
            GuiLabel({ startX + textBoxWidth, 80, textBoxWidth, 24 }, "Y");
            GuiLabel({ startX + 2 * textBoxWidth, 80, textBoxWidth, 24 }, "Z");

            GuiLabel({ startX + 2 * textBoxWidth - 24, 176, 32, 12 }, "Hide:");
            GuiCheckBox({ startX + 2 * textBoxWidth, 168, 24, 24 }, NULL, &gui_state.objecttoggle.hideCheckBox);
        }
        if (gui_state.objects.toggles[1]) {
            if (gui_state.current_object_state.mesh_active) {
                mesh_object* current_mesh_object = obj_db.get_mesh_object(obj_db.get_entry_from_index(gui_state.objects.listActive));
                if (current_mesh_object != nullptr) {
                    float panelX = CurrentWindowWidth * 0.75f;
                    float contentWidth = (CurrentWindowWidth - panelX) - 72;
                    float startX = panelX + 60;

                    GuiLabel({ panelX, 56, 40, 24 }, "Mesh :");

                    std::vector<std::pair<std::string, std::string>> mesh_types_arguments{ {{"Sides"},{""}}, {{""},{""}}, {{""},{""}}, {{"Rings"},{"Slices"}}, {{"Rings"},{"Slices"}}, {{"Slices"},{""}}, {{"Slices"},{""}}, {{"RadSeg"},{"Sides"}}, {{"RadSeg"},{"Sides"}} };

                    if (!mesh_types_arguments[current_mesh_object->get_mesh_type()].first.empty()) {
                        GuiLabel({ panelX, 96, 32, 24 }, mesh_types_arguments[current_mesh_object->get_mesh_type()].first.c_str());
                        if (GuiTextBox({ startX, 96, contentWidth, 24 }, gui_state.meshtoggle.Param1TextBoxText, 128, gui_state.meshtoggle.Param1TextBoxEditMode)) {
                            gui_state.meshtoggle.Param1TextBoxEditMode = !gui_state.meshtoggle.Param1TextBoxEditMode;
                            try {
                                current_mesh_object->set_param1(std::stoi(gui_state.meshtoggle.Param1TextBoxText));
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());
                            }
                            catch (const std::invalid_argument&) {
                                std::cout << "FISHTANK: ERROR: Invalid argument at the first parametre! \n";
                            }
                            catch (const std::out_of_range&) {
                                std::cout << "FISHTANK: ERROR: Out of range at the first parametre! \n";
                            }
                        }
                        if (!gui_state.meshtoggle.Param1TextBoxEditMode) {
                            strcpy_s(gui_state.meshtoggle.Param1TextBoxText, sizeof(gui_state.meshtoggle.Param1TextBoxText), std::to_string(current_mesh_object->get_param1()).c_str());
                        }
                    }
                    if (!mesh_types_arguments[current_mesh_object->get_mesh_type()].second.empty()) {
                        GuiLabel({ panelX, 120, 32, 24 }, mesh_types_arguments[current_mesh_object->get_mesh_type()].second.c_str());

                        if (GuiTextBox({ startX, 120, contentWidth, 24 }, gui_state.meshtoggle.Param2TextBoxText, 128, gui_state.meshtoggle.Param2TextBoxEditMode)) {
                            gui_state.meshtoggle.Param2TextBoxEditMode = !gui_state.meshtoggle.Param2TextBoxEditMode;

                            try {
                                current_mesh_object->set_param2(std::stoi(gui_state.meshtoggle.Param2TextBoxText));
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());
                            }
                            catch (const std::invalid_argument&) {
                                std::cout << "FISHTANK: ERROR: Invalid argument at the second parametre! \n";
                            }
                            catch (const std::out_of_range&) {
                                std::cout << "FISHTANK: ERROR: Out of range at the second parametre! \n";
                            }
                        }
                        if (!gui_state.meshtoggle.Param2TextBoxEditMode) {
                            strcpy_s(gui_state.meshtoggle.Param2TextBoxText, sizeof(gui_state.meshtoggle.Param2TextBoxText), std::to_string(current_mesh_object->get_param2()).c_str());
                        }
                    }

                    //To implement
                    if (GuiDropdownBox({ startX, 168, contentWidth, 24 }, "No collision; Collides; Walkable", &gui_state.meshtoggle.DropdownBox055Active, gui_state.meshtoggle.DropdownBox055EditMode)) {
                        gui_state.meshtoggle.DropdownBox055EditMode = !gui_state.meshtoggle.DropdownBox055EditMode;

                    }

                    gui_state.meshtoggle.MeshTypeDropboxActive = current_mesh_object->get_mesh_type();

                    if (GuiDropdownBox({ startX, 56, contentWidth, 24 }, "Poly; Plane; Cube; Sphere; Hemisphere; Cylinder; Cone; Torus; Knot", &gui_state.meshtoggle.MeshTypeDropboxActive, gui_state.meshtoggle.MeshTypeDropboxEditMode)) { //ISSUE. CAN TRIGGER AN OBJECT CHANGE due to overlay, fix by lock/unlock gui
                        gui_state.meshtoggle.MeshTypeDropboxEditMode = !gui_state.meshtoggle.MeshTypeDropboxEditMode;

                        if (!gui_state.meshtoggle.MeshTypeDropboxEditMode) {

                            switch (gui_state.meshtoggle.MeshTypeDropboxActive) {
                            case 0: {
                                current_mesh_object->set_mesh_type(mesh_poly);
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());

                            } break;
                            case 1: {
                                current_mesh_object->set_mesh_type(mesh_plane);
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());

                            } break;
                            case 2: {
                                current_mesh_object->set_mesh_type(mesh_cube);
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());

                            } break;
                            case 3: {
                                current_mesh_object->set_mesh_type(mesh_sphere);
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());

                            } break;
                            case 4: {
                                current_mesh_object->set_mesh_type(mesh_hemisphere);
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());

                            } break;
                            case 5: {
                                current_mesh_object->set_mesh_type(mesh_cylinder);
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());

                            } break;
                            case 6: {
                                current_mesh_object->set_mesh_type(mesh_cone);
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());

                            } break;
                            case 7: {
                                current_mesh_object->set_mesh_type(mesh_torus);
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());

                            } break;
                            case 8: {
                                current_mesh_object->set_mesh_type(mesh_knot);
                                obj_db.change_mesh_object_model(obj_db.get_entry_from_index(gui_state.objects.listActive), current_mesh_object->gen_mesh_model());

                            } break;

                            }
                        }

                    }
                }


            }
            if (gui_state.current_object_state.model_active) {
            //    gui_state.modelcollisiontoggle.CreateButtonCollisionsPressed = GuiButton({ 1032, 272, 144, 24 }, "Create collision mesh"); //Change to remove IF exist
            //    GuiLabel({ 1096, 304, 24, 24 }, "Or");
            
                GuiLabel({ 1040, 328, 128, 12 }, "Choose colider settings");
                if (GuiDropdownBox({ 1032, 344, 144, 24 }, "No collision; Collides; Walkable", &gui_state.modelcollisiontoggle.ColiderSettingsDropBoxActive, gui_state.modelcollisiontoggle.ColiderSettingsDropBoxEditMode)) gui_state.modelcollisiontoggle.ColiderSettingsDropBoxEditMode = !gui_state.modelcollisiontoggle.ColiderSettingsDropBoxEditMode;
            
                //Using mods

            }
        }
        if (gui_state.objects.toggles[2]) {
            gui_state.logictoggle.AddLogicButtonPressed = GuiButton({ CurrentWindowWidth * (0.75f), 72, CurrentWindowWidth * (0.125f), 24 }, "Add");
            gui_state.logictoggle.RemoveLogicButtonPressed = GuiButton({ CurrentWindowWidth * (0.875f), 72, CurrentWindowWidth * (0.125f), 24 }, "Remove");

            if (gui_state.logictoggle.AddLogicButtonPressed) {
                current_object->insert_logic(gui_state.logictoggle.LogicTextBoxText, gui_state.logictoggle.LogicListViewActive);
                gui_state.logictoggle.LogicListViewActive = current_object->get_logic_size() - 1;
            }

            if (gui_state.logictoggle.RemoveLogicButtonPressed) {
                current_object->remove_logic(gui_state.logictoggle.LogicListViewActive);
            }

            if (GuiTextBox({ CurrentWindowWidth * (0.75f), 48, CurrentWindowWidth * (0.25f), 24 }, gui_state.logictoggle.LogicTextBoxText, 128, gui_state.logictoggle.LogicTextBoxEditMode)) gui_state.logictoggle.LogicTextBoxEditMode = !gui_state.logictoggle.LogicTextBoxEditMode;

            GuiListView({ CurrentWindowWidth * (0.75f), 96, CurrentWindowWidth * (0.25f), 120 }, current_object->get_logic_string().c_str(), &gui_state.logictoggle.LogicListViewScrollIndex, &gui_state.logictoggle.LogicListViewActive);

        }
        if (gui_state.objects.toggles[3]) {
            if (gui_state.current_object_state.mesh_active) {

                mesh_object* current_mesh_object = obj_db.get_mesh_object(obj_db.get_entry_from_index(gui_state.objects.listActive));

                DrawTexturePro(gui_state.meshmaterialtoggle.current_preview, texture_to_rec(gui_state.meshmaterialtoggle.current_preview), { CurrentWindowWidth * float(0.75), 48, 144, 144 }, { 0,0 }, 0, WHITE);

                if (GuiButton({ CurrentWindowWidth * float(0.75), 192, CurrentWindowWidth * float(0.25), 24 }, "Change material")) {
                    gui_state.meshmaterialtoggle.MaterialChangeButtonPressed = !gui_state.meshmaterialtoggle.MaterialChangeButtonPressed;
                }

                if (gui_state.meshmaterialtoggle.MaterialChangeButtonPressed) {
                    GuiPanel({ CurrentWindowWidth * float(0.75) - 120,24,120,CurrentWindowHeight - 24 }, NULL);
                    gui_state.meshmaterialtoggle.scroll_index = GuiScrollBar({ CurrentWindowWidth * float(0.75) - 16,24,16,CurrentWindowHeight - 24 }, gui_state.meshmaterialtoggle.scroll_index, 0, std::max(0, int(mat_db.size() - gui_state.meshmaterialtoggle.current_ceil_height))); // mat_db size should be devided by the amount of textures displayed.

                    int temp_x = 0;

                    for (auto text_vec_obj : gui_state.meshmaterialtoggle.current_material_list) {
                        //GuiPanel({ CurrentWindowWidth * float(0.75) - 120,float(24 + (104 * temp_x)),104,104 }, NULL);
                        DrawTexturePro(gui_state.meshmaterialtoggle.current_material_list[temp_x].first, texture_to_rec(gui_state.meshmaterialtoggle.current_material_list[temp_x].first), { CurrentWindowWidth * float(0.75) - 120,float(24 + (104 * temp_x)),104,104 }, { 0,0 }, 0, WHITE);
                        
                        if (GuiLabelButton({ CurrentWindowWidth * float(0.75) - 120,float(24 + (104 * temp_x)),104,104 }, NULL)) {
                        //    std::cout << gui_state.meshmaterialtoggle.current_material_list[temp_x].second << "\n";
                            current_mesh_object->set_mesh_material(gui_state.meshmaterialtoggle.current_material_list[temp_x].second, &mat_db);

                            gui_state.meshmaterialtoggle.current_preview = gui_state.meshmaterialtoggle.current_material_list[temp_x].first;
                        }

                        temp_x++;
                    }

                }

                /* TO IMPLEMENT
                gui_state.meshmaterialtoggle.Rotate90ButtonPressed = GuiButton({ CurrentWindowWidth * float(0.9375), 48, CurrentWindowWidth * float(0.0625), 24 }, "R90");
                gui_state.meshmaterialtoggle.MirrorHorButtonPressed = GuiButton({ CurrentWindowWidth * float(0.9375), 96, CurrentWindowWidth * float(0.0625), 24 }, "MRH");
                gui_state.meshmaterialtoggle.MirrorVerticalButtonPressed = GuiButton({ CurrentWindowWidth * float(0.9375), 144, CurrentWindowWidth * float(0.0625), 24 }, "MRV");

                GuiLabel({ CurrentWindowWidth * float(0.9375), 72, 48, 24 }, "Rotate");
                GuiLabel({ CurrentWindowWidth * float(0.9375), 120, 48, 24 }, "Mirror");
                */



            }

            if (gui_state.current_object_state.model_active) {
              //  if (GuiDropdownBox({ 1440, 240, 192, 24 }, NULL, &gui_state.modelshadertoggle.ChooseShaderActive, gui_state.modelshadertoggle.ChooseShaderEditMode)) gui_state.modelshadertoggle.ChooseShaderEditMode = !gui_state.modelshadertoggle.ChooseShaderEditMode;
                //if (GuiDropdownBox({ 1440, 288, 96, 24 }, NULL, &gui_state.modelshadertoggle.ShaderSettingsDropdownBoxActive, gui_state.modelshadertoggle.ShaderSettingsDropdownBoxEditMode)) gui_state.modelshadertoggle.ShaderSettingsDropdownBoxEditMode = !gui_state.modelshadertoggle.ShaderSettingsDropdownBoxEditMode;
                //if (GuiTextBox({ 1536, 288, 96, 24 }, gui_state.modelshadertoggle.ShaderParamText, 128, gui_state.modelshadertoggle.ShaderParamEditMode)) gui_state.modelshadertoggle.ShaderParamEditMode = !gui_state.modelshadertoggle.ShaderParamEditMode;
            }

        }
    }

    if (gui_state.MaterialWindow.material_window_state) {
        gui_state.MaterialWindow.material_window_state = !GuiWindowBox({ 256,40,440,400 }, "Material creation");

        if (!gui_state.MaterialWindow.material_window_state) {
            for (auto to_unload : gui_state.MaterialWindow.vec_mat) {
                to_unload.second = "";
                UnloadTexture(to_unload.first);

                to_unload.first = CreateDefaultTexture();
            }
        }

        GuiPanel({ 262,72,200,200 }, NULL);

        DrawTexturePro(gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first, texture_to_rec(gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first), { 262,72,200,200 }, { 0,0, }, 0, WHITE);

        if (GuiDropdownBox({ 262,272,120,20 }, "Albedo;Metalness;Normal;Roughness;Occlusion;Emission;Heightmap;Cubemap;Irrdaiance;Prefilter;Brdf",&gui_state.MaterialWindow.material_dropdown_index, gui_state.MaterialWindow.material_dropdown_bool)) {
            gui_state.MaterialWindow.material_dropdown_bool = !gui_state.MaterialWindow.material_dropdown_bool;
        }

        if (GuiButton({ 382,272,80,20 }, "Browse")) {
            std::string winname = "Browse a texture";
            std::string folder = std::string(GetWorkingDirectory()) + "\\textures\\";
            const char* filters[] = { "*.png" };
            auto pathfor = tinyfd_openFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Texture (*.png)", 1);

            if (pathfor != NULL) {
                gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first = LoadTexture(pathfor);
                gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].second = (pathfor);

                switch (gui_state.MaterialWindow.material_dropdown_index)
                {
                case 0: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_ALBEDO, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 1: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_METALNESS, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 2: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_NORMAL, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 3: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_ROUGHNESS, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 4: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_OCCLUSION, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 5: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_EMISSION, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 6: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_HEIGHT, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 7: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_CUBEMAP, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 8: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_IRRADIANCE, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 9: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_PREFILTER, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                      break;
                case 10: {
                    SetMaterialTexture(&gui_state.MaterialWindow.mat_create, MATERIAL_MAP_BRDF, gui_state.MaterialWindow.vec_mat[gui_state.MaterialWindow.material_dropdown_index].first);
                }
                       break;
                default:
                    break;
                }
            }

        }

        GuiPanel({ 490,72,200,200 }, NULL);
        
        BeginTextureMode(gui_state.MaterialWindow.material_texture_preview);
        ClearBackground(BLACK);
        BeginMode3D(gui_state.MaterialWindow.preview_camera);

        DrawGrid(100, 10);
        DrawMesh(gui_state.MaterialWindow.std_mesh, gui_state.MaterialWindow.mat_create, MatrixIdentity());

        EndMode3D();
        EndTextureMode();
        

        DrawTexture(gui_state.MaterialWindow.material_texture_preview.texture, 490, 72, WHITE);
        GuiLabel({ 568,56,47,23 }, "Preview");

        if (GuiButton({ 490,292,200,26 }, "Browse shader")) {
            std::string winname = "Browse a shader";
            std::string folder = std::string(GetWorkingDirectory()) + "\\shaders\\";
            const char* filters[] = { "*.fs" };  // Маски файло

            auto pathfor = tinyfd_openFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Fragment shaders (*.fs)", 1);

            if (pathfor != NULL) {

                gui_state.MaterialWindow.mat_create.shader = LoadShader(NULL, pathfor);
                gui_state.MaterialWindow.shader_path = pathfor;

            }
        }
        if (GuiButton({ 626,400,50,30 }, "Save")) {

            fs::path zipath = "materials\\";
            std::string winname = "Save";
            std::string folder = zipath.string();
            const char* filters[] = { "Folder" };  // Маски файлов

            auto pathfor = tinyfd_saveFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Material save (*Folder)");

            if (pathfor != NULL) {

                std::vector<std::string> saving_names = { "ALBEDO.png","METALNESS.png","NORMAL.png","ROUGHNESS.png","OCCLUSION.png","EMISSION.png","HEIGHT.png","CUBEMAP.png","IRRIDIANCE.png","PREFILTER.png","BRDF.png" };

                fs::create_directories(pathfor);

                for (int ind = 0; ind <= 10; ind++) {
                    if (!gui_state.MaterialWindow.vec_mat[ind].second.empty()) { //Если существует.
                        auto forsave = LoadImageFromTexture(gui_state.MaterialWindow.vec_mat[ind].first);
                        auto tosave = pathfor + std::string("//") + saving_names[ind];
                        ExportImage((forsave), (tosave).c_str());
                        UnloadImage(forsave);
                    }

                }

                gui_state.MaterialWindow.preview_camera.position = { 5.0f,0.0f,0.0f };
                BeginTextureMode(gui_state.MaterialWindow.material_texture_preview); //Making the preview
                BeginMode3D(gui_state.MaterialWindow.preview_camera);

                DrawMesh(gui_state.MaterialWindow.std_mesh, gui_state.MaterialWindow.mat_create, MatrixIdentity());

                EndMode3D();
                EndTextureMode();

                auto forsave = LoadImageFromTexture(gui_state.MaterialWindow.material_texture_preview.texture);
                auto tosavefff = (pathfor + std::string("//PREVIEW.png"));

                ExportImage(forsave, tosavefff.c_str());
                UnloadImage(forsave);

                fs::path identyi = pathfor + std::string("\\mat.mati");

                std::ofstream matinfo(identyi.string(), std::ios::binary);

                matinfo.write(reinterpret_cast<char*>(&gui_state.MaterialWindow.mat_create.maps->value), sizeof(gui_state.MaterialWindow.mat_create.maps->value)); //Сохраняем два!

                if (!gui_state.MaterialWindow.shader_path.empty()) {


                    short int shader_iden = 1;
                    matinfo.write(reinterpret_cast<char*>(&shader_iden), sizeof(shader_iden)); //Сохраняем тот факт что шейдера есть.

                    size_t pathsize = gui_state.MaterialWindow.shader_path.size();
                    matinfo.write(reinterpret_cast<char*>(&pathsize), sizeof(pathsize)); //Сохраняем раз!
                    matinfo.write(gui_state.MaterialWindow.shader_path.c_str(), pathsize);
                }
                else {
                    short int shader_iden = -1;

                    matinfo.write(reinterpret_cast<char*>(&shader_iden), sizeof(shader_iden)); //Сохраняем тот факт что шейдера нет.
                }

                matinfo.close();

                gui_state.MaterialWindow.preview_camera.position = { 6,6,6 };
            }
        }

        if (GuiDropdownBox({ 490,272,120,20 }, "Repeat;Clamp;Mirror repeat;Mirror clamp", &gui_state.MaterialWindow.material_chosen_wrap, gui_state.MaterialWindow.material_wrap_bool)) {
            gui_state.MaterialWindow.material_wrap_bool = !gui_state.MaterialWindow.material_wrap_bool;
            if (!gui_state.MaterialWindow.material_wrap_bool) {
                switch (gui_state.MaterialWindow.material_chosen_wrap)
                {
                case(0): {
                    gui_state.MaterialWindow.mat_create.maps->value = TEXTURE_WRAP_REPEAT;


                }break;
                case(1): {

                    gui_state.MaterialWindow.mat_create.maps->value = TEXTURE_WRAP_CLAMP;


                }break;
                case(2): {

                    gui_state.MaterialWindow.mat_create.maps->value = TEXTURE_WRAP_MIRROR_REPEAT;


                }break;
                case(3): {

                    gui_state.MaterialWindow.mat_create.maps->value = TEXTURE_WRAP_MIRROR_CLAMP;


                }break;
                default:
                    break;
                }
            }
        }
    }

    GuiLock();

    EndDrawing();

}

void manageRenderTexutre(RenderTexture& render) {
    if (IsRenderTextureValid(render)) {
        UnloadRenderTexture(render);
    }
    render = LoadRenderTexture(int(CurrentWindowWidth*0.75f-(24)), CurrentWindowHeight-24);
}

void DrawModelPro(Model modelin, Matrix matrixin) {

    rlPushMatrix();

    rlMultMatrixf(MatrixToFloat(matrixin));
    DrawModel(modelin, { 0,0,0 }, { 1.0 }, WHITE);

    rlPopMatrix();

}

void renderWorld(RenderTexture& render, BlenderCamera& in_camera) {

    static bool mouse_lock_state = false;

    //Camera work
   
    //BRAND NEW IMPLEMENTATION OF CAMERA
    if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) {
        mouse_lock_state = true;

        DisableCursor();        
    }

    if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) && mouse_lock_state) {
        
        BlenderCameraUpdate(&in_camera);

    }
    else if (IsMouseButtonReleased(MOUSE_MIDDLE_BUTTON)) {
        mouse_lock_state = false;
        EnableCursor();
    }

    //Camera work ENDs here

    //Rendering is here!

    BeginTextureMode(render);

    //Fix for Vertical mirror.

    ClearBackground(BLACK);

    BeginMode3D(in_camera.camera);

    DrawGrid(50, 1.0f);

    //First, Draw grid. Then, all of the objects.
        for (mesh_object mesh_object_to_draw : obj_db.get_mesh_vector()) {
            DrawMesh(mesh_object_to_draw.get_mesh_model(), mesh_object_to_draw.get_mesh_material(), mesh_object_to_draw.get_object_matrix());
        }
        for (model_object model_object_to_draw : obj_db.get_model_vector()) {
            DrawModelPro(model_object_to_draw.get_model().model_mdl, model_object_to_draw.get_object_matrix());
        }

    EndMode3D();

    EndTextureMode();
}

void LoadMaterialPreviews(GUIState& gui_states, material_database& mat_db, bool to_unload) {
    if (to_unload) {
        for (auto& material : gui_states.meshmaterialtoggle.current_material_list) {
            UnloadTexture(material.first);
        }
        gui_states.meshmaterialtoggle.current_material_list.clear();
    }

    int start_index = gui_states.meshmaterialtoggle.scroll_index;
    int end_index = start_index + gui_states.meshmaterialtoggle.current_ceil_height;

    if (end_index > mat_db.get_material_show_vector().size()) {
        end_index = mat_db.get_material_show_vector().size();
    }

    for (int x = start_index; x < end_index; x++) {
        std::string temp_path = mat_db.get_material_show_vector()[x].mat_path + "\\PREVIEW.PNG";
        if (FileExists(temp_path.c_str())) {
            Texture2D preview_texture = LoadTexture(temp_path.c_str());
            gui_states.meshmaterialtoggle.current_material_list.push_back({ preview_texture, mat_db.get_material_show_vector()[x].mat_path });
        }
        else {
            gui_states.meshmaterialtoggle.current_material_list.push_back({ mat_db.get_default_texture(), mat_db.get_material_show_vector()[x].mat_path });
        }
    }
}

void manage_control(GUIState* gui_state_in) {
    
    if (!gui_state_in->current_object_state.disabled) {
        if (IsKeyPressed(KEY_DELETE) && !gui_state_in->current_object_state.disabled) {
            obj_db.remove_object(obj_db.get_entry_from_index(gui_state_in->objects.listActive));
            gui_state_in->objects.listActive--;
        }
        if (IsKeyPressed(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D)) {

            auto temp_entry = obj_db.get_entry_from_index(gui_state_in->objects.listActive);

            obj_db.duplicate_object(obj_db.get_entry_from_index(gui_state_in->objects.listActive));
            gui_state_in->objects.listActive = obj_db.get_size() - 1;

            if (temp_entry.type == OBJECT_MESH) {
                mesh_object* temp_mesh = obj_db.get_mesh_object(obj_db.get_entry_from_index(gui_state_in->objects.listActive));
                temp_mesh->set_mesh_material(temp_mesh->get_mesh_material_path(), &mat_db); //Reload the material!
            }

        }

        if (IsKeyDown(KEY_Z)) { //Work with XYZ. This one is for Z
            if (IsKeyDown(KEY_LEFT_SHIFT)) { //Scale
                if (GetMouseWheelMove() != 0) {
                    current_object->add_scale({ 0,0, float(GetMouseWheelMove() * (5 * KEYBOARD_MANIPULATION_ACC)) });
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_object->add_scale({ 0,0, float(10 * KEYBOARD_MANIPULATION_ACC) });
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    current_object->add_scale({ 0,0, -1 * float(10 * KEYBOARD_MANIPULATION_ACC) });
                }
                if (IsKeyPressed(KEY_ZERO)) {
                    current_object->set_scale(0, MATRIX_CHANGE_Z);
                }
            }
            else if (IsKeyDown(KEY_LEFT_CONTROL)) { //Angles
                if (GetMouseWheelMove() != 0) {
                    current_object->add_angle({ 0,0, float(GetMouseWheelMove() * KEYBOARD_MANIPULATION_ACC) });
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_object->add_angle({ 0,0, float(10 * KEYBOARD_MANIPULATION_ACC) });
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    current_object->add_angle({ 0,0, -1 * float(10 * KEYBOARD_MANIPULATION_ACC) });
                }
                if (IsKeyPressed(KEY_ZERO)) {
                    current_object->set_angle(0, MATRIX_CHANGE_Z);
                }
            }
            else { //Position
                if (GetMouseWheelMove() != 0) {
                    current_object->add_position({ 0,0, float(GetMouseWheelMove() * KEYBOARD_MANIPULATION_ACC) });
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_object->add_position({ 0,0, float(10 * KEYBOARD_MANIPULATION_ACC) });
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    current_object->add_position({ 0,0, -1 * float(10 * KEYBOARD_MANIPULATION_ACC) });
                }
                if (IsKeyPressed(KEY_ZERO)) {
                    current_object->set_position(0, MATRIX_CHANGE_Z);
                }
            }
        }
        if (IsKeyDown(KEY_X)) { //Work with XYZ. This one is for Z
            if (IsKeyDown(KEY_LEFT_SHIFT)) { //Scale
                if (GetMouseWheelMove() != 0) {
                    current_object->add_scale({ float(GetMouseWheelMove() * KEYBOARD_MANIPULATION_ACC),0,0 });
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_object->add_scale({ float(10 * KEYBOARD_MANIPULATION_ACC),0,0 });
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    current_object->add_scale({ -1 * float(10 * KEYBOARD_MANIPULATION_ACC),0,0 });
                }
                if (IsKeyPressed(KEY_ZERO)) {
                    current_object->set_scale(0, MATRIX_CHANGE_X);
                }
            }
            else if (IsKeyDown(KEY_LEFT_CONTROL)) { //Angles
                if (GetMouseWheelMove() != 0) {
                    current_object->add_angle({ float(GetMouseWheelMove() * KEYBOARD_MANIPULATION_ACC),0,0 });
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_object->add_angle({ float(10 * KEYBOARD_MANIPULATION_ACC),0,0 });
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    current_object->add_angle({ -1 * float(10 * KEYBOARD_MANIPULATION_ACC),0,0 });
                }
                if (IsKeyPressed(KEY_ZERO)) {
                    current_object->set_angle(0, MATRIX_CHANGE_X);
                }
            }
            else { //Position
                if (GetMouseWheelMove() != 0) {
                    current_object->add_position({ float(GetMouseWheelMove() * KEYBOARD_MANIPULATION_ACC),0,0 });
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_object->add_position({ float(10 * KEYBOARD_MANIPULATION_ACC),0,0 });
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    current_object->add_position({ -1 * float(10 * KEYBOARD_MANIPULATION_ACC),0,0 });
                }
                if (IsKeyPressed(KEY_ZERO)) {
                    current_object->set_position(0, MATRIX_CHANGE_X);
                }
            }
        }
        if (IsKeyDown(KEY_C)) { //Work with XYZ. This one is for Z
            if (IsKeyDown(KEY_LEFT_SHIFT)) { //Scale
                if (GetMouseWheelMove() != 0) {
                    current_object->add_scale({ 0,float(GetMouseWheelMove() * KEYBOARD_MANIPULATION_ACC),0 });
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_object->add_scale({ 0,float(10 * KEYBOARD_MANIPULATION_ACC),0 });
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    current_object->add_scale({ 0,-1 * float(10 * KEYBOARD_MANIPULATION_ACC),0 });
                }
                if (IsKeyPressed(KEY_ZERO)) {
                    current_object->set_scale(0, MATRIX_CHANGE_Y);
                }
            }
            else if (IsKeyDown(KEY_LEFT_CONTROL)) { //Angles
                if (GetMouseWheelMove() != 0) {
                    current_object->add_angle({ 0,float(GetMouseWheelMove() * KEYBOARD_MANIPULATION_ACC),0 });
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_object->add_angle({ 0, float(10 * KEYBOARD_MANIPULATION_ACC),0 });
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    current_object->add_angle({ 0, -1 * float(10 * KEYBOARD_MANIPULATION_ACC),0 });
                }
                if (IsKeyPressed(KEY_ZERO)) {
                    current_object->set_scale(0, MATRIX_CHANGE_Y);
                }
            }
            else { //Position
                if (GetMouseWheelMove() != 0) {
                    current_object->add_position({ 0,float(GetMouseWheelMove() * KEYBOARD_MANIPULATION_ACC),0 });
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_object->add_position({ 0,float(10 * KEYBOARD_MANIPULATION_ACC),0 });
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    current_object->add_position({ 0,-1 * float(10 * KEYBOARD_MANIPULATION_ACC),0 });
                }
                if (IsKeyPressed(KEY_ZERO)) {
                    current_object->set_position(0, MATRIX_CHANGE_Y);
                }
            }
        }    
    
}

}

void manage_gui_state(GUIState* gui_state_in) {

    if (gui_state_in->tools.meshToolActive) {

        obj_db.add_mesh_object(GenMeshCube(STANDART_MESH_SIZE, STANDART_MESH_SIZE, STANDART_MESH_SIZE));

        gui_state_in->objects.listActive = obj_db.get_size() - 1;
    }
    if (gui_state_in->tools.modelToolActive) { //Add implementations.
        std::string winname = "Browse a model : Choose from this directory";
        std::string folder = std::string(GetWorkingDirectory()) + "\\resources\\models\\";

        const char* filters[] = { "*.obj" };  // 

        auto pathfor = tinyfd_openFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Texture (*.png)", 1);
        //ADD A CHECK IF ITS IN THE RECOURCES TAB
        if (pathfor != NULL) {
            obj_db.add_model_object(pathfor);
        }
    }

    if (gui_state_in->tools.entityToolActive) {//ADD
        //obj_db.add_mesh_object(basic_mesh_object);
        //gui_states.objects.listScrollIndex;
    }

    if (gui_state_in->meshmaterialtoggle.scroll_index != gui_state_in->meshmaterialtoggle.previous_scroll_index) { //Manage scrolling the material list
        LoadMaterialPreviews(*gui_state_in, mat_db, true);
        gui_state_in->meshmaterialtoggle.previous_scroll_index = gui_state_in->meshmaterialtoggle.scroll_index;
    }

    auto entry_object_for_type = obj_db.get_entry_from_index(gui_state_in->objects.listActive);

    if (gui_state_in->objects.listActive != gui_state_in->objects.previous_ListActive) {

        current_object = obj_db.get_base_object(entry_object_for_type); //Get a new one.

        gui_state_in->objects.previous_ListActive = gui_state_in->objects.listActive;

        //Manage types of objects!
        if (true) {
            gui_state_in->objects.previous_type = entry_object_for_type.type;

            switch (entry_object_for_type.type) {
            case OBJECT_MESH: {
                mesh_object* temp_obj = obj_db.get_mesh_object(entry_object_for_type);

                gui_state_in->objects.GuiToggle1Text = "Object";
                gui_state_in->objects.GuiToggle2Text = "Mesh";
                gui_state_in->objects.GuiToggle3Text = "Logic";
                gui_state_in->objects.GuiToggle4Text = "Material";

                gui_state_in->current_object_state.disabled = false;
                gui_state_in->current_object_state.entity_active = false;
                gui_state_in->current_object_state.mesh_active = true;
                gui_state_in->current_object_state.model_active = false;

                for (int i = 0; i < 4; i++) { //Set them all to false.
                    gui_state_in->objects.previousStates[i] = false; //Setting all of them to false IF empty.
                    gui_state_in->objects.toggles[i] = false; //Setting all of them to false IF empty.
                }

                gui_state_in->objects.toggles[0] = true;

                UnloadTexture(gui_state_in->meshmaterialtoggle.current_preview); //Fixed memory leak.
                gui_state_in->meshmaterialtoggle.current_preview = mat_db.get_material_preview(temp_obj->get_mesh_material_path());


            }
                            break;
            case OBJECT_MODEL:
            {
                current_object = obj_db.get_base_object(obj_db.get_entry_from_index(gui_state_in->objects.listActive));

                gui_state_in->objects.GuiToggle1Text = "Object";
                gui_state_in->objects.GuiToggle2Text = "Collision";
                gui_state_in->objects.GuiToggle3Text = "Logic";
                gui_state_in->objects.GuiToggle4Text = "";

                gui_state_in->current_object_state.disabled = false;
                gui_state_in->current_object_state.entity_active = false;
                gui_state_in->current_object_state.mesh_active = false;
                gui_state_in->current_object_state.model_active = true;

                for (int i = 0; i < 4; i++) { //Set them all to false.
                    gui_state_in->objects.previousStates[i] = false; //Setting all of them to false IF empty.
                    gui_state_in->objects.toggles[i] = false; //Setting all of them to false IF empty.
                }

                gui_state_in->objects.toggles[0] = true;
            }
            break;
            default:
            {
                gui_state_in->objects.GuiToggle1Text = "";
                gui_state_in->objects.GuiToggle2Text = "";
                gui_state_in->objects.GuiToggle3Text = "";
                gui_state_in->objects.GuiToggle4Text = "";

                gui_state_in->current_object_state.disabled = true;
                gui_state_in->current_object_state.entity_active = false;
                gui_state_in->current_object_state.mesh_active = false;
                gui_state_in->current_object_state.model_active = false;

                for (int i = 0; i < 4; i++) { //Set them all to false.
                    gui_state_in->objects.previousStates[i] = false; //Setting all of them to false IF empty.
                    gui_state_in->objects.toggles[i] = false; //Setting all of them to false IF empty.
                }

            }
            break;
            }


        }



    }

    //Manage dropdowns

    if (gui_state_in->dropdowns.file.active == 1) { //IT means save
        gui_state_in->dropdowns.file.active = 0; //change back.

        std::string winname = "Save map";
        std::string folder = std::string(GetWorkingDirectory()) + "\\saves\\";
        const char* filters[] = { "*.zip" };

        auto save_path = tinyfd_saveFileDialog(winname.c_str(), folder.c_str(), 1, filters, "ZIP Map save (*.zip)");

        if (save_path != NULL) { //IF not aborted <- MOVE TO ODJ_DB
            obj_db.save(save_path);
        }

    }

    if (gui_state_in->dropdowns.file.active == 2) {
        gui_state_in->dropdowns.file.active = 0;

        std::string winname = "Browse a map.zip";
        std::string folder = std::string(GetWorkingDirectory()) + "\\saves\\";

        const char* filters[] = { "*.zip" }; 

        auto load_path = tinyfd_openFileDialog(winname.c_str(), folder.c_str(), 1, filters, "Map (*.zip)", 1);

        if (load_path != NULL) {
            obj_db.load(load_path);
        }
            /*
            std::fstream file_load(load_path);
            if (file_load.is_open()) {
                json json_to_load;
                try {
                    json_to_load = json::parse(file_load);
                }
                catch (const json::parse_error& e) {
                    std::cout << "FISHTANK: ERROR: Error loading the JSON! \n";
                    exit;
                }

                obj_db.json_deserialize_db(json_to_load);

            }
            */
    }

    if (gui_state_in->dropdowns.file.active == 3) {
        gui_state_in->dropdowns.file.active = 0;
        gui_state_in->credit.CreditsWindowActive = true;
    }

    if (gui_state_in->dropdowns.file.active == 4) {
        bool exit_signal = true;
    }

    if (gui_state_in->dropdowns.material.active == 1) {
        gui_state_in->dropdowns.material.active = 0;
        gui_state_in->MaterialWindow.material_window_state = true;
    }
}


int main() {    
    SetTargetFPS(30);

    GUIState main_gui_state;

    init(main_gui_state);

    ClearWindowState(FLAG_WINDOW_UNDECORATED);
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(1280, 720, WINDOW_NAME);

    //doesnt work in INIT
    main_gui_state.MaterialWindow.std_mesh = GenMeshCube(5, 5, 5);
    main_gui_state.MaterialWindow.material_texture_preview = LoadRenderTexture(200, 200);
    main_gui_state.MaterialWindow.mat_create = LoadMaterialDefault();

    for (int ind = 0; main_gui_state.MaterialWindow.vec_mat.size() < 11; ind++) {
        main_gui_state.MaterialWindow.vec_mat.push_back({ CreateDefaultTexture(), "" });
    }

    SetWindowMinSize(MINIMUM_RESOLUTION_WIDTH, MINIMUM_RESOLUTION_HEIGHT);
    SetWindowMaxSize(MAXIMUM_RESOLUTION_WIDTH, MAXIMUM_RESOLUTION_HEIGHT);

    RenderTexture world_texture;

    manageRenderTexutre(world_texture);

    BlenderCamera main_camera = CreateBlenderCamera(); //Issue. Camera goes wild when pressing RMB
    
    LoadMaterialPreviews(main_gui_state, mat_db, false);

    while (!exit_signal) {
        //Manage Window things
        manage_control(&main_gui_state);
        
        if ((CurrentWindowHeight != GetRenderHeight()) || (CurrentWindowWidth != GetRenderWidth())) {
                // std::cout << "ScreenChange";
                CurrentWindowWidth = GetRenderWidth();
                CurrentWindowHeight = GetRenderHeight();

                manageRenderTexutre(world_texture);
        
                main_gui_state.meshmaterialtoggle.current_ceil_height = ceil((CurrentWindowHeight - 24) / 104);

                LoadMaterialPreviews(main_gui_state, mat_db, true);

                //Manage material vector
        }

        current_object = obj_db.get_base_object(obj_db.get_entry_from_index(main_gui_state.objects.listActive)); //Update current object.

        manage_gui_state(&main_gui_state);

        renderWorld(world_texture, main_camera); //Render world

        draw_gui_and_world(main_gui_state, world_texture); //Render GUI

        if (WindowShouldClose()) { //IF about to close DIE
            exit_signal = true; 
        }


    }

}

