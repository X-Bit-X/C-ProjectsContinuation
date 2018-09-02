// Eulerian Path.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include <Graph.h>


int main()
{
	auto interpret = [](short result) constexpr 
	{ 
		switch (result)
		{
		case 0: return "not Eulerian";
		case 1: return "Eulerian path";
		case 2: return "Eulerian circle";
		}
	};

	Graph path(5, { { 1, 2 },{ 2, 0 },{ 1, 0 },{ 0, 3 },{ 3, 4 } });
	std::cout << interpret(path.eulerian()) << std::endl;

	Graph circle(5, { { 1, 2 },{ 2, 0 },{ 1, 0 },{ 0, 3 },{ 3, 4 },{ 0, 4 } });
	std::cout << interpret(circle.eulerian()) << std::endl;

	Graph non(5, { { 1, 2 },{ 2, 0 },{ 1, 0 },{ 0, 3 },{ 3, 4 },{ 1, 3 } });
	std::cout << interpret(non.eulerian()) << std::endl;


	getchar();
    return 0;
}