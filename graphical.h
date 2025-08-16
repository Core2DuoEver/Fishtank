#pragma once

#include "raylib.h"
#include "rlgl.h"

void DrawModelPro(Model modelin, Matrix matrixin) {

	rlPushMatrix();

	rlMultMatrixf(MatrixToFloat(matrixin));
	DrawModel(modelin, { 0,0,0 }, { 1.0 }, WHITE);

	rlPopMatrix();

}

void SetColor(int textColor)
{
    std::cout << "\033[" << textColor << "m";
}

// Function to reset the console color
void ResetColor() { std::cout << "\033[0m"; }


Vector3 TransformNormal(Vector3 normal, Matrix transform) {
    // 1. Извлекаем 3x3 часть матрицы (игнорируем перевод)
    Matrix normalMatrix = MatrixTranspose(MatrixInvert(transform));

    // 2. Умножаем нормаль на матрицу
    Vector3 result;
    result.x = normal.x * normalMatrix.m0 + normal.y * normalMatrix.m1 + normal.z * normalMatrix.m2;
    result.y = normal.x * normalMatrix.m4 + normal.y * normalMatrix.m5 + normal.z * normalMatrix.m6;
    result.z = normal.x * normalMatrix.m8 + normal.y * normalMatrix.m9 + normal.z * normalMatrix.m10;

    // 3. Нормализуем результат
    return Vector3Normalize(result);
}