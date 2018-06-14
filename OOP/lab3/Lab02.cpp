#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include "Hexagon.h"
#include "Octagon.h"
#include "Triangle.h"
#include "TListItem.h"
#include "TList.h"

void Menu();

int main()
{
	TList list;
	size_t side;
	size_t sidea, sideb, sidec;
	size_t fig;
	size_t action = 7;
	Menu();

	while (action != 0) {
		std::cout << "Enter action number: ";
		std::cin >> action;
		switch (action)
		{
		case 0:
			break;
		case 1: //Add new item in begin of list
			std::cout << "Select a figure: " << std::endl;
			std::cout << "1. Triangle" << std::endl;
			std::cout << "2. Hexagon" << std::endl;
			std::cout << "3. Octagon" << std::endl;
			std::cout << "0. Back to action selection" << std::endl;
			std::cout << "==>";
			std::cin >> fig;
			switch (fig)
			{
			case 1: //triangle
				std::cout << "Enter sides of triangle for adding: ";
				std::cin >> sidea >> sideb >> sidec;
				list.AddFirst(std::shared_ptr<Triangle>(new Triangle(sidea, sideb, sidec)));
				break;
			case 2: //hexagon
				std::cout << "Enter a side of hexagon for adding: ";
				std::cin >> side;
				list.AddFirst(std::shared_ptr<Hexagon>(new Hexagon(side)));
				break;
			case 3: //octagon
				std::cout << "Enter a side of octagon for adding: ";
				std::cin >> side;
				list.AddFirst(std::shared_ptr<Octagon>(new Octagon(side)));
				break;
			case 0:
				break;
			}
			break;
		case 2: //Add new item in end of list
			std::cout << "Select a figure: " << std::endl;
			std::cout << "1. Triangle" << std::endl;
			std::cout << "2. Hexagon" << std::endl;
			std::cout << "3. Octagon" << std::endl;
			std::cout << "0. Back to action selection" << std::endl;
			std::cout << "==>";
			std::cin >> fig;
			switch (fig)
			{
			case 1: //triangle
				std::cout << "Enter sides of triangle for adding: ";
				std::cin >> sidea >> sideb >> sidec;
				list.AddLast(std::shared_ptr<Triangle>(new Triangle(sidea, sideb, sidec)));
				break;
			case 2: //hexagon
				std::cout << "Enter a side of hexagon for adding: ";
				std::cin >> side;
				list.AddLast(std::shared_ptr<Hexagon>(new Hexagon(side)));
				break;
			case 3: //octagon
				std::cout << "Enter a side of octagon for adding: ";
				std::cin >> side;
				list.AddFirst(std::shared_ptr<Octagon>(new Octagon(side)));
				break;
			case 0:
				break;
			}
			break;
		case 3: //Insert in list
			size_t pos;
			std::cout << "Enter an item number position: ";
			std::cin >> pos;

			std::cout << "Select a figure: " << std::endl;
			std::cout << "1. Triangle" << std::endl;
			std::cout << "2. Hexagon" << std::endl;
			std::cout << "3. Octagon" << std::endl;
			std::cout << "0. Back to action selection" << std::endl;
			std::cout << "==>";
			std::cin >> fig;
			switch (fig)
			{
			case 1:
				std::cout << "Enter sides of triangle for adding: ";
				std::cin >> sidea >> sideb >> sidec;
				list.Insert(pos, std::shared_ptr<Triangle>(new Triangle(sidea, sideb, sidec)));
				break;
			case 2:
				std::cout << "Enter a side of hexagon for adding: ";
				std::cin >> side;
				list.Insert(pos, std::shared_ptr<Hexagon>(new Hexagon(side)));
				break;
			case 3:
				std::cout << "Enter a side of hexagon for adding: ";
				std::cin >> side;
				list.Insert(pos, std::shared_ptr<Octagon>(new Octagon(side)));
				break;
			case 0:
				break;
			}
			break;
		case 4:
			std::cout << list;
			break;
		case 5:
			std::cout << "Enter a position of item for delete: ";
			std::cin >> pos;
			list.DeleteElem(pos);
			break;
		case 6:
			list.Erase();
			break;
		case 7:
			Menu();
			break;
		default:
			break;
		}
	}

	return 0;
}

void Menu() {
	std::cout << "\n" << std::endl;
	std::cout << "1. Add new item in begin of list." << std::endl;
	std::cout << "2. Add new item in end of list." << std::endl;
	std::cout << "3. Insert in list." << std::endl;
	std::cout << "4. Print list." << std::endl;
	std::cout << "5. Delete item from list." << std::endl;
	std::cout << "6. Erase list." << std::endl;
	std::cout << "7. Print MENU." << std::endl;
	std::cout << "0. Exit." << std::endl;

}
