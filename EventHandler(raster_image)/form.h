#pragma once
#include "common.h"
#include "elements.h"
#include "Brezenhem.h"

#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <iterator>

class Form {
public:
    explicit Form(Point position, Size size)
        : position_(position)
        , size_(size) {
    }

    // Узнаем позицию формы
    Point GetFormPosition() const {
        return { position_.x, position_.y };
    }

    // Узнаем размер формы
    Size GetFormSize() {
        return { size_.height, size_.width };
    }

    // Добавляем в форму элемент указанного типа
    void AddElementOnForm(ElementType elem_type, Point position, Size size, Point pivot_position, double angle) {
        int** a;
        a = new int*[4]; 
        for (int i = 0; i < 4; i++)
        {
            a[i] = new int[2];
        }
        a[0][0] = position.x;
        a[0][1] = position.y;
        a[1][0] = position.x + size.width;
        a[1][1] = position.y;
        a[2][0] = position.x + size.width; 
        a[2][1] = position.y + size.height;
        a[3][0] = position.x;
        a[3][1] = position.y + size.height;
        
        RotationPositionOfElement(a, pivot_position.x, pivot_position.y, angle);
        if (IsPointInRestangle({ a[0][0], a[0][1] }, size_.width+ position_.x, position_.x, size_.height+ position_.y, position_.y)
            && IsPointInRestangle({ a[1][0], a[1][1] }, size_.width+ position_.x, position_.x, size_.height+ position_.y, position_.y)
            && IsPointInRestangle({ a[3][0], a[3][1] }, size_.width+ position_.x, position_.x, size_.height+ position_.y, position_.y)
            && IsPointInRestangle({ a[2][0], a[2][1] }, size_.width+ position_.x, position_.x, size_.height+ position_.y, position_.y)) {
                auto elem = std::make_shared<Element>(elem_type);
                elem->SetElementAngleRotation(angle);
                elem->SetElementPosition(a);
                elem->SetElementMaxPoint({ position_.x + size_.width, position_.y + size_.height });
                elem->SetElementSize(size);
                elem->SetPivotPosition(pivot_position);
                // Элемент  добавляется в словарь для хранения очередности.
                if (!line_of_elements_.empty()) {
                    line_of_elements_[id_of_visible_element]->MakeElementUnvisible();
                }
                line_of_elements_[current_id_] = std::move(elem);
                line_of_elements_[current_id_]->MakeElementVisible();
                id_of_visible_element = current_id_;
                current_id_++;
            
        }
    }


    // Меняем видимость элемента на форме на видимый
    void MakeElementVisibleOnForm(size_t id) {
        if (line_of_elements_.count(id)) {
            line_of_elements_[id_of_visible_element]->MakeElementUnvisible();
            line_of_elements_[id]->MakeElementVisible();
            id_of_visible_element = id;
        }
        else {
            throw std::out_of_range("No element with given ID");
        }
    }

    // Меняем видимость элемента на форме на не видимый
    void MakeElementUnvisibleOnForm(size_t id) {
        if (line_of_elements_.count(id)) {
            line_of_elements_[id]->MakeElementUnvisible();
            if (line_of_elements_.size() > 1) {
                if (GetElementNodeById(id) != std::prev(line_of_elements_.end())) {
                    id_of_visible_element = std::prev(line_of_elements_.end())->first;
                }
                else {
                    id_of_visible_element = std::prev(GetElementNodeById(id))->first;
                }
            }
            else {
                id_of_visible_element = 0;
            }
        }
        else {
            throw std::out_of_range("No element with given ID");
        }
    }

    // Удаляем элемент из формы
    void DeleteElementFromForm(size_t id) {
        auto it = GetElementNodeById(id);
        // Если элемент подлежащий удалению был видим, то делаю его не видимым.
        if (it->second->GetElementVisibility()) {
            MakeElementUnvisibleOnForm(id);
        }
        line_of_elements_.erase(GetElementNodeById(id));
    }

