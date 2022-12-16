#pragma once
#include "form.h"
#include "common.h"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

// Поддерживаемые виды элементов: кнопка, изображение, поле для ввода данных
enum class ElementType { BUTTON, IMAGE, EDIT};

class Element {
public:
    // Елемент после создания имеет нулевые координаты, размер, угол поворота. 
    // Видимость после создания - false
    
    explicit Element(ElementType el_type)
        : el_type_(el_type) {
    }

    // Устанавливаем позицию элемента
    void SetElementPosition(int** a) {
        position_ = a;
    }

    // Узнаем позицию элемента
    int** GetElementPosition() const {
        return (int**)position_;
    }

    // Устанавливаем позицию точки поворота
    void SetPivotPosition(Point pivot_position) {
        pivot_position_ = pivot_position;
    }

    // Узнаем позицию точки поворота
    Point GetPivotPosition() const {
        return pivot_position_;
    }

    // Устанавливаем размер элемента
    void SetElementSize(Size size) {
            size_ = size;
    }

    // Узнаем размер элемента
    Size GetElementSize() {
        return size_;
    }

    // Устанавливаем максимальную позицию, которая соответствует границе формы
    void SetElementMaxPoint(Point p) {
        max_point_= p;
    }

    // Узнаем максимальную позицию, которая соответствует границе формы
    Point GetElementMaxPoint() {
        return max_point_;
    }

    // Устанавливаем минимальную позицию, которая соответствует границе формы
    void SetElementMinPoint(Point p) {
        min_point_ = p;
    }

    // Узнаем минимальную позицию, которая соответствует границе формы
    Point GetElementMinPoint() {
        return min_point_;
    }

    // Устанавливаем угол поворота элемента
    void SetElementAngleRotation(double angle) {
        angle_rotation_ = angle;
    }

    // Узнаем угол поворота элемента
    double GetElementAngleRotation() const {
        return angle_rotation_;
    }

    // Делаем элемент видимым
    void MakeElementVisible() {
        visible_ = true;
    }

    // Делаем элемент не видимым
    void MakeElementUnvisible() {
        visible_ = false;
    }

    // Узнаем статус видимости элемента
    bool GetElementVisibility() {
        return visible_;
    }

    // Узнаем тип элемента
    ElementType GetElementType() {
        return el_type_;
    }

// Должен рисоваться прямоугольник
    void Draw(char** image) const {

            if (el_type_ == ElementType::BUTTON) {

                Brezenhem(image, position_[0][0], position_[0][1], position_[1][0], position_[1][1], 'B');
                Brezenhem(image, position_[1][0], position_[1][1], position_[2][0], position_[2][1], 'B');
                Brezenhem(image, position_[2][0], position_[2][1], position_[3][0], position_[3][1], 'B');
                Brezenhem(image, position_[3][0], position_[3][1], position_[0][0], position_[0][1], 'B');
            }
            if (el_type_ == ElementType::EDIT) {
                Brezenhem(image, position_[0][0], position_[0][1], position_[1][0], position_[1][1], 'E');
                Brezenhem(image, position_[1][0], position_[1][1], position_[2][0], position_[2][1], 'E');
                Brezenhem(image, position_[2][0], position_[2][1], position_[3][0], position_[3][1], 'E');
                Brezenhem(image, position_[3][0], position_[3][1], position_[0][0], position_[0][1], 'E');
            }
            if (el_type_ == ElementType::IMAGE) {
                Brezenhem(image, position_[0][0], position_[0][1], position_[1][0], position_[1][1], 'I');
                Brezenhem(image, position_[1][0], position_[1][1], position_[2][0], position_[2][1], 'I');
                Brezenhem(image, position_[2][0], position_[2][1], position_[3][0], position_[3][1], 'I');
                Brezenhem(image, position_[3][0], position_[3][1], position_[0][0], position_[0][1], 'I');
            }
    }

private:
    ElementType el_type_;
    double angle_rotation_ = 0;
    bool visible_ = false;
    Size size_ = {};
    Point max_point_ = {};
    Point min_point_ = {};
    int** position_ = nullptr;
    Point pivot_position_{ 0, 0 };
};

