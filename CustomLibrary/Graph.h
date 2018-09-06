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
	using Edge = std::pair<double, std::array<Node, 2>>;

	Graph() {}
	Graph(Node nodes, std::vector<Edge> edges)
		: m_nodes{ std::move(nodes) }, m_vertercies{ std::vector<Vertex>(m_nodes) }, m_edges{ std::move(edges) }
	{
		for (const auto &val : m_edges)
		{
			m_vertercies[val.second[0]].push_back({ val.first, val.second[1] });
			m_vertercies[val.second[1]].push_back({ val.first, val.second[0] });
		}
	}
	Graph(Node nodes)
		: m_nodes{ std::move(nodes) }, m_vertercies{ std::vector<Vertex>(m_nodes) } {}

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
	void addEdge(Edge edge)
	{
		const Node m = std::max(edge.second[0], edge.second[1]);
		if (m > m_vertercies.size())
			m_vertercies.resize(m + 1);
		m_vertercies[edge.second[0]].push_back({ edge.first, edge.second[1] });
		m_vertercies[edge.second[1]].push_back({ edge.first, edge.second[0] });
		m_edges.push_back(std::move(edge));
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
			for (const auto &x : m_vertercies[current])
				if (dist[x.second] > dist[current] + x.first)
				{
					dist[x.second] = dist[current] + x.first;
					pq.push({ dist[x.second], x.second });
				}
		}
		return dist[destination];
	}

	Graph minimumSpanningTree()
	{
		std::sort(m_edges.begin(), m_edges.end());
		std::vector<Node> id; id.reserve(m_nodes);
		for (size_t i = 0; i < id.capacity(); i++)
			id.push_back(i);
		
		Graph gph(m_nodes);
		static auto root = [&](Node x) { for (; id[x] != x; x = id[x]) id[x] = id[id[x]]; return x; };

		for (const auto &val : m_edges)
		{
			const Node x = root(val.second[0]), y = root(val.second[1]);
			if (x != y)
				gph.addEdge(val), id[x] = id[y];
		}

		return gph;
	}

private:
	using Link = std::pair<double, Node>;
	using Vertex = std::vector<Link>;
	Node m_nodes;
	std::vector<Vertex> m_vertercies;
	std::vector<Edge> m_edges;

	std::vector<bool> goThrough(std::vector<bool> check, const Node &node = 0) const
	{
		check[node] = true;
		for (const auto &val : m_vertercies[node])
			if (!check[val.second])
				check = goThrough(std::move(check), val.second);
		return check;
	}
};