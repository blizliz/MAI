#include <cstdlib>
#include <iostream>
#include <memory>

#include "Figure.h"
#include "Hexagon.h"
#include "Octagon.h"
#include "Triangle.h"
#include "TArray.h"
#include "TList.h"

void Menu();

int main(int argc, char** argv) {
    TList<TArray<Figure>,Figure> list;

    Triangle triangle;
    Hexagon hexagon;
    Octagon octagon;
    size_t action = 6;

    while(action != 0) {
        Menu();
        std::cin >> action;
        switch (action) {
            case 0:
                break;
            case 1:
                std::cin >> triangle;
                list.Insert(std::make_shared<Triangle> (triangle));
                break;
            case 2:
                std::cin >> hexagon;
                list.Insert(std::make_shared<Hexagon> (hexagon));
                break;
            case 3:
                std::cin >> octagon;
                list.Insert(std::make_shared<Octagon> (octagon));
                break;
            case 4:
                list.RemoveByType(1);
                break;
            case 5:
                list.RemoveByType(2);
                break;
            case 6:
                list.RemoveByType(3);
                break;    
            case 7:
                std::cout << list << std::endl;
                break;
        }
    }

   return 0;
}

void Menu() {
    std::cout << "\n" << std::endl;
    std::cout << "1. Add triangle." << std::endl;
    std::cout << "2. Add hexagon." << std::endl;
    std::cout << "3. Add octagon." << std::endl;
    std::cout << "4. Remove all triangles." << std::endl;
    std::cout << "5. Remove all hexagons." << std::endl;
    std::cout << "6. Remove all octagons." << std::endl;
    std::cout << "7. Print list." << std::endl;
    std::cout << "0. Exit." << std::endl;
    std::cout << "Enter action number: ";
}