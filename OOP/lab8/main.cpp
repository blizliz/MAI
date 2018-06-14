#include <memory>
#include "Octagon.h"
#include "Hexagon.h"
#include "Triangle.h"
#include <cstdlib>
#include <iostream>
#include "TList.h"

#include <random>
#include <chrono>

using namespace std;

void Menu();

int main()
{
	TList<Figure> list;
	TList<Figure> list1;
	TList<Figure> list2;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 100);
	size_t side;
	size_t sidea, sideb, sidec;
	size_t fig;
	size_t action = 8;

	while (action != 0) {
		Menu();
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
			for (auto i : list) {
				std::cout << "( ";
				i->Print();
				std::cout << " ) ";
			}
			std::cout << std::endl;
			break;
		case 6:
			std::cout << "Enter a position of item for delete: ";
			std::cin >> pos;
			list.DeleteElem(pos);
			break;
		case 7:
			list.Erase();
			break;
		case 8:
			for (int i = 0; i < 100; i++) {
				int side = distribution(generator);
				list1.push(std::make_shared<Triangle>(side, side, side));
				list1.push(std::make_shared<Hexagon>(side));
				list1.push(std::make_shared<Octagon>(side));
				list2.push(std::make_shared<Triangle>(side, side, side));
				list2.push(std::make_shared<Hexagon>(side));
				list2.push(std::make_shared<Octagon>(side));
			}

			std::cout << "Sort -------------" << std::endl;
			auto start1 = std::chrono::high_resolution_clock::now();
			list1.sort();
			auto end1 = std::chrono::high_resolution_clock::now();
			std::cout << "Done -------------" << std::endl;

			std::cout << "Sort -------------" << std::endl;
			auto start2 = std::chrono::high_resolution_clock::now();
			list2.sort_parallel();
			auto end2 = std::chrono::high_resolution_clock::now();
			std::cout << "Done -------------" << std::endl;

			std::cout << "Sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() << std::endl;
			std::cout << "ParallelSort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << std::endl;

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
	std::cout << "5. Print list with iterator." << std::endl;
	std::cout << "6. Delete item from list." << std::endl;
	std::cout << "7. Erase list." << std::endl;
	std::cout << "8. Compare sorts of list." << std::endl;
	std::cout << "0. Exit." << std::endl;
	std::cout << "______________________" << std::endl;
	std::cout << "Enter action number: ";

}
