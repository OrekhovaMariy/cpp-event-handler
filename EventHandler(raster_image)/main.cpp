#include <iostream>
#include <cassert>
#include <sstream>

#include "common.h"
#include "event_handler.h"

using namespace std;

void TestForm() {
	EventHandler handler(40);
	std::stringstream output;
	handler.AddFormInLine({ 10, 15 }, { 15, 20 }); // id - 0
	handler.AddFormInLine({ 15, 20 }, { 15, 20 }); // id - 1 
	handler.AddFormInLine({ 20, 25 }, { 15, 20 }); // id - 2
	handler.AddFormInLine({ 50, 25 }, { 15, 20 }); // не добавилась, так как расположение не соответствует обработчику
	
	handler.Print(output);

	handler.DeleteForm(2); 
	handler.Print(output);
	
	handler.AddFormInLine({ 20, 25 }, { 15, 20 }); // id - 3
	handler.DeleteForm(1);
	handler.Print(output);
	const auto answer =
		"##########################################\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#          ++++++++++++++++              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +    ++++++++++++++++         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +    ++++++++++++++++    #\n"
		"#          +    +    +              +    #\n"
		"#          +    +    +              +    #\n"
		"#          +    +    +              +    #\n"
		"#          +    +    +              +    #\n"
		"#          +    +    +              +    #\n"
		"#          +    +    +              +    #\n"
		"#          +    +    +              +    #\n"
		"#          +    +    +              +    #\n"
		"#          +    +    +              +    #\n"
		"#          ++++++    +              +    #\n"
		"#               +    +              +    #\n"
		"#               +    +              +    #\n"
		"#               +    +              +    #\n"
		"#               +++++++++++++++++++++    #\n"
		"##########################################\n"
		"##########################################\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#          ++++++++++++++++              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +    ++++++++++++++++         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          +    +              +         #\n"
		"#          ++++++              +         #\n"
		"#               +              +         #\n"
		"#               +              +         #\n"
		"#               +              +         #\n"
		"#               ++++++++++++++++         #\n"
		"##########################################\n"
		"##########################################\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#                                        #\n"
		"#          ++++++++++++++++              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +              +              #\n"
		"#          +         ++++++++++++++++    #\n"
		"#          +         +              +    #\n"
		"#          +         +              +    #\n"
		"#          +         +              +    #\n"
		"#          +         +              +    #\n"
		"#          +         +              +    #\n"
		"#          +         +              +    #\n"
		"#          +         +              +    #\n"
		"#          +         +              +    #\n"
		"#          +         +              +    #\n"
		"#          +++++++++++              +    #\n"
		"#                    +              +    #\n"
		"#                    +              +    #\n"
		"#                    +              +    #\n"
		"#                    ++++++++++++++++    #\n"
		"##########################################\n";
	assert(answer == output.str());
}

