// Pig Latin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <sstream>
#include <queue>


int main()
{
	const std::string consonants = "bcdfghjklmnpqrstvwxyz";
	const std::string vowels = "aeiouAEIOU";

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

	for (; !sentence.empty(); sentence.pop())
	{
		std::string constantCluster;
		for (auto i = sentence.front().begin(); i != sentence.front().end(); i++)
			if (i == sentence.front().begin() && *i == 'y' || *i == 'Y')
				constantCluster.push_back(*i);
			else if (![&i]() constexpr { for (const char &val : "aeiouAEIOU") if (*i == val) return true; return false; }())
				constantCluster.push_back(*i);
			else
			{
				sentence.front().erase(sentence.front().begin(), i);
				break;
			}

		sentence.front().append(constantCluster.empty() ? "-yay" : '-' + std::move(constantCluster) + "ay");
		std::cout << sentence.front() << ' ';
	}


	getchar();
    return 0;
}