// Graph from links.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

#include <Graph.h>


int main()
{
	Graph ex({ 0, 1, 2, 3, 4, 5 }, { { 0, 1 }, { 2, 3 }, { 4, 5 } });
	std::cout << ex << std::endl;

	getchar();
    return 0;
}