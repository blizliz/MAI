#include <cstdlib>
#include <iostream>

#include "Hexagon.h"
#include "TListItem.h"
#include "TList.h"

void Menu();

int main(int argc, char **argv)
{
    TList list;
	Hexagon hexagon;
    Menu();
    int action = 7;
    while (action != 0)
    {
		std::cout << "Enter action number: ";
		std::cin >> action;
		switch (action) {
		case 0:
			break;
		case 1:
			std::cin >> hexagon;
			list.push(hexagon);
			break;
		case 2:
			std::cin >> hexagon;
			list.pushBack(hexagon);
			break;
		case 3:
			std::cin >> hexagon;
			list.delEl(hexagon);
			break;
		case 4:
			std::cout << list;
			break;
		case 5:
			list.pop();
			break;
		case 6:
			list.eraseList();
			break;
		case 7:
			Menu();
			break;
		}
    }
    return 0;
}

void Menu()
{
    std::cout << "\n" << std::endl;
    std::cout << "1. Add new item in begin of list." << std::endl;
    std::cout << "2. Add new item in end of list." << std::endl;
    std::cout << "3. Delete item from list." << std::endl;
    std::cout << "4. Print list." << std::endl;
    std::cout << "5. Pop from begin of list." << std::endl;
    std::cout << "6. Erase list." << std::endl;
    std::cout << "7. MENU." << std::endl;
    std::cout << "0. Exit." << std::endl;
}