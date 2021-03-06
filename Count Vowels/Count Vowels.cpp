// Count Vowels.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <string>


int main()
{
	std::cout << "Enter a sentence." << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::istringstream formater(input);

	std::queue<std::string> sentence;
	while (formater)
	{
		std::string buf;
		formater >> buf;
		if (!buf.empty())
			sentence.push(std::move(buf));
	}

	size_t result = 0;
	for (; !sentence.empty(); sentence.pop())
		for (auto i = sentence.front().begin(); i != sentence.front().end(); i++)
			if ((i == sentence.front().begin() && (*i == 'y' || *i == 'Y')) || [&i]() constexpr { for (const char &val : "aeiouAEIOU") if (*i == val) return true; return false; }())
				result++;

	std::cout << result << std::endl;


	getchar();
    return 0;
}