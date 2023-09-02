#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	PmergeMe p(argv[1]);
	p.sortDeque();
	p.sortQueue();
	return (0);
}