void TestElementsOnForm() {
	EventHandler handler(100);
	handler.AddFormInLine({ 10, 20 }, { 60, 50 }); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::BUTTON, { 15 , 25 }, { 10 , 10 }, { 0 , 0 }, 0); // id - 0
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::IMAGE, { 25 , 35 }, { 15 , 15 }, { 0, 0 }, 0); // id - 1
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::EDIT, { 30 , 40 }, { 20 , 10 }, { 0 , 0 }, 0); // id - 2
	std::stringstream output;
	handler.Print(output);

	handler.AddFormInLine({ 20, 30 }, { 60, 50 }); // id - 1
	handler.GetFormNodeById(1)->second->AddElementOnForm(ElementType::BUTTON, { 25 , 35 }, { 10 , 10 }, { 0 , 0 }, 0.); // id - 0

	assert(handler.GetFormNodeById(0)->second->GetLineOfElements().size() == 3);
	assert(handler.GetFormNodeById(1)->second->GetLineOfElements().size() == 1);
	
	handler.Print(output);
	
	handler.DeleteForm(0);
	handler.Print(output);

	handler.AddFormInLine({ 10, 20 }, { 60, 50 }); // id - 2
	handler.Print(output);
	handler.GetFormNodeById(2)->second->AddElementOnForm(ElementType::BUTTON, { 25 , 35 }, { 10 , 10 }, { 35 , 40 }, 0); //id - 0
	handler.GetFormNodeById(2)->second->AddElementOnForm(ElementType::IMAGE, { 5 , 30 }, { 10 , 10 }, { 25 , 35 }, 0); // не добавился, так как расположение не соответствует форме
	handler.GetFormNodeById(2)->second->AddElementOnForm(ElementType::IMAGE, { 30 , 30 }, { 13 , 13 }, { 33, 33 }, 45); // id - 1
	
	handler.Print(output);
	
	handler.GetFormNodeById(2)->second->AddElementOnForm(ElementType::EDIT, { 30 , 40 }, { 20 , 10 }, { 0 , 0 }, 20); // id - 2
	handler.GetFormNodeById(2)->second->AddElementOnForm(ElementType::IMAGE, { 25 , 35 }, { 15 , 15 }, { 35 , 45 }, 25); // id - 3
	handler.Print(output);

	handler.GetFormNodeById(2)->second->MakeElementUnvisibleOnForm(3);
	handler.GetFormNodeById(2)->second->MakeElementVisibleOnForm(0);
	handler.GetFormNodeById(2)->second->DeleteElementFromForm(3);
	handler.GetFormNodeById(2)->second->ChangeElementPositionOnForm(2, { 45 , 50 }, {45,50}, 0);
	handler.Print(output);
	handler.GetFormNodeById(2)->second->ChangeElementPositionOnForm(2, { 0, 0 }, {0,0}, 45);
	handler.Print(output);

	handler.GetFormNodeById(2)->second->ChangeElementAngleRotationOnForm(0, 45);
	handler.Print(output);

	handler.GetFormNodeById(2)->second->ChangeElementAngleRotationOnForm(0, 45); 
	handler.Print(output);
	
	std::cout << output.str() << std::endl;
}

void TestHendler() {
	EventHandler handler(40);
	handler.AddFormInLine({ 10, 10 }, { 20, 20 }); // id - 0
	handler.Click({ 5,10 }); // ничего не вывелось, так как клик пришелся мимо формы
	handler.Click({ 50,50 }); // ничего не вывелось, так как клик пришелся мимо области обработчика
	handler.AddFormInLine({ 15, 15 }, { 20, 20 }); // id - 1
	handler.Click({ 21, 22 }); // будет вывод - Form 1
	handler.Click({ 11, 11 }); // ничего не выведется, потому что форма по которой попал клик, была неактивной. После клика она стала активной.
	assert(handler.GetFormNodeById(0)->second->GetFormActivities() == 1); // в активную форму будет переведена форма с id 0
	assert(handler.GetFormNodeById(1)->second->GetFormActivities() == 0); // с id 1 форма перестанет быть активной

	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::BUTTON, { 15 , 15 }, { 10 , 10 }, { 20 , 20 }, 45);
	handler.GetFormNodeById(0)->second->AddElementOnForm(ElementType::IMAGE, { 20 , 20 }, { 10 , 10 }, { 20 , 20 }, 0);

	handler.Click({ 25, 25}); // будет вывод - Form 0. Element on the form number 1 - Image.
	std::stringstream output;
	handler.Print(output);
	std::cout << output.str() << std::endl;

	handler.Click({ 18, 18 }); // будет вывод - Form 0. 
	//Так как клик пришелся по невидимому элементу и перевел его в видимый.
	handler.Click({ 18, 18 }); // будет вывод - Form 0. Element on the form number 0 - Button.

}

// Отчет координат для форм, элементов и обработчика идет от верхнего левого угла
int main() {
	TestForm();
	TestElementsOnForm();
	TestHendler();
}