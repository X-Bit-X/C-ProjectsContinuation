#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <queue>

#include "Error.h"

class Graph
{
public:
	using Node = unsigned int;
	using Edge = std::pair<std::array<Node, 2>, double>;

	Graph(Node nodes, const std::vector<Edge> &edges)
		: m_nodes{ std::move(nodes) }, m_vertercies{ std::vector<Vertex>(m_nodes) }
	{
		for (const auto &val : edges)
		{
			m_vertercies[val.first[0]].push_back({ val.second, val.first[1] });
			m_vertercies[val.first[1]].push_back({ val.second, val.first[0] });
		}
	}

	friend std::ostream& operator<<(std::ostream &out, const Graph &a)
	{
		out << "[( ";
		for (int it = 0; it < a.m_nodes; it++)
			out << it << ' ';
		out << ')';
		for (const auto &it : a.m_vertercies)
		{
			out << "{ ";
			for (const auto &it2 : it)
				out << it2.second << ' ';
			out << '}';
		}
		out << ']';
		return out;
	}

	void setNodes(const Node &nodeLim) { m_nodes = nodeLim; m_vertercies.resize(nodeLim); }
	void addEdge(const Edge &edge)
	{
		const Node m = std::max(edge.first[0], edge.first[1]);
		if (m > m_vertercies.size())
			m_vertercies.resize(m + 1);
		m_vertercies[edge.first[0]].push_back({ edge.second, edge.first[1] });
		m_vertercies[edge.first[1]].push_back({ edge.second, edge.first[0] });
	}

	//0 -> none, 1 -> path, 2 -> circle and path
	short eulerian() const
	{
		if (!isConnected())
			return 0;

		unsigned int odd = 0;
		for (const auto &link : m_vertercies)
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

	double dijkstra(const Node &start, const Node &destination) const
	{
		std::priority_queue<Link, std::vector<Link>, std::greater<Link>> pq;
		std::vector<double> dist(m_nodes, HUGE_VAL);

		pq.push({ 0, start });
		dist[start] = 0;

		while (!pq.empty())
		{
			const int current = pq.top().second;
			pq.pop();
			for (auto x : m_vertercies[current])
				if (dist[x.second] > dist[current] + x.first)
				{
					dist[x.second] = dist[current] + x.first;
					pq.push({ dist[x.second], x.second });
				}
		}
		return dist[destination];
	}

private:
	using Link = std::pair<double, Node>;
	using Vertex = std::vector<Link>;
	Node m_nodes;
	std::vector<Vertex> m_vertercies;

	std::vector<bool> goThrough(std::vector<bool> check, const Node &node = 0) const
	{
		check[node] = true;
		for (const auto &val : m_vertercies[node])
			if (!check[val.second])
				check = goThrough(std::move(check), val.second);
		return check;
	}
};