// Check if Palindrome.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <ios>


int main()
{
	std::cout << "Enter a string." << std::endl;
	std::string word;
	std::getline(std::cin, word);

	std::string pal(word);
	std::reverse(pal.begin(), pal.end());

	std::cout << std::boolalpha << (pal == word ? true : false);


	getchar();
    return 0;
}