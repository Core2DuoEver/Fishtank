#pragma once
#include "raylib.h";

float dtr(float degrees) { //������� � �������.
	return((degrees / PI) * 180.0f);
}
float rtd(float radians) { //������� � �������.
	return((radians / 180.0f) * PI);

}