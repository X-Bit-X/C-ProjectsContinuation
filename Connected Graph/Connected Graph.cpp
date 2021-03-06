// Connected Graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include <Graph.h>


int main()
{
	const Graph nonCon(5, { { 0, { 1, 3 } },{ 0, { 4, 3 } },{ 0, { 2, 0 } } });
	std::cout << std::boolalpha << nonCon.isConnected() << std::endl;

	const Graph Con(5, { { 0, { 1, 3 } },{ 0, { 4, 3 } },{ 0, { 2, 0 } },{ 0, { 3, 2 } } });
	std::cout << Con.isConnected() << std::endl;


	getchar();
    return 0;
}