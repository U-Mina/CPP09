/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:50:31 by ewu               #+#    #+#             */
/*   Updated: 2025/04/01 15:50:10 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream> //convert str to str-stream

BitcoinExchange::BitcoinExchange()
{
	//std::cout << "default cons called!\n";
	readDB();
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	this->_DB = other._DB;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		this->_DB = other._DB;
	return *this;
}
BitcoinExchange::~BitcoinExchange()
{
	//std::cout << "default des called!\n";
}

static bool _checkdigit(std::string& s)
{
	for (int i = 0; s[i]; ++i)
	{
		if (!isdigit(s[i]))
		return false;
	}
	return true;
}

static bool _checkFeb(int yy, int dd)
{
	if ((yy % 4 == 0 && yy % 100 != 0) || yy % 400 == 0)
	{
		if (dd > 29)
		return false;
	}
	if (dd > 28)
	return false;
	return true;
}

static bool _range(std::string& yy, std::string& mm, std::string& dd)
{
	int year = std::stoi(yy);
	if (year < 2009)
	return false;
	int month = std::stoi(mm);
	if (month < 1 || month > 12)
	return false;
	int day = std::stoi(dd);
	if (day > 31)
	return false;
	if (!_checkFeb)
	return (false);
	if (month == 4 || month == 6 || month == 9 || month == 11) //30 days month
	{
		if (day > 30)
		return false;
	}
	return true;
}

//YYYY-MM-DD
bool BitcoinExchange::validDate(const std::string& _date) const
{
	if (_date.size() > 10 || _date[4] != '-' || _date[7] != '-')
	return false;
	std::string yy = _date.substr(0, 4);
	std::string mm = _date.substr(5, 2);
	std::string dd = _date.substr(8, 2);
	if (!_checkdigit(yy) || !_checkdigit(mm) || !_checkdigit(dd)) //any non-num in date
	return false;
	if (!_range(yy, mm, dd))
	return false;
	return true;
}

bool BitcoinExchange::validValue(const std::string& _val) const
{
	unsigned int pos; //handle cases like 12.345abcdef
	try
	{
		float _rate = std::stof(_val);
		if (_rate < 0.00f)
		{
			std::cerr << "Error: not a positive number.\n";
			return false;
		}
		if (_rate > 1000.00f)
		{
			std::cerr << "Error: too large a number.\n";
			return false;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error:\nInvalid value: " << _val << "\n";
		return false;
	}
	return true;
}

void BitcoinExchange::readDB()
{
	std::ifstream csv("data.csv");
	if (!csv.is_open()) //cant open data.csv
	{
		throw std::runtime_error("Error:\nCannot open data.csv\n");
		return ;
	}
	std::string line;
	std::getline(csv, line); //read the 1st line, skip it in loop
	while (std::getline(csv, line))
	{
		std::stringstream tmp(line); //convert str to str-stream, use getline() to read (date part and value part)
		std::string tmpDate;
		std::string tmpVal;
		if (std::getline(tmp, tmpDate, ',') && std::getline(tmp, tmpVal)) // data,val
		{
			try
			{
				float _rate = std::strtof(tmpVal.c_str(), NULL);
				_DB[tmpDate] = _rate; //store date-val pair in map _DB
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			
		}
	}
	csv.close();
}
void BitcoinExchange::readInput(const std::string& inFile) const
{
	std::ifstream input(inFile);
	if (!input.is_open())
	{
		throw std::runtime_error("Error:\nCannot open input.txt\n");
		return ;
	}
	std::string line;
	
}

/**
 * std::getline(std::istream& is, std::string& str)
 * std::getline(std::istream& is, std::string& str, char delim)
 * Reads from input-stream (usually std::cin/file stream) into str until it '\n'
 * or delimiter, delim is NOT INCLUED in 'str'
 */