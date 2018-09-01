#pragma once

#include <iostream>
#include <vector>

using Node = unsigned int;
using Edge = std::vector<Node>;
class Graph
{
public:
	Graph(const std::vector<Node> &vertices, const std::vector<Edge> &edges)
		: m_vertices{ vertices }, m_edges{ edges } {}

	friend std::ostream& operator<<(std::ostream &out, const Graph &a)
	{
		out << "[(;";
		for (const auto &it : a.m_vertices)
			out << it << ';';
		out << ')';
		for (const auto &it : a.m_edges)
		{
			out << "{;";
			for (const auto &it2 : it)
				out << it2 << ';';
			out << '}';
		}
		out << ']';
		return out;
	}

private:
	std::vector<Node> m_vertices;
	std::vector<Edge> m_edges;
};