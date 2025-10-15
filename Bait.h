#pragma once

//Raysan libs.

#include "raylib.h"; //Main Graphic lib - Zlib
#include "raymath.h"; //Needed for Matrices math
#include "rlgl.h";  //Needed for additional low-level OpenGL work.

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"; //Main gui lib.

//Standart libs

#include <cstdlib>; 
#include <string>;
#include <cstring>
#include <iostream>;
#include <vector>;
#include <string>;
#include <fstream>;
#include "zip.h"; // BSD License
#include "tinyfiledialogs/tinyfiledialogs.h"; //Zlib
#include "boost/filesystem.hpp" //Boost license

namespace fs = boost::filesystem;

//define's

#define standart_screen_width 1280
#define standart_screen_height 720

#define minimal_resolution_width 640
#define minimal_resolution_height 480

#define maximum_resolution_width 7680
#define maximum_resolution_height 4320

#define window_name "Fishtank"

#define target_fps 60