    // Меняем позицию элемента на форме
    void ChangeElementPositionOnForm(size_t id, Point new_position, Point new_pivot, double new_angle ) {
            if (line_of_elements_.count(id)) {
                Size size = line_of_elements_[id]->GetElementSize();
                int** a;
                a = new int* [4];
                for (int i = 0; i < 4; i++)
                {
                    a[i] = new int[2];
                }
                a[0][0] = new_position.x;
                a[0][1] = new_position.y;
                a[1][0] = new_position.x + size.width;
                a[1][1] = new_position.y;
                a[2][0] = new_position.x + size.width;
                a[2][1] = new_position.y + size.height;
                a[3][0] = new_position.x;
                a[3][1] = new_position.y + size.height;
                RotationPositionOfElement(a, new_pivot.x, new_pivot.y, new_angle);
                if (IsPointInRestangle({ a[0][0], a[0][1] }, size_.width + position_.x, position_.x, size_.height + position_.y, position_.y)
                    && IsPointInRestangle({ a[1][0], a[1][1] }, size_.width + position_.x, position_.x, size_.height + position_.y, position_.y)
                    && IsPointInRestangle({ a[3][0], a[3][1] }, size_.width + position_.x, position_.x, size_.height + position_.y, position_.y)
                    && IsPointInRestangle({ a[2][0], a[2][1] }, size_.width + position_.x, position_.x, size_.height + position_.y, position_.y)) {

                    line_of_elements_[id]->SetElementPosition(a);
                    line_of_elements_[id]->SetElementAngleRotation(new_angle);
                    line_of_elements_[id]->SetPivotPosition(new_pivot);
                }
                else {
                    DeleteElementFromForm(id);
                }
            }
            else {
                throw std::out_of_range("No element with given ID");
            }
    }

    // Меняем угол поворота элемента относительно заданной точки
    void ChangeElementAngleRotationOnForm(size_t id, double new_angle) {
        if (line_of_elements_.count(id)) {
            Size size = line_of_elements_[id]->GetElementSize();
            int** a = line_of_elements_[id]->GetElementPosition();
            Point pivot = line_of_elements_[id]->GetPivotPosition();
            
            RotationPositionOfElement(a, pivot.x, pivot.y, new_angle);
            if (IsPointInRestangle({ a[0][0], a[0][1] }, size_.width + position_.x, position_.x, size_.height + position_.y, position_.y)
                && IsPointInRestangle({ a[1][0], a[1][1] }, size_.width + position_.x, position_.x, size_.height + position_.y, position_.y)
                && IsPointInRestangle({ a[3][0], a[3][1] }, size_.width + position_.x, position_.x, size_.height + position_.y, position_.y)
                && IsPointInRestangle({ a[2][0], a[2][1] }, size_.width + position_.x, position_.x, size_.height + position_.y, position_.y)) {
                line_of_elements_[id]->SetElementAngleRotation(new_angle);
                line_of_elements_[id]->SetPivotPosition(pivot);
                line_of_elements_[id]->SetElementPosition(a);
            }
            else {
                DeleteElementFromForm(id);
            }
        }
        else {
            throw std::out_of_range("No element with given ID");
        }
    }

    // Делаем форму активной
    void MakeFormActive() {
        active_ = true;
    }

    // Делаем форму неактивной
    void MakeFormUnactive() {
        active_ = false;
    }

    // Узнать статус активности формы
    bool GetFormActivities() {
        return active_;
    }

    // Получить доступ для чтения к словарю элементов
    std::unordered_map<size_t, std::shared_ptr<Element>> GetLineOfElements() const {
        return line_of_elements_;
    }

