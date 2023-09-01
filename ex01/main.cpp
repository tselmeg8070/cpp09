#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	try {
		RPN rpn;
		rpn.calculate(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error" << std::endl;
	}
}
