#ifndef NOTATIONCONVERTER_H

#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"
#include "Deque.h"
#include "DLinkedList.h"


class NotationConverter : public NotationConverterInterface
{
public:
	std::string postfixToInfix(std::string inStr);
	std::string postfixToPrefix(std::string inStr);

	std::string infixToPostfix(std::string inStr);
	std::string infixToPrefix(std::string inStr);

    std::string prefixToInfix(std::string inStr);
	std::string prefixToPostfix(std::string inStr);

	//////////////////////////////////////////////
	bool isOperator(const std::string& s);
	int prec(const std::string& s);
	bool isLetter(const std::string& s);
	bool isSpace(const std::string& s);
	//bool isWrongInput(const std::string& s); 

};

#endif