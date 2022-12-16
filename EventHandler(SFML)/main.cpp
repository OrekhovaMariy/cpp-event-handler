#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include <cassert>
#include <sstream>

#include "common.h"
#include "event_handler.h"

using namespace std;

void TestForm(sf::RenderWindow& window, EventHandler handler) {

	handler.AddFormInLine({ 10, 15 }, { 150, 200 }); // id - 0
	handler.AddFormInLine({ 0, 0 }, { 150, 200 }); // id - 1 
	handler.AddFormInLine({ 20, 25 }, { 150, 200 }); // id - 2
	handler.AddFormInLine({ 500, 250 }, { 150, 200 }); // не добавилась, так как расположение не соответствует обработчику

	handler.PrintLineOfForms(window);
}
void TestFormDelete(sf::RenderWindow& window, EventHandler handler) {
	handler.AddFormInLine({ 10, 15 }, { 150, 200 }); // id - 0
	handler.AddFormInLine({ 0, 0 }, { 150, 200 }); // id - 1 
	handler.AddFormInLine({ 20, 25 }, { 150, 200 }); // id - 2
	handler.DeleteForm(2);
	handler.PrintLineOfForms(window);

}

void TestElementsOnFormAddElement(sf::RenderWindow& window, EventHandler handler) {

	handler.AddFormInLine({ 100, 200 }, { 600, 500 }); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::BUTTON, { 150 , 250 }, { 100 , 100 }, { 100 , 200 }, 0); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::IMAGE, { 250 , 350 }, { 150 , 150 }, { 100 , 200 }, 20); // id - 1
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::EDIT, { 300 , 400 }, { 200 , 100 }, { 100 , 200 }, 0); // id - 2

	handler.PrintLineOfForms(window);
}

void TestElementsOnFormDeleElement(sf::RenderWindow& window, EventHandler handler) {
	handler.AddFormInLine({ 100, 200 }, { 600, 500 }); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::BUTTON, { 150 , 250 }, { 100 , 100 }, { 100 , 200 }, 0); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::IMAGE, { 250 , 350 }, { 150 , 150 }, { 100 , 200 }, 20); // id - 1
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::EDIT, { 250 , 300 }, { 200 , 100 }, { 100 , 200 }, 0); // id - 2
	handler.AddFormInLine({ 300, 400 }, { 600, 500 }); // id - 1
	handler.GetFormNodeById(1)->second->AddElementOnForm(ElementType::BUTTON, { 450 , 550 }, { 100 , 100 }, { 550 , 600 }, 10); // id - 0
	handler.GetFormNodeById(1)->second->AddElementOnForm(ElementType::IMAGE, { 50 , 300 }, { 100 , 100 }, { 250 , 350 }, 0); // не добавился, так как расположение не соответствует форме
	handler.GetFormNodeById(1)->second->AddElementOnForm(ElementType::IMAGE, { 450 , 550 }, { 150 , 150 }, { 0 , 0 }, 10); // id - 1
	handler.GetFormNodeById(1)->second->AddElementOnForm(ElementType::EDIT, { 300 , 400 }, { 200 , 100 }, { 100 , 200 }, 0); // id - 2

	assert(handler.GetFormNodeById(0)->second->GetLineOfElements().size() == 3);
	assert(handler.GetFormNodeById(1)->second->GetLineOfElements().size() == 3);

	handler.GetFormNodeById(1)->second->DeleteElementFromForm(2);
	assert(handler.GetFormNodeById(1)->second->GetLineOfElements().size() == 2);
	handler.PrintLineOfForms(window);
}

void TestElementsOnFormChangeVisibleElement(sf::RenderWindow& window, EventHandler handler) {
	handler.AddFormInLine({ 100, 200 }, { 600, 500 }); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::BUTTON, { 150 , 250 }, { 170 , 170 }, { 100 , 200 }, 0); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::IMAGE, { 250 , 350 }, { 150 , 150 }, { 100 , 200 }, 20); // id - 1
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::EDIT, { 300 , 400 }, { 200 , 100 }, { 100 , 200 }, 0); // id - 2
	handler.GetFormNodeById(0)->second->MakeElementUnvisibleOnForm(2);
	handler.GetFormNodeById(0)->second->MakeElementVisibleOnForm(0);
	handler.PrintLineOfForms(window);
}

