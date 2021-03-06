// Count Words in a String.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


int main()
{
	std::cout << "Enter file name or input directly." << std::endl;
	std::wstring input;
	std::getline(std::wcin, input);
	std::wifstream file(input);
	size_t sum = 0;
	if (!file)
	{
		std::wistringstream buf(input);
		while (buf >> input)
			sum++;
	}
	else
		while (file >> input)
			sum++;

	std::cout << "Words: " << sum << std::endl;


	getchar();
    return 0;
}