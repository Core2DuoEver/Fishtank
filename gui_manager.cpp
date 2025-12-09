#include "gui_manager.h"

gui_manager::gui_manager(State* state_in, RenderTexture* render_in, objects_database* obj_db_in) {
	gui_state = state_in;
	world_render = render_in;
	gui_obj_db = obj_db_in;


	update_window_size();
}

void gui_manager::draw_editor_interface() {

	BeginDrawing();

	ClearBackground(WHITE);

	draw_main_layout();

	draw_object_list();

	draw_world_view();
	draw_tool_panel();
	draw_drop_downs();

	if (!gui_state->current_object_state.disabled) {
		draw_object_properties();
	}

	EndDrawing();

}

void gui_manager::update_window_size() {
	currentWindowWidth = GetRenderWidth();
	currentWindowHeight = GetRenderHeight();
}

void gui_manager::draw_main_layout() {
	GuiPanel({ 0, 0, currentWindowWidth, currentWindowHeight }, NULL); //Panel BG main
	GuiPanel({ 0, 0, currentWindowWidth, 24 }, NULL); //Panel tools dropdowns
	GuiPanel({ currentWindowWidth * float(0.75), 0, currentWindowWidth - currentWindowWidth * float(0.75), 24 }, NULL); //Decorative panel over RUN and ?
	GuiPanel({ currentWindowWidth * float(0.75), 24, currentWindowWidth - currentWindowWidth * float(0.75), 192 }, NULL); //Decorative panel over obejct buttons
	GuiPanel({ 0, 24, 24, currentWindowHeight }, NULL); //Tools panel
	GuiPanel({ currentWindowWidth * float(0.75), 216, 24, 216 }, NULL); //Object list panel
	GuiPanel({ currentWindowWidth * float(0.75), 216, currentWindowWidth * float(0.875) - currentWindowWidth * float(0.75), 24 }, NULL); //Objects label BG
}

void gui_manager::draw_object_list() {

}

