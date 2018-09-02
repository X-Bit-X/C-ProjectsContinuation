#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

#include "Error.h"

using Node = unsigned int;
using Edge = std::array<Node, 2>;
class Graph
{
public:
	Graph(Node nodes, const std::vector<Edge> &edges)
		: m_nodes{ std::move(nodes) }, m_links{ std::vector<Links>(m_nodes) }
	{
		for (const auto &edge : edges)
		{
			m_links[edge[0]].push_back(edge[1]); 
			m_links[edge[1]].push_back(edge[0]);
		}
	}

	friend std::ostream& operator<<(std::ostream &out, const Graph &a)
	{
		out << "[( ";
		for (int it = 0; it < a.m_nodes; it++)
			out << it << ' ';
		out << ')';
		for (const auto &it : a.m_links)
		{
			out << "{ ";
			for (const auto &it2 : it)
				out << it2 << ' ';
			out << '}';
		}
		out << ']';
		return out;
	}

	void setNodes(const Node &nodeLim) { m_nodes = nodeLim; m_links.resize(nodeLim); }
	void addEdge(const Edge &edge)
	{
		const Node m = std::max(edge[0], edge[1]);
		if (m > m_links.size())
			m_links.resize(m + 1);
		m_links[edge[0]].push_back(edge[1]);
		m_links[edge[1]].push_back(edge[0]);
	}

	//0 -> none, 1 -> path, 2 -> circle and path
	short eulerian() const
	{
		if (!isConnected())
			return 0;

		unsigned int odd = 0;
		for (const auto &link : m_links)
			if (link.size() & 1)
				odd++;

		return odd == 0 ? 2 : odd == 2 ? 1 : 0;
	}

	bool isConnected() const
	{
		for (const auto &val : goThrough(std::vector<bool>(m_nodes)))
			if (!val)
				return false;
		return true;
	}

private:
	using Links = std::vector<Node>;
	Node m_nodes;
	std::vector<Links> m_links;

	std::vector<bool> goThrough(std::vector<bool> check, const Node &node = 0) const
	{
		check[node] = true;
		for (const auto &val : m_links[node])
			if (!check[val])
				check = goThrough(std::move(check), val);
		return check;
	};
};