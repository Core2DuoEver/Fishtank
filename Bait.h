#pragma once

//Standart libs

#include <cstdlib>

#include <string>

#include <cstring>

#include <iostream>

#include <vector>

#include <fstream>

#include <algorithm>

#include <future>

#include <regex>

//Raysan libs.

#include "raylib.h"//Main Graphic lib - Zlib
#include "raymath.h"; //Needed for Matrices math
#include "rlgl.h";  //Needed for additional low-level OpenGL work.

//Open-source libs
#include "zip.h"; // BSD License
#include "tinyfiledialogs/tinyfiledialogs.h"; //Zlib
#include "boost/filesystem.hpp" //Boost license
#include "nlohmann/json.hpp"

using json = nlohmann::json;
namespace fs = boost::filesystem;

//define's

#define STANDART_RESOLUTION_WIDTH 1280
#define STANDART_RESOLUTION_HEIGHT 720

#define MINIMUM_RESOLUTION_WIDTH 640
#define MINIMUM_RESOLUTION_HEIGHT 480

#define MAXIMUM_RESOLUTION_WIDTH 7680
#define MAXIMUM_RESOLUTION_HEIGHT 4320

#define WINDOW_NAME "Fishtank"

#define TARGET_FPS 60

#define STANDART_MESH_SIZE 1 //Applies to all of XYZ so scale would be one to one.

#define STANDART_MESH_PLANE_RES 1 //Applies to the polygons made for the plane. 

#define SPLASH_ART_TEXTSIZE 7
#define SPLASH_ART_BORDERSIZE 12 
//It's 6 initially, but, from elements is 12
//On initial launch OR entry vipe
#define EMPTY_GUI_LIST ""

#define STANDART_MESH_NAME "Mesh"
#define STANDART_MODEL_NAME "Model"


#define DEFAULT_TEXTURE_HEIGHT 256
#define DEFAULT_TEXTURE_WIDTH 256
#define DEFAULT_TEXTURE_SIZE_CHECKERS 16
#define DEFAULT_TEXTURE_COLOR_BG {0,0,0,255}
#define DEFAULT_TEXTURE_COLOR_CHECKERS {255,0,255,255}

#define KEYBOARD_MANIPULATION_ACC 0.1

#define MAP_SAVE_JSON_NAME "map_data.json"

//Enums

enum matrix_change_index {
	MATRIX_CHANGE_X, MATRIX_CHANGE_Y, MATRIX_CHANGE_Z
};
enum object_types {
	OBJECT_DISABLED = 0, OBJECT_MESH = 1, OBJECT_MODEL = 2
};
enum mesh_types {
	mesh_poly, mesh_plane, mesh_cube, mesh_sphere, mesh_hemisphere, mesh_cylinder, mesh_cone, mesh_torus, mesh_knot, mesh_heightmap, mesh_cubicmap
};
