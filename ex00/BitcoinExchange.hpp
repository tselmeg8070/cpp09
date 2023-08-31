#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP
# include <map>
# include <string>
# include <iostream>
# include <fstream>

class BitcoinExchange
{
	private:
		map<std::string, double> _database;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &t);
		~BitcoinExchange();
		BitcoinExchange &operator=(const BitcoinExchange &t);

		void	processFile(const std::string &filePath);
};

#endif
