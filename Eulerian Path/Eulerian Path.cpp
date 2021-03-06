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

	const Graph path(5, { { 0, { 1, 2 } },{ 0, { 2, 0 } },{ 0, { 1, 0 } },{ 0, { 0, 3 } },{ 0, { 3, 4 } } });
	std::cout << interpret(path.eulerian()) << std::endl;

	const Graph circle(5, { { 0, { 1, 2 } },{ 0, { 2, 0 } },{ 0, { 1, 0 } },{ 0, { 0, 3 } },{ 0, { 3, 4 } },{ 0, { 0, 4 } } });
	std::cout << interpret(circle.eulerian()) << std::endl;

	const Graph non(5, { { 0, { 1, 2 } },{ 0, { 2, 0 } },{ 0, { 1, 0 } },{ 0, { 0, 3 } },{ 0, { 3, 4 } },{ 0, { 1, 3 } } });
	std::cout << interpret(non.eulerian()) << std::endl;


	getchar();
    return 0;
}