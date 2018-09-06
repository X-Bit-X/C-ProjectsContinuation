// Graph from links.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

#include <Graph.h>


int main()
{
	const Graph ex(4, { { 0, { 0, 1 } }, { 0, { 1, 2 } }, { 0, { 2, 3 } } });
	std::cout << ex << std::endl;

	getchar();
    return 0;
}