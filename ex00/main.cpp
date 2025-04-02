/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:43:18 by ewu               #+#    #+#             */
/*   Updated: 2025/04/02 14:48:22 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "Input.txt file needed to calculate!\n";
		return 1;	
	}
	try
	{
		BitcoinExchange test1;
		test1.readInput(av[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}
