#pragma once
#include "raylib.h";

float dtr(float degrees) { //Градусы в радианы.
	return((degrees / PI) * 180.0f);
}
float rtd(float radians) { //Радианы в градусы.
	return((radians / 180.0f) * PI);

}