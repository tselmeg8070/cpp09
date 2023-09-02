#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const std::string &str) : _original(str)
{
	std::set<int>			set;
	std::stringstream		s(str);
	std::string				word;
	int						val;

	while (getline(s, word, ' '))
	{
		val = std::atoi(word.c_str());
		if (set.find(val) != set.end())
		{
			set.insert(val);
			_dequeValues.push_back(val);
			_queueValues.push_back(val);
		}
		else
			throw std::runtime_error("Error");
	}
}

PmergeMe::PmergeMe(const PmergeMe &t) : _original(t._original), _dequeValues(t._dequeValues), _queueValues(t._queueValues)
{}

PmergeMe::~PmergeMe()
{}

PmergeMe &PmergeMe::operator=(const PmergeMe &t)
{
	if (this != &t)
	{
		delete (this);
		return (*(new PmergeMe(t)));
	}
	return (*this);
}

void	PmergeMe::sortDeque()
{
	mergeSort(_dequeValues.begin(), _dequeValues.end());
	std::deque<int>::iterator b = _dequeValues.begin();

	while (b != _dequeValues.end())
	{
		std::cout << *b << " ";
		++b;
	}
	std::cout << std::endl;
}

void	PmergeMe::sortQueue()
{
	mergeSort(_queueValues.begin(), _queueValues.end());
	std::list<int>::iterator b = _queueValues.begin();

	while (b != _queueValues.end())
	{
		std::cout << *b << " ";
		++b;
	}
	std::cout << std::endl;
}


