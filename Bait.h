#pragma once

//Основные библиотеки.

#include "raylib.h"; //Нужна для отображения графики Zlib
#include "raymath.h"; //Нужна для преобразований матрицы.
#include "rlgl.h"; //НИзкоуровневая хуйня


#define RAYGUI_IMPLEMENTATION
#include "raygui.h"; //Нужна для графического интерфейса. 

//Допы

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

//Писанина

//Переменные 

extern int screenWidth = 1280;
extern int screenHeight = 720;

extern std::string window_name = "Fishtank";

extern Texture default_texture; 

extern float mesh_toc = 0.1;