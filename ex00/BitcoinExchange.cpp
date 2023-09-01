#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	int	i;

	std::ifstream				resFile;
	std::string					myline;
	std::string					word;
	std::vector<std::string>	row;

	resFile.open("data.csv");
	if (resFile.is_open())
	{
		i = 0;
		while (resFile)
		{
			row.clear();
			std::getline(resFile, myline);
			std::stringstream s(myline);
			while (std::getline(s, word, ','))
			{
				row.push_back(word);
			}
			if (i != 0)
				_database[row[0]] = std::atof(row[1].c_str());
			i++;
		}
		resFile.close();
	}
	else
		throw std::runtime_error("Error: could not open database.");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &t) : _database(t._database)
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &t)
{
	if (this != &t)
		_database = t._database;
	return (*this);
}

bool	isDateAndtimeValid(std::vector<int> &time)
{
	if (time.size() != 3)
		return (false);
	if (time[0] < 2000 || time[0] > 10000)
		return (false);
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

void	BitcoinExchange::handleLine(std::vector<std::string> &line)
{
	std::string						word;
	float							val;
	std::map<std::string, float>::iterator	itlow;

	if (line.size() != 0)
	{
		std::vector<int> dates;
		std::stringstream s(line[0]);
		while (getline(s, word, '-'))
			dates.push_back(std::atoi(word.c_str()));
		if (isDateAndtimeValid(dates))
		{
			if (line.size() != 2)
				std::cerr << "Error: bad row => " << line[0] << std::endl;
			else
			{
				val = std::atof(line[1].c_str());
				if (val < 0)
					std::cerr << "Error: not a positive number" << std::endl;
				else if (val > 1000)
					std::cerr << "Error: too large a number." << std::endl;
				else if ((line[1] == "0.0" || line[1] == "0") && val == 0)
					std::cout << line[0] << " => " << line[1] << " = 0.0" << std::endl;
				else if ((line[1] == "0.0" || line[1] == "0") && val != 0)
					std::cerr << "Error: bad input => " << line[1] << std::endl;
				else
				{
					itlow = _database.lower_bound(line[0]);
					if (_database.begin() == itlow && line[0].compare(itlow->first) < 0)
						std::cerr << "Error: bitcoin doesn't exist here" << std::endl;
					else
						std::cout << line[0] << " => " << line[1] << " = " << (itlow->second * val) << std::endl;
				}
			}
		}
		else
			std::cerr << "Error: bad input => " << line[0] << std::endl;
	}
}

std::string	stripSpaces(std::string &s)
{
	std::string res = "";

	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
			res += s[i];
	}
	return (res);
}

void BitcoinExchange::processFile(const std::string &filePath)
{
	int	i;

	std::ifstream				resFile;
	std::string					myline;
	std::string					word;
	std::vector<std::string>	row;

	resFile.open(filePath.c_str());
	if (resFile.is_open())
	{
		i = 0;
		while (resFile)
		{
			row.clear();
			std::getline(resFile, myline);
			std::stringstream s(myline);
			while (getline(s, word, '|'))
				row.push_back(stripSpaces(word));
			if (i != 0)
				handleLine(row);
			i++;
		}
		resFile.close();
	}
	else
		throw std::runtime_error("Error: could not open file.");
}
