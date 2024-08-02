#include "utils.h"

void utils::print_array(std::vector<column>& columns)
{
	for (column& c : columns) {
		std::cout << c.get_height() << ' ';
	}
	std::cout << '\n';
}
