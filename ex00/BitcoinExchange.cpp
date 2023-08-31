#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	int	i;

	std::ifstream resFile;
	std::string myline;
	resFile.open("data.csv");
	if (resFile.is_open())
	{
		vector<string> row;
		i = 0;
		while (myfile)
		{
			row.clear();
			std::getline(myfile, myline);
			stringstream s(line);
			while (getline(s, word, ','))
			{
				row.push_back(word);
			}
			if (i != 0)
				_database[row[0]] = atod(row[1]);
			i++;
		}
	}
	else
		throw BitcoinExchange::FileCreationError();
}

bool	checkDate(std::string &dateString)
{
	std::vector<std::string>
}

bool	isDateAndtimeValid(std::vector<int> time)
{
	if (time[1] > 12)
		return (false);
	if (time[2] > 31)
		return (false);
	if (time[2] == 31 and (time[1] == 4 or time[1] == 6 or time[1] == 9 or time[1] == 11))
		return (false);
	if (time[1] == 2)
	{
		if (time[2] > 29)
			return (false);
		if (time[2] == 29 and ((time[0] % 100) % 4 != 0))
			return (false);
	}
	return (true);
}

void	handleLine(std::vector<std::string> &line)
{
	if (line.size() != 2)
		std::cerr << "Error: columns doesn't seem right" << std::endl;
	else
	{

	}
}

void BitcoinExchange::processFile(const std::string &filePath)
{
	int	i;

	std::ifstream resFile;
	std::string myline;
	resFile.open(filePath);
	if (resFile.is_open())
	{
		std::vector<std::string> row;
		i = 0;
		while (myfile)
		{
			row.clear();
			std::getline(myfile, myline);
			stringstream s(line);
			while (getline(s, word, '|'))
			{
				row.push_back(word);
			}
			i++;
		}
	}
	else
		throw BitcoinExchange::FileCreationError();
}
