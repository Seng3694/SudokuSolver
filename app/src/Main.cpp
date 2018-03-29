#include <iostream>
#include <chrono>

#include "Board.h"

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		Board board{};

		if (board.load(argv[1]))
		{
			board.print();

			std::cout << std::endl << std::endl;

			SolveResult result{};

			if (board.isSolveable())
			{
				auto begin = std::chrono::steady_clock::now();

				std::cout << "solving..." << std::endl << std::endl;
				result = board.solve();

				auto end = std::chrono::steady_clock::now();

				auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

				if (result.solved)
				{
					board.print();
					std::cout << std::endl;
					std::cout << "solved in " << elapsedMilliseconds << " ms" << std::endl;
					std::cout << "with backtracks: " << result.backtracks << std::endl;
				}
			}

			if(!result.solved)
			{
				std::cout << "is not solveable" << std::endl;
			}
		}
		else
		{
			std::cout << "could not load " << argv[1] << std::endl;
		}

		std::cout << "press any key to exit..." << std::endl;
		std::getchar();
	}

	return 0;
}