#include <memory>
#include "Octagon.h"
#include "Hexagon.h"
#include "Triangle.h"
#include <cstdlib>
#include <iostream>
#include "TList.h"
#include "TArray.h"

#include <random>
#include <chrono>

int main()
{
	typedef std::function<void(void)> TCommand;

	TList<Figure> list;
	TArray<TCommand> array(100);

	size_t sidea;
	size_t sideb;
	size_t sidec;
	
	TCommand insert = [&]() {
		std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> distr1(1, 3);

		std::uniform_int_distribution<int> distr2(1, 100);

		switch (distr1(gen)) {
		case 1: //Triangle
			sidea = distr2(gen);
			sideb = distr2(gen);
			sidec = distr2(gen);
			list.push(std::make_shared<Triangle>(sidea, sideb, sidec));
			break;
		case 2: //Hexagon
			sidea = distr2(gen);

			list.push(std::make_shared<Hexagon>(sidea));
			break;
		case 3: //Octagon
			sidea = distr2(gen);

			list.push(std::make_shared<Octagon>(sidea));
			break;
		}
	};

	TCommand delete_less_square = [&]() {
		double square = 500;

		TList<Figure> tmp_list;
		while (!list.Empty()) {
			std::shared_ptr<Figure> cur = list .pop();
			if (cur->Square() >= square) {
				tmp_list.push(std::move(cur));
			}
		}

		while (!tmp_list.Empty()) {
			list.push(tmp_list.pop());
		}
	};

	TCommand print = [&]() {
		for (auto it : list) {
			it->Print();
			std::cout << "Its square is " << it->Square() << std::endl << std::endl;
		}
	};

	TCommand reverse = [&]() {
		TList<Figure> tmp;
		while (!list.Empty()) {
			tmp.push(list.pop());
		}

		list.Swap(tmp);
	};

	array.push(std::shared_ptr<TCommand>(&print, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&reverse, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&delete_less_square, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&print, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&insert, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&insert, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&insert, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&insert, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&insert, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&insert, [](TCommand *) {}));
	array.push(std::shared_ptr<TCommand>(&insert, [](TCommand *) {}));


	while (array.GetSize()) {
		std::shared_ptr<TCommand> cmd = array.pop();
		std::future<void> future = std::async(*cmd);
		future.get();
	}

	system("pause");
	return 0;
}

