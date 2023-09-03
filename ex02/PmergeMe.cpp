#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **argv)
{
	int	val;

	std::set<int> set;
	while (*argv)
	{
		val = std::atoi(*argv);
		if (set.find(val) == set.end() && val >= 0)
		{
			set.insert(val);
			_dequeValues.push_back(val);
			_listValues.push_back(val);
		}
		else
			throw std::runtime_error("Error");
		argv++;
	}
}

PmergeMe::PmergeMe(const PmergeMe &t)
	: _dequeValues(t._dequeValues),
		_listValues(t._listValues),
		_sortedDequeValues(t._sortedDequeValues),
		_sortedListValues(t._sortedListValues),
		_dequeTimeTaken(t._dequeTimeTaken),
		_listTimeTaken(t._listTimeTaken)
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &t)
{
	if (this != &t)
	{
		delete (this);
		return (*(new PmergeMe(t)));
	}
	return (*this);
}

const std::deque<int> &PmergeMe::getDequeValues() const
{
	return (_dequeValues);
}

const std::list<int> &PmergeMe::getListValues() const
{
	return (_listValues);
}

const std::deque<int> &PmergeMe::getSortedDequeValues() const
{
	return (_sortedDequeValues);
}

const std::list<int> &PmergeMe::getSortedListValues() const
{
	return (_sortedListValues);
}

double PmergeMe::getDequeTimeTaken() const
{
	return (_dequeTimeTaken);
}

double PmergeMe::getListTimeTaken() const
{
	return (_listTimeTaken);
}

void PmergeMe::fordJohnsonDeque()
{
	bool			hasStray = false;
	int				stray;
	int				bsLimit;
	clock_t	start;
	clock_t	end;

	hasStray = false;
	std::deque<int> cpyDequeValues;
	std::deque<std::deque<int> > pairs;
	std::deque<int> sorted;
	std::deque<int> waitList;
	cpyDequeValues = _dequeValues;
	start = clock();
	//Edge case
	if (_dequeValues.size() <= 1)
	{
		sorted = _dequeValues;
		end = clock();
		_dequeTimeTaken = double((end - start) / double(CLOCKS_PER_SEC));
		return ;
	}
	//Making list even by storing stray one
	if (cpyDequeValues.size() % 2 == 1)
	{
		hasStray = true;
		stray = cpyDequeValues.back();
		cpyDequeValues.pop_back();
	}
	//Making pairs
	for (size_t i = 0; i < cpyDequeValues.size(); i = i + 2)
	{
		std::deque<int> temp;
		if (cpyDequeValues[i] > cpyDequeValues[i + 1])
		{
			temp.push_back(cpyDequeValues[i]);
			temp.push_back(cpyDequeValues[i + 1]);
		}
		else
		{
			temp.push_back(cpyDequeValues[i + 1]);
			temp.push_back(cpyDequeValues[i]);
		}
		pairs.push_back(temp);
	}
	//Sorting pairs with mergesort
	mergeSortDeque(pairs.begin(), pairs.end());
	for (size_t i = 0; i < pairs.size(); i++)
	{
		sorted.push_back(pairs[i].front());
		waitList.push_back(pairs[i].back());
	}
	//First element in waitList is lower than first element of sorted
	//so it safe to add push it to front of sorted.
	sorted.push_front(waitList.front());
	waitList.pop_front();
	bsLimit = 2;
	while (!waitList.empty())
	{
		std::deque<int>::iterator it = sorted.begin();
		std::advance(it, bsLimit);
		it = std::lower_bound(sorted.begin(), it, waitList.front());
		sorted.insert(it, waitList.front());
		waitList.pop_front();
		bsLimit += 2;
	}
	if (hasStray)
	{
		std::deque<int>::iterator it = std::lower_bound(sorted.begin(),
				sorted.end(), stray);
		sorted.insert(it, stray);
	}
	_sortedDequeValues = sorted;
	end = clock();
	_dequeTimeTaken = double((end - start) / double(CLOCKS_PER_SEC));
}

void PmergeMe::fordJohnsonList()
{
	bool									hasStray = false;
	int										stray;
	int										bsLimit;
	clock_t									start;
	clock_t									end;
	std::list<int>::iterator				it;
	std::list<int>							cpyListValues;
	std::list<std::list<int> >				pairs;
	std::list<int>							sorted;
	std::list<int>							waitList;
	std::list<std::list<int> >::iterator	itPair;

	cpyListValues = _listValues;
	start = clock();

	// Edge case
	if (_listValues.size() <= 1)
	{
		sorted = _listValues;
		std::time(&end);
		_listTimeTaken = double((end - start) / double(CLOCKS_PER_SEC));
		return ;
	}

	// Making list even by storing stray one
	if (cpyListValues.size() % 2 == 1)
	{
		hasStray = true;
		stray = cpyListValues.back();
		cpyListValues.pop_back();
	}

	// Making pairs
	it = cpyListValues.begin();
	while (it != cpyListValues.end())
	{
		std::list<int>				temp;
		std::list<int>::iterator	next = ++it;
		--it;
		if (*it > *(next))
		{
			temp.push_back(*it);
			temp.push_back(*(next));
		}
		else
		{
			temp.push_back(*(next));
			temp.push_back(*it);
		}
		pairs.push_back(temp);
		std::advance(it, 2);
	}

	// Sorting pairs with mergesort
	mergeSortList(pairs.begin(), pairs.end());
	itPair = pairs.begin();
	while (itPair != pairs.end())
	{
		sorted.push_back(itPair->front());
		waitList.push_back(itPair->back());
		++itPair;
	}

	// First element in waitList is lower than the first element of sorted
	// so it's safe to push it to the front of sorted.
	sorted.push_front(waitList.front());
	waitList.pop_front();

	bsLimit = 2;
	while (!waitList.empty())
	{
		it = sorted.begin();
		std::advance(it, bsLimit);
		it = lower_bound_list(sorted.begin(), it, waitList.front());
		sorted.insert(it, waitList.front());
		waitList.pop_front();
		bsLimit += 2;
	}

	if (hasStray)
	{
		it = lower_bound_list(sorted.begin(), sorted.end(), stray);
		sorted.insert(it, stray);
	}

	_sortedListValues = sorted;
	end = clock();
	_listTimeTaken = double((end - start) / double(CLOCKS_PER_SEC));
}

bool PmergeMe::customPairComparisonList(const std::list<int> &a,
		const std::list<int> &b)
{
	return (a.front() < b.front());
}

bool PmergeMe::customPairComparisonDeque(const std::deque<int> &a,
		const std::deque<int> &b)
{
	return (a.front() < b.front());
}
