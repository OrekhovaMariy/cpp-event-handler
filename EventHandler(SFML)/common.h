#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Brezenhem.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

struct Size {
    float width = 0.;
    float height = 0.;
};

struct Point {
    float x = 0.;
    float y = 0.;
};

// Проверяет, содержится ли заданная точка в прямоугольнике, обозначенным максимальными и минимальными значениями
inline bool IsPointInRestangle(Point p, float max_x, float min_x, float max_y, float min_y) {
    if (p.x < min_x || p.x>max_x || p.y<min_y || p.y > max_y) {
        return false;
    }
    return true;
}

// Проверяет, содержится ли заданная фигура в прямоугольнике, обозначенным максимальными и минимальными значениями
inline bool IsShapeInRestangle(float** a, float max_x, float min_x, float max_y, float min_y) {
    if (IsPointInRestangle({ a[0][0], a[0][1] }, max_x, min_x, max_y, min_y)
        && IsPointInRestangle({ a[1][0], a[1][1] }, max_x, min_x, max_y, min_y)
        && IsPointInRestangle({ a[3][0], a[3][1] }, max_x, min_x, max_y, min_y)
        && IsPointInRestangle({ a[2][0], a[2][1] }, max_x, min_x, max_y, min_y)) {
        return true;
    }
    else {
        return false;
    }
}

// Поворот четырехугольника относительно заданной точки вращения
void RotationPositionOfElement(float** a, float x_pivot, float y_pivot, float angle) {
    //вращение многоугольника a, заданного координатами n вершин 
    //относительно точки x_pivot, y_pivot на заданный в градусах угол angle
    const double g2r = M_PI / 180.;
    angle *= static_cast<float>(g2r);
    for (int i = 0; i < 4; i++) {
        float x_shifted = a[i][0] - x_pivot;
        float y_shifted = a[i][1] - y_pivot;
        a[i][0] = x_pivot + (x_shifted * cos(angle) - y_shifted * sin(angle));
        a[i][1] = y_pivot + (x_shifted * sin(angle) + y_shifted * cos(angle));
    }
}

// Создаем массив вершин многоугольника
float** CreatePositionOfTop(float max_x, float min_x, float max_y, float min_y) {
    float** a;
    a = new float* [4];
    for (int i = 0; i < 4; i++)
    {
        a[i] = new float[2];
    }
    a[0][0] = min_x;
    a[0][1] = min_y;
    a[1][0] = max_x;
    a[1][1] = min_y;
    a[2][0] = max_x;
    a[2][1] = max_y;
    a[3][0] = min_x;
    a[3][1] = max_y;

    return a;
}