    // Управление элементом на форме
    void HendlerOfElements(Point click) {

        if (!line_of_elements_.empty()) {
            int last_id_of_visible_element = id_of_visible_element;
            //Проверяю приходиться ли клик на элемент формы. Начинаю с видимого элемента.
            if (line_of_elements_.count(id_of_visible_element)) {
                auto& it = line_of_elements_.at(id_of_visible_element);
                int** a = it->GetElementPosition();
                int max_x = 0;
                int max_y = 0;
                int min_x = size_.width + position_.x;
                int min_y = size_.height + position_.y;
                for (int i = 0; i < 4; ++i) {
                    if (a[i][0] > max_x) {
                        max_x = a[i][0];
                    }
                    if (a[i][1] > max_y) {
                        max_y = a[i][1];
                    }
                }
                for (int i = 0; i < 4; ++i) {
                    if (a[i][0] <  min_x) {
                        min_x = a[i][0];
                    }
                    if (a[i][1] < min_y) {
                        min_y = a[i][1];
                    }
                }
                if (IsPointInRestangle(click, max_x, min_x, max_y, min_y)) {
                    if (it->GetElementType() == ElementType::BUTTON) {
                        std::cout << "Element on the form number " << id_of_visible_element << " - Button.";
                    }
                    if (it->GetElementType() == ElementType::EDIT) {
                        std::cout << "Element on the form number " << id_of_visible_element << " - Edit.";
                    }
                    else if (it->GetElementType() == ElementType::IMAGE) {
                        std::cout << "Element on the form number " << id_of_visible_element << " - Image.";
                    }
                }
                else {
                    // Если элемент не видимый, то перевожу его в видимый режим
                    for (size_t i = 0; i < last_id_of_visible_element; ++i) {
                        if (line_of_elements_.count(i)) {
                            auto& t = line_of_elements_.at(i);
                            int** a = t->GetElementPosition();
                             max_x = 0;
                             max_y = 0;
                             min_x = size_.width + position_.x;
                             min_y = size_.height + position_.y;
                            for (int i = 0; i < 4; ++i) {
                                if (a[i][0] > max_x) {
                                    max_x = a[i][0];
                                }
                                if (a[i][1] > max_y) {
                                    max_y = a[i][1];
                                }
                            }
                            for (int i = 0; i < 4; ++i) {
                                if (a[i][0] < min_x) {
                                    min_x = a[i][0];
                                }
                                if (a[i][1] < min_y) {
                                    min_y = a[i][1];
                                }
                            }
                            if (IsPointInRestangle(click, max_x, min_x, max_y, min_y)) {
                                line_of_elements_[id_of_visible_element]->MakeElementUnvisible();
                                t->MakeElementVisible();
                                id_of_visible_element = i;
                            }
                        }
                    }
                    for (size_t i = last_id_of_visible_element + 1; i < line_of_elements_.size(); ++i) {
                        if (line_of_elements_.count(i)) {
                            auto& t = line_of_elements_.at(i);
                            int** a = t->GetElementPosition();
                            max_x = 0;
                            max_y = 0;
                            min_x = size_.width + position_.x;
                            min_y = size_.height + position_.y;
                            for (int i = 0; i < 4; ++i) {
                                if (a[i][0] > max_x) {
                                    max_x = a[i][0];
                                }
                                if (a[i][1] > max_y) {
                                    max_y = a[i][1];
                                }
                            }
                            for (int i = 0; i < 4; ++i) {
                                if (a[i][0] < min_x) {
                                    min_x = a[i][0];
                                }
                                if (a[i][1] < min_y) {
                                    min_y = a[i][1];
                                }
                            }
                            if (IsPointInRestangle(click, max_x, min_x, max_y, min_y)) {
                                line_of_elements_[id_of_visible_element]->MakeElementUnvisible();
                                t->MakeElementVisible();
                                id_of_visible_element = i;
                            }
                        }
                    }
                }
            }
        }
    }

    // Очередь вывода элементов на печать
    void PrintLineOfElements (char** image) const {
        for (size_t i = 0; i < id_of_visible_element; ++i) {
            if (line_of_elements_.count(i)) {
                line_of_elements_.at(i)->Draw(image);
            }
        }
        for (size_t i = id_of_visible_element + 1; i < line_of_elements_.size(); ++i) {
            if (line_of_elements_.count(i)) {
                line_of_elements_.at(i)->Draw(image);
            }
        }
        if (line_of_elements_.count(id_of_visible_element)) {
            line_of_elements_.at(id_of_visible_element)->Draw(image);
        }
    }


    //Рисуем формы в обработчике
    void DrawForm(char** image, int n) const {
        int x = 0;
        int y = 0;
        if (position_.x + size_.width < n) {
            x = position_.x + size_.width;
        }
        else {
            x = n-1;
        }
        if (position_.y + size_.height < n) {
            y = position_.y + size_.height;
        }
        else {
            y = n-1;
        }

        for (int i = position_.x; i < x+1; i++)
        {
            for (int j = position_.y; j < y + 1; j++) {
                image[j][i] = ' ';
            }
        }

        Brezenhem(image, position_.x, position_.y, x, position_.y, '+');
        Brezenhem(image, position_.x, position_.y, position_.x, y,'+');
        Brezenhem(image, x, position_.y, x, y,'+');
        Brezenhem(image, position_.x, y, x, y,'+');


        PrintLineOfElements(image);
    }


private:
    // Доступ к определенному элементу в словаре по его id при использовании итератора
    std::unordered_map<size_t, std::shared_ptr<Element>>::iterator GetElementNodeById(size_t id) {
        auto it = line_of_elements_.find(id);
        if (it == line_of_elements_.end()) {
            throw std::out_of_range("No element with given ID");
        }
        return it;
    }

    std::unordered_map<size_t, std::shared_ptr<Element>> line_of_elements_;
    Point position_ = {};
    Size size_ = {};
    bool active_ = false;
    size_t current_id_ = 0;
    size_t id_of_visible_element = 0;
};
