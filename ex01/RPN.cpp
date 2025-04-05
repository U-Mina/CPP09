/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:39:48 by ewu               #+#    #+#             */
/*   Updated: 2025/04/05 15:00:06 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

// RPN::RPN() {}
RPN::RPN(const std::string& _input) : input(_input) {} //input = av[1]
RPN::~RPN() {}
RPN::RPN(const RPN& other)
{
	this->input = other.input;
}
RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		input = other.input;
	return *this;
}

//real functional part
bool RPN::isOp(const std::string& token) const //+-*/
{
	if (token == "+" || token == "-" || token == "*" || token == "/")
		return true;
	return false;
}
//if create enum type of operator, can use switch-case
double RPN::doOp(double n1, double n2, const std::string& op) const
{
	if (op == "+")
		return (n1 + n2);
	if (op == "-")
		return (n1 - n2);
	if (op == "*")
		return (n1 * n2);
	if (op == "/")
	{
		if (n2 == 0)
			throw std::runtime_error("divided by 0!");
		return (n1 / n2);
	}
	throw std::runtime_error("invalid operator!");
}

/**
 * stringstream ss >> token:
 * >>: extraction operator! in here, it reads 
 * whihespace-separated(delim as ' ') token from ss
 */
double RPN::mainRPN()
{
	std::stringstream tmp(input);
	std::string token;
	// while (std::getline(tmp, token, ' ')), this will not skip whitespace but makes it a token too
	while (tmp >> token)
	{
		if (isOp(token)) //if it's operator, pop top 2 nbr and doOp()
		{
			if (nbrStack.size() < 2)
				throw std::runtime_error("not enough number is stack to do operation!");
			else
			{
				double n2 = nbrStack.top();
				nbrStack.pop();
				double n1 = nbrStack.top();
				nbrStack.pop();
				double res = doOp(n1, n2, token);
				nbrStack.push(res);
			}
		}
		else //is nbr, push to stack
		{
			try {
				double nbr = std::stod(token);
				if (nbr > 10)
					throw std::runtime_error("number in argument greater than 10!");
				nbrStack.push(nbr);
			}
			catch(const std::invalid_argument& e)
			{
				throw std::runtime_error("invalid input: " + token);
			}			
		}
	}
	if (nbrStack.size() != 1)
		throw std::runtime_error("too many numbers for current operator");
	return nbrStack.top();	
}
