#pragma once



//Standart libs

#include <cstdlib>; 
#include <string>;
#include <cstring>
#include <iostream>;
#include <vector>;
#include <string>;
#include <fstream>;

//Open-source libs
#include "zip.h"; // BSD License
#include "tinyfiledialogs/tinyfiledialogs.h"; //Zlib
#include "boost/filesystem.hpp" //Boost license

//Raysan libs.

#include "raylib.h"; //Main Graphic lib - Zlib
#include "raymath.h"; //Needed for Matrices math
#include "rlgl.h";  //Needed for additional low-level OpenGL work.

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"; //Main gui lib.

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
//On initial launch OR entry vipe
#define EMPTY_GUI_LIST "No entry"

#define STANDART_MESH_NAME "Mesh"
#define STANDART_MODEL_NAME "Model"