void TestElementsOnFormChangePositionElement(sf::RenderWindow& window, EventHandler handler) {
	handler.AddFormInLine({ 100, 200 }, { 600, 500 }); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::BUTTON, { 150 , 250 }, { 170 , 170 }, { 100 , 200 }, 0); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::IMAGE, { 250 , 350 }, { 150 , 150 }, { 100 , 200 }, 20); // id - 1
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::EDIT, { 300 , 400 }, { 200 , 100 }, { 100 , 200 }, 0); // id - 2
	handler.GetFormNodeById(0)->second->ChangeElementPositionOnForm(2, { 350 , 500 }, { 450,500 }, 10);
	handler.GetFormNodeById(0)->second->ChangeElementPositionOnForm(1, { 0, 0 }, { 0,0 }, 45);
	handler.GetFormNodeById(0)->second->ChangeElementAngleRotationOnForm(0, 45);
	assert(handler.GetFormNodeById(0)->second->GetLineOfElements().size() == 1);
	handler.PrintLineOfForms(window);

}

void TestHendler(EventHandler handler) {

	handler.AddFormInLine({ 100, 100 }, { 200, 200 }); // id - 0
	handler.Click({ 50,100 }); // ничего не вывелось, так как клик пришелся мимо формы
	handler.Click({ 500,500 }); // ничего не вывелось, так как клик пришелся мимо области обработчика
	handler.AddFormInLine({ 150, 150 }, { 200, 200 }); // id - 1
	handler.Click({ 210, 220 }); // будет вывод - Form 1
	handler.Click({ 110, 110 }); // ничего не выведется, потому что форма по которой попал клик, была неактивной. После клика она стала активной.
	assert(handler.GetFormNodeById(0)->second->GetFormActivities() == 1); // в активную форму будет переведена форма с id 0
	assert(handler.GetFormNodeById(1)->second->GetFormActivities() == 0); // с id 1 форма перестанет быть активной

	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::BUTTON, { 150 , 150 }, { 100 , 100 }, { 200 , 200 }, 45);
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::IMAGE, { 200 , 200 }, { 100 , 100 }, { 200 , 200 }, 0);

	handler.Click({ 250, 250 }); // будет вывод - Form 0. Element on the form number 1 - Image.


	handler.Click({ 180, 180 }); // будет вывод - Form 0. 
	//Так как клик пришелся по невидимому элементу и перевел его в видимый.
	handler.Click({ 180, 180 }); // будет вывод - Form 0. Element on the form number 0 - Button.

}


int main() {
	//создаем окно обработчика

	int n = 400;
	int m = 400;

	sf::VideoMode mode(n, m);

	sf::RenderWindow window(mode, "TestForm");
	EventHandler handler({ static_cast<float>(n) ,static_cast<float>(m) }, window);


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}
		window.clear();
		TestForm(window, handler);
		window.display();
	}

	sf::RenderWindow window1(mode, "TestFormDelete");
	EventHandler handler1({ static_cast<float>(n) ,static_cast<float>(m) }, window1);

	while (window1.isOpen()) {
		sf::Event event;
		while (window1.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window1.close();
			}

		}
		window1.clear();
		TestFormDelete(window1, handler1);
		window1.display();
	}

	mode.height = 1000;
	mode.width = 1000;
	sf::RenderWindow window2(mode, "TestElementsOnFormAddElement");
	EventHandler handler2({ static_cast<float>(n) ,static_cast<float>(m) }, window2);

	while (window2.isOpen()) {
		sf::Event event;
		while (window2.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window2.close();
			}

		}
		window2.clear();
		TestElementsOnFormAddElement(window2, handler2);
		window2.display();
	}

	sf::RenderWindow window3(mode, "TestElementsOnFormDeleElement");
	EventHandler handler3({ static_cast<float>(n) ,static_cast<float>(m) }, window3);

	while (window3.isOpen()) {
		sf::Event event;
		while (window3.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window3.close();
			}

		}
		window3.clear();
		TestElementsOnFormDeleElement(window3, handler3);
		window3.display();
	}

	sf::RenderWindow window4(mode, "TestElementsOnFormChangeElement");
	EventHandler handler4({ static_cast<float>(n) ,static_cast<float>(m) }, window4);

	while (window4.isOpen()) {
		sf::Event event;
		while (window4.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window4.close();
			}

		}
		window4.clear();
		TestElementsOnFormChangeVisibleElement(window4, handler4);
		window4.display();
	}

	sf::RenderWindow window5(mode, "TestElementsOnFormChangeElement");
	EventHandler handler5({ static_cast<float>(n) ,static_cast<float>(m) }, window5);

	while (window5.isOpen()) {
		sf::Event event;
		while (window5.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window5.close();
			}

		}
		window5.clear();
		TestElementsOnFormChangePositionElement(window5, handler5);
		window5.display();
	}

	TestHendler(handler5);
	return 0;
}