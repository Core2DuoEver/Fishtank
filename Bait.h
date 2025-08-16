#pragma once

//�������� ����������.

#include "raylib.h"; //����� ��� ����������� ������� Zlib
#include "raymath.h"; //����� ��� �������������� �������.
#include "rlgl.h"; //�������������� �����


#define RAYGUI_IMPLEMENTATION
#include "raygui.h"; //����� ��� ������������ ����������. 

//����

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

//��������

//���������� 

extern int screenWidth = 1280;
extern int screenHeight = 720;

extern std::string window_name = "Fishtank";

extern Texture default_texture; 

extern float mesh_toc = 0.1;