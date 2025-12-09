#pragma once

#include "string";
#include "raylib.h"

struct State {
    struct ObjectPanel { //Manages objects.
        bool previousStates[4];
        bool toggles[4] = { false, false, false, false };

        int lastActiveToggle = 0;

        int listScrollIndex = 0;
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
        bool MELabelPressed = false;            // LabelButton: MELabel
        bool GithubLabelButtonPressed = false;            // LabelButton: GithubLabelButton
        bool WindowBox079Active = true;            // WindowBox: WindowBox079
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
        bool disabled = false;
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

    float currentWindowWidth = 0;
    float currentWindowHeight = 0;

    std::string object_list_string = "";

    RenderTexture* currentWorldTexture = nullptr;

    bool helpButtonPressed = false;
    bool CreditsWindowActive = true;            // WindowBox: CreditsWindow

};

class gui_state_manager
{
    State current_state;

};

