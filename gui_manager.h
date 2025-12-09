#pragma once

#include "Bait.h"
#include "gui_state_manager.h"

#include "rcamera_blender.h" //https://github.com/grplyler/raylib-blender-camera

#include "objects_database.h"

#include "raygui.h"

class gui_manager
{
private:
    RenderTexture* world_render = nullptr;
    State* gui_state = nullptr;
    objects_database* gui_obj_db = nullptr;

    float currentWindowWidth = 0;
    float currentWindowHeight = 0;

public:
    gui_manager(State* state_in, RenderTexture* render_in, objects_database* obj_db_in);
        
    void update_window_size();

    void draw_editor_interface();

    void draw_main_layout();
    
    void draw_world_view();
    
    void draw_tool_panel();

    void draw_object_list();

    void draw_drop_downs();

    void draw_object_properties();
};

