// Dijkstra’s Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include <Graph.h>


int main()
{
	const Graph test(9, 
		{
			{ 4, { 0, 1 } },{ 8, { 0, 7 } },{ 11, { 1, 7 } },
			{ 8, { 1, 2 } },{ 7, { 7, 8 } },{ 1, { 7, 6 } },
			{ 2, { 2, 8 } },{ 6, { 8, 6 } },{ 4, { 2, 5 } },
			{ 2, { 6, 5 } },{ 7, { 2, 3 } },{ 14, { 3, 5 } },
			{ 9, { 3, 4 } },{ 10, { 5, 4 } }
		});
	std::cout << test.dijkstra(0, 4) << "\n" << test.dijkstra(1, 7) << "\n" << test.dijkstra(5, 5) << "\n" << std::endl;

	const Graph testInf(5,
		{
			{ 4, { 0, 2 } },{ 7, { 1, 3 } },{ 10, { 3, 4 } }
		});
	std::cout << testInf.dijkstra(0, 4) << std::endl;


	getchar();
    return 0;
}