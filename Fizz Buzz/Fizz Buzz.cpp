// Fizz Buzz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>


int main()
{
	for (size_t i = 1; i <= 100; i++)
	{
		if (i % 3 == 0 && i % 5 == 0)
			std::cout << "FizzBuzz";
		else if (i % 3 == 0)
			std::cout << "Fizz";
		else if (i % 5 == 0)
			std::cout << "Buzz";
		else
			std::cout << i;
		std::cout << "\n";
	}


	getchar();
    return 0;
}