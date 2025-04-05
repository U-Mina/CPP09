/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:29:26 by ewu               #+#    #+#             */
/*   Updated: 2025/04/05 14:38:51 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN
{
private:
	std::string input; //input line, read one-by-one, ' ' as delim
	std::stack<double> nbrStack;
public:
	// RPN();
	RPN(const std::string& _input);
	~RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	bool isOp(const std::string& token) const;
	double doOp(double n1, double n2, const std::string& op) const; //push res back to slack
	double mainRPN(); //main entry, check_token, push/pop(), doop, and return res
};

#endif