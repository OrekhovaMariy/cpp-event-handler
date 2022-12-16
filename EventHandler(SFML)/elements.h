#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "form.h"
#include "common.h"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

// Поддерживаемые виды элементов: кнопка, изображение, поле для ввода данных
enum class ElementType { BUTTON, IMAGE, EDIT };

class Element {
public:
    // Елемент после создания имеет нулевые координаты, размер, угол поворота. 
    // Видимость после создания - false

    explicit Element(ElementType el_type)
        : el_type_(el_type) {
    }

    // Устанавливаем позицию элемента
    void SetElementPosition(float** a) {
        position_ = a;
    }

    // Узнаем позицию элемента
    float** GetElementPosition() const {
        return (float**)position_;
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
        max_point_ = p;
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
    void SetElementAngleRotation(float angle) {
        angle_rotation_ = angle;
    }

    // Узнаем угол поворота элемента
    float GetElementAngleRotation() const {
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
    void Draw(sf::RenderWindow& window) const {
        sf::ConvexShape convex;

        // Устанавливаем количество вершин
        convex.setPointCount(4);
        // Описываем вершины
        convex.setPoint(0, sf::Vector2f(position_[0][0], position_[0][1]));
        convex.setPoint(1, sf::Vector2f(position_[1][0], position_[1][1]));
        convex.setPoint(2, sf::Vector2f(position_[2][0], position_[2][1]));
        convex.setPoint(3, sf::Vector2f(position_[3][0], position_[3][1]));

        if (el_type_ == ElementType::BUTTON) {
            convex.setFillColor(sf::Color::Blue);
        }
        if (el_type_ == ElementType::EDIT) {
            convex.setFillColor(sf::Color::Green);
        }
        if (el_type_ == ElementType::IMAGE) {
            convex.setFillColor(sf::Color::Yellow);
        }
        convex.setOutlineThickness(size_.height / 100);
        convex.setOutlineColor(sf::Color::Red);
        window.draw(convex);
    }

private:
    ElementType el_type_;
    float angle_rotation_ = 0.;
    bool visible_ = false;
    Size size_ = {};
    Point max_point_ = {};
    Point min_point_ = {};
    float** position_ = nullptr;
    Point pivot_position_{ 0., 0. };
};

