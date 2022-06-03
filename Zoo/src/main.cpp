
#include <iostream>
#include "Zoo.h"

int main()
{
	srand((int)time(NULL));

	try {
		Zoo(std::cout).run(std::cin);
	}
	catch (std::exception& e) { cerr << e.what() << '\n'; }

	return EXIT_SUCCESS;
}