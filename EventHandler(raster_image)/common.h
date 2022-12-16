#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Brezenhem.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

struct Size {
    int width = 0;
    int height = 0;
};

struct Point {
    int x = 0;
    int y = 0;
};

// Проверяет, содержится ли заданная точка в прямоугольнике, обозначенным максимальными и минимальными значениями
inline bool IsPointInRestangle(Point p, int max_x, int min_x, int max_y, int min_y) {
    if (p.x < min_x || p.x>max_x || p.y<min_y || p.y > max_y) {
        return false;
    }
    return true;
}

// Поворот четырехугольника относительно заданной точки вращения
void RotationPositionOfElement(int **a, int x_pivot, int y_pivot, double angle) {
    //вращение многоугольника a, заданного координатами n вершин 
    //относительно точки x_pivot, y_pivot на заданный в градусах угол angle
    const double g2r = M_PI / 180.;
    angle *= g2r;
    for (int i = 0; i < 4; i++) {
        double x_shifted = a[i][0] - x_pivot;
        double y_shifted = a[i][1] - y_pivot;


        a[i][0] = x_pivot + (x_shifted * cos(angle) - y_shifted * sin(angle));
        a[i][1] = y_pivot + (x_shifted * sin(angle) + y_shifted * cos(angle));
    }
}
