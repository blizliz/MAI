#include "Triangle.h"
#include "Hexagon.h"
#include "Octagon.h"
#include <cstdlib>
#include <iostream>

void Menu()
{
	std::cout << "\n" << std::endl;
	std::cout << "1. Triangle" << std::endl;
	std::cout << "2. Hexagon" << std::endl;
	std::cout << "3. Octagon" << std::endl;
	std::cout << "4. MENU" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

int main()
{
	Figure *ptr;
	Menu();
    int action = 4;
    while (action != 0)
    {
		std::cout << "Enter action number: ";
		std::cin >> action;
		switch (action) {
		case 0:
			break;
		case 1:
			//Triangle
			ptr = new Triangle(std::cin);
			ptr->Print();
			std::cout << "Square: " << ptr->Square() << std::endl;
			delete ptr;
			break;
		case 2:
			//Hexagon
			ptr = new Hexagon(std::cin);
			ptr->Print();
			std::cout << "Square: " << ptr->Square() << std::endl;
			delete ptr;
			break;
		case 3:
			//Octagon
			ptr = new Octagon(std::cin);
			ptr->Print();
			std::cout << "Square: " << ptr->Square() << std::endl;
			delete ptr;
			break;
		case 4:
			Menu();
		default:
			std::cout << "Incorrect input!" << std::endl;
		}
    }
    return 0;
}

