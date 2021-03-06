// Minimum Spanning Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include <Graph.h>


int main()
{
	Graph test(5, 
		{
			{ 1, { 0, 1 } },{ 7, { 0, 2 } },{ 5, { 1, 2 } },{ 4, { 1, 3 } },
			{ 3, { 1, 4 } },{ 6, { 2, 3 } },{ 2, { 3, 4 } }
		});
	Graph ex(4, { { 0,{ 0, 1 } },{ 0,{ 1, 2 } },{ 0,{ 2, 3 } } });
	Graph path(5, { { 0,{ 1, 2 } },{ 0,{ 2, 0 } },{ 0,{ 1, 0 } },{ 0,{ 0, 3 } },{ 0,{ 3, 4 } } });
	Graph circle(5, { { 0,{ 1, 2 } },{ 0,{ 2, 0 } },{ 0,{ 1, 0 } },{ 0,{ 0, 3 } },{ 0,{ 3, 4 } },{ 0,{ 0, 4 } } });
	Graph non(5, { { 0,{ 1, 2 } },{ 0,{ 2, 0 } },{ 0,{ 1, 0 } },{ 0,{ 0, 3 } },{ 0,{ 3, 4 } },{ 0,{ 1, 3 } } });
	Graph test2(9,
		{
			{ 4,{ 0, 1 } },{ 8,{ 0, 7 } },{ 11,{ 1, 7 } },
		{ 8,{ 1, 2 } },{ 7,{ 7, 8 } },{ 1,{ 7, 6 } },
		{ 2,{ 2, 8 } },{ 6,{ 8, 6 } },{ 4,{ 2, 5 } },
		{ 2,{ 6, 5 } },{ 7,{ 2, 3 } },{ 14,{ 3, 5 } },
		{ 9,{ 3, 4 } },{ 10,{ 5, 4 } }
		});
	Graph testInf(5,
		{
			{ 4,{ 0, 2 } },{ 7,{ 1, 3 } },{ 10,{ 3, 4 } }
		});
	Graph nonCon(5, { { 0,{ 1, 3 } },{ 0,{ 4, 3 } },{ 0,{ 2, 0 } } });
	Graph Con(5, { { 0,{ 1, 3 } },{ 0,{ 4, 3 } },{ 0,{ 2, 0 } },{ 0,{ 3, 2 } } });


	std::cout << test.minimumSpanningTree() << "\n" << ex.minimumSpanningTree() << "\n" << path.minimumSpanningTree() << "\n"
		<< circle.minimumSpanningTree() << "\n" << non.minimumSpanningTree() << "\n" << test2.minimumSpanningTree() << "\n"
		<< testInf.minimumSpanningTree() << "\n" << nonCon.minimumSpanningTree() << "\n" << Con.minimumSpanningTree() << std::endl;


	getchar();
    return 0;
}