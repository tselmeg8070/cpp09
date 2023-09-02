#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP
# define K 10
# include <ctime>
# include <cmath>
# include <iostream>
# include <deque>
# include <queue>
# include <set>
# include <iterator>
# include <algorithm>
# include <sstream>
# include <string>
# include <list>

class	PmergeMe {


	private:
		std::string			_original;
		std::deque<int>		_dequeValues;
		std::list<int>		_queueValues;
	public:
		PmergeMe(const std::string &str);
		PmergeMe(const PmergeMe &t);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &t);

		void	sortDeque();
		void	sortQueue();

		template <class Iterator>
		void	insertionSort(Iterator begin, Iterator end)
		{
			std::iter_swap(begin, std::min_element(begin, end));
			for (Iterator b = begin; ++b < end; begin = b)
				for (Iterator c = b; *c < *begin; --c, --begin)
					std::iter_swap(begin, c);
		}

		template <class Iterator>
		void mergeSort(Iterator begin, Iterator end) {
			if (end - begin <= K)
				insertionSort(begin, end);
			else
			{
				Iterator middle = begin + (end - begin) / 2;
				mergeSort(begin, middle);
				mergeSort(middle, end);
				std::inplace_merge(begin, middle, end);
			}
		}
};

#endif
