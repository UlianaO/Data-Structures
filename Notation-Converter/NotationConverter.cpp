/******************************************************
Uliana Ozerova, driver, 50%.
Daniel Shultz, navigator, 50%

This program converts between the three common mathemtical notation for arithmetic.
3 fully implemented functions: post->pref, inf->post, pref->inf.
For:
1. post->inf:   post->pref, pref-<inf
2. pref->post:  pref->inf, inf->post
3. inf->pref:   inf->post, post->pref
********************************************************/

#include <iostream>
#include "NotationConverter.h"
#include "Deque.h"

int NotationConverter::prec(const std::string& s) {

    int result;
     if (s == "+")
        result = 1;
    else if (s == "-")
        result = 2;
    else if (s == "/")
        result = 3;
    else if (s == "*")
        result = 4;
    else
        result = 0;
    return result;
}

bool NotationConverter::isOperator(const std::string& s) {

    bool result = false;
    if (s == "+" || s == "-" || s == "*" || s == "/")
        result = true;
    return result;

}

bool NotationConverter::isSpace(const std::string& s) {

    bool result = false;
    if (s == " ")
        result = true;
    return result;

}


bool NotationConverter::isLetter(const std::string& s) {
    bool result = false;
    if (s == "A" || s == "B" || s == "C" || s == "D" || s == "E" ||
        s == "F" || s == "G" || s == "H" || s == "I" || s == "J" ||
        s == "K" || s == "L" || s == "M" || s == "N" || s == "O" ||
        s == "P" || s == "Q" || s == "R" || s == "S" || s == "T" ||
        s == "U" || s == "V" || s == "W" || s == "X" || s == "Y" ||
        s == "Z" || s == "a" || s == "b" || s == "c" || s == "d" ||
        s == "e" || s == "f" || s == "g" || s == "h" || s == "i" ||
        s == "j" || s == "k" || s == "l" || s == "m" || s == "n" ||
        s == "o" || s == "p" || s == "q" || s == "r" || s == "s" ||
        s == "t" || s == "u" || s == "v" || s == "w" || s == "x" ||
        s == "y" || s == "z")
        result = true;

    return result;

}
std::string NotationConverter::postfixToInfix(std::string inStr) {
    std::string result = "";

    result = prefixToInfix(postfixToPrefix(inStr));
    return result;
}

/*********************************************************
Postfix: A B + C D + *
Prefix: * + A B + C D
Insert A, B. +: get A-B, remove A-B -> insert + A B into the deque
**********************************************************/
std::string NotationConverter::postfixToPrefix(std::string inStr) {
    LinkedDeque D;
    std::string prefix;
    std::string temp = "";

    for (unsigned i = 0; i < inStr.length(); i++) {
        temp = inStr[i];

        if (isLetter(temp)) {
            D.insertBack(temp);
        }
        else if (isOperator(temp)) {
            std::string first = D.back();
            D.removeBack();
            std::string last = D.back();
            D.removeBack();
            D.insertBack(temp + " " + last + " " + first);
            prefix = D.back();

        }
        else if (isSpace(temp)) {
            continue;
        }
        else
            throw "Error";
    }

        return prefix;

}

/***********************************************
If Letter, assign to result.
2. IF (, insert to deque
3. if ), make sure no ( after
4. if Operator, if deque is empty, jist assign to result
5. If not, check precedence. If current > deque, insert to deque
6. Assign only if less
*************************************************/
std::string NotationConverter::infixToPostfix(std::string inStr) {

    std::string postfix;        // string to return - operators and operands will be concatenated into this string
    LinkedDeque D;
    std::string temp = "";


    for (unsigned i = 0; i < inStr.length(); i++) { //goes through the string
        temp = inStr[i];
        if (isLetter(temp)) { //if letter, postfix updates with the current letter
            postfix = postfix + " " + temp;
        }

        else if (temp == "(") {
            D.insertBack(temp);
        }

        else if (temp == ")") {
            while ((D.back() != "(") && (!D.empty())) { //is the end of the expression?
                std::string a = D.back();
                postfix = postfix + " " + a;
                D.removeBack();
            }
            //if (, remove
            if (D.back() == "(") {
                D.removeBack();
            }
        }

        else if (isOperator(temp)) { // */ high prec, +- low prec
            if (D.empty()) {
                D.insertBack(temp);
            }
            else {
                if (prec(temp) >= prec(D.back())) {
                    D.insertBack(temp);
                }
                else {
                        while ((prec(temp) < prec(D.back()))) {
                            std::string b = D.back();
                            postfix = postfix + " " + b;
                            D.removeBack();
                        }
                        D.insertBack(temp);
                    }
                }
        }
        else if (isSpace(temp)) {
            continue;
        }
        else
            throw "Error";
    }

    return postfix;

}

/*inf->pref: inf->post, post->pref*/
std::string NotationConverter::infixToPrefix(std::string inStr) {

    std::string result = "";
    result = postfixToPrefix(infixToPostfix(inStr));
    return result;
}

std::string NotationConverter::prefixToInfix(std::string inStr) {

    LinkedDeque D;

    std::string prefix;
    int i = 0;
    std::string temp = "";
    for (i = inStr.length() - 1; i >= 0; i--) { // +AB, 0 1 2, length=3, i should start at 2 =>length -1
        temp = inStr[i];

        //if a letter, store in a deque untill 3d character is an operator.
        if (isLetter(temp)) {
            //prefix = prefix + temp;
            D.insertBack(temp);
        }

        //Stack has: B-A, temp = +. get A, delete, get B, delete, put temp in between
        else if (isOperator(temp)) {
            std::string first = D.back();
            D.removeBack();
            std::string last = D.back();
            D.removeBack();
            D.insertBack("(" + first + " " + temp + " " + last + ")");  //prefix = "(" + first + " " + temp + " " + last + ")";

            prefix = D.back();
        }
        else if (isSpace(temp)) {
            continue;
        }
        else
            throw "Error";
    }

    return prefix; //back of the deque has the complete expression
}

/*pref->post: pref->inf, inf->post*/
std::string NotationConverter::prefixToPostfix(std::string inStr) {
    std::string result = "";
    result = infixToPostfix(prefixToInfix(inStr));
    return result;
}

