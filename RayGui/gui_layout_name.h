/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_LAYOUT_NAME_IMPLEMENTATION
*       #include "gui_layout_name.h"
*
*       INIT: GuiLayoutNameState state = InitGuiLayoutName();
*       DRAW: GuiLayoutName(&state);
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

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_LAYOUT_NAME_H
#define GUI_LAYOUT_NAME_H

typedef struct {
    bool WindowBox000Active;
    bool DropdownBox002EditMode;
    int DropdownBox002Active;
    int ListView006ScrollIndex;
    int ListView006Active;

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiLayoutNameState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiLayoutNameState InitGuiLayoutName(void);
void GuiLayoutName(GuiLayoutNameState *state);
static void Button007();
static void Button008();
static void Button009();

#ifdef __cplusplus
}
#endif

#endif // GUI_LAYOUT_NAME_H

/***********************************************************************************
*
*   GUI_LAYOUT_NAME IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_LAYOUT_NAME_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiLayoutNameState InitGuiLayoutName(void)
{
    GuiLayoutNameState state = { 0 };

    state.WindowBox000Active = true;
    state.DropdownBox002EditMode = false;
    state.DropdownBox002Active = 0;
    state.ListView006ScrollIndex = 0;
    state.ListView006Active = 0;

    // Custom variables initialization

    return state;
}
static void Button007()
{
    // TODO: Implement control logic
}
static void Button008()
{
    // TODO: Implement control logic
}
static void Button009()
{
    // TODO: Implement control logic
}


void GuiLayoutName(GuiLayoutNameState *state)
{
    if (state->DropdownBox002EditMode) GuiLock();

    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox((Rectangle){ 88, 96, 1416, 736 }, "Fishtank");
        GuiPanel((Rectangle){ 352, 152, 888, 632 }, NULL);
        GuiLine((Rectangle){ 88, 784, 1416, 12 }, NULL);
        if (GuiButton((Rectangle){ 104, 800, 72, 24 }, "MESH")) Button007(); 
        if (GuiButton((Rectangle){ 272, 800, 80, 24 }, "ENTITY")) Button008(); 
        if (GuiButton((Rectangle){ 184, 800, 80, 24 }, "MODEL")) Button009(); 
    }
    GuiGroupBox((Rectangle){ 96, 152, 248, 632 }, "Objects");
    GuiGroupBox((Rectangle){ 1248, 152, 248, 632 }, "Details");
    GuiListView((Rectangle){ 104, 160, 232, 616 }, NULL, &state->ListView006ScrollIndex, &state->ListView006Active);
    if (GuiDropdownBox((Rectangle){ 88, 160, 104, 24 }, "File", &state->DropdownBox002Active, state->DropdownBox002EditMode)) state->DropdownBox002EditMode = !state->DropdownBox002EditMode;
    
    GuiUnlock();
}

#endif // GUI_LAYOUT_NAME_IMPLEMENTATION
