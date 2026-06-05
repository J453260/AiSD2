#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <cassert>

#include "edge.hpp"
#include "basegraph.hpp"
#include "iterator.hpp"

class Graph : public BaseGraph<int>
{
    bool directed;
    std::vector<std::vector<float>> adj_matrix;
public:
    Graph(int n, bool d=false) : directed(d)
    {
        adj_matrix = std::vector<std::vector<float>>(n, std::vector<float>(n, 0.0f));
    }
    ~Graph()
    {
        for (auto& item : adj_matrix)
            item.clear();
        adj_matrix.clear();
    }
    bool is_directed() const override
    {
        return directed;
    }
    int v() const override
    {
        return adj_matrix.size();
    }
    int e() const override
    {
        int counter = 0;
        for (int u = 0; u < v(); u++)
            for (int w = 0; w < v(); w++)
                if (adj_matrix[u][w] > 0.0f) counter++;
        return (directed ? counter : counter / 2);
    }
    int degree(int u) override
    {
        assert(0 <= u && u < v());
        int counter = 0;
        for (int w = 0; w < v(); w++)
        {
            if (adj_matrix[u][w] > 0.0f) counter++;
            if (adj_matrix[w][u] > 0.0f) counter++;
        }
        return (directed ? counter : counter / 2);
    }
    int outdegree(int u) override
    {
        int counter = 0;
        for (int w = 0; w < v(); w++)
            if (adj_matrix[u][w] > 0.0f) counter++;
        return counter;
    }
    int indegree(int u) override
    {
        int counter = 0;
        for (int w = 0; w < v(); w++)
            if (adj_matrix[w][u] > 0.0f) counter++;
        return counter;
    }
    void add_node(int u) override
    {
        assert(0 <= u && u < v());
    }
    void del_node(int u) override
    {
        for (int w = 0; w < v(); w++)
        {
            adj_matrix[u][w] = 0.0f;
            adj_matrix[w][u] = 0.0f;
        }
    }
    bool has_node(int u) const override
    {
        return (0 <= u && u < v());
    }
    void add_edge(int u, int w, float weight=1.0f) override
    {
        if (adj_matrix[u][w] == 0.0f)
        {
            adj_matrix[u][w] = weight;
            if (!directed && adj_matrix[w][u] == 0.0f)
                adj_matrix[w][u] = weight;
        }
    }
    void add_edge(Edge<int> edge) override
    {
        add_edge(edge.source, edge.target);
    }
    void del_edge(int u, int w) override
    {
        if (adj_matrix[u][w] > 0.0f)
        {
            adj_matrix[u][w] = 0.0f;
            if (!directed)
                adj_matrix[w][u] = 0.0f;
        }
    }
    void del_edge(Edge<int> edge) override
    {
        del_edge(edge.source, edge.target);
    }
    bool has_edge(int u, int w) const override
    {
        return adj_matrix[u][w] > 0.0f;
    }
    bool has_edge(Edge<int> edge) const override
    {
        return adj_matrix[edge.source][edge.target] > 0.0f;
    }
    float weight(int u, int w) const override
    {
        return adj_matrix[u][w];
    }
    float weight(Edge<int> edge) const override
    {
        return adj_matrix[edge.source][edge.target];
    }
    void clear() override
    {
        for (int u = 0; u < v(); u++)
            for (int w = 0; w < v(); w++)
                adj_matrix[u][w] = 0.0f;
    }
    void display() const override
    {
        for (const auto& row : adj_matrix)
        {
            for (const auto& cell : row)
                std::cout << cell << " ";
            std::cout << std::endl;
        }
    }

    class NodeIterator : public Iterator<int>
    {
        Graph *gptr;
        int node;
    public:
        NodeIterator(Graph *gp) : gptr(gp), node(0) {}
        NodeIterator(Graph *gp, int u) : gptr(gp), node(u) {}
        ~NodeIterator() {}
        NodeIterator(const NodeIterator& other)
        {
            gptr = other.gptr;
            node = other.node;
        }
        NodeIterator& operator=(const NodeIterator& other)
        {
            if (this == &other) return *this;
            gptr = other.gptr;
            node = other.node;
            return *this;
        }
        NodeIterator& operator++()
        {
            ++node;
            return *this;
        }
        NodeIterator operator++(int)
        {
            NodeIterator it = *this;
            ++node;
            return it;
        }
        bool operator==(const NodeIterator& other) const
        {
            return (gptr == other.gptr) && (node == other.node);
        }
        bool operator!=(const NodeIterator& other) const
        {
            return !(*this == other);
        }
        int operator*() const override
        {
            return node;
        }
    };
    NodeIterator node_begin()
    {
        return NodeIterator(this, 0);
    }
    NodeIterator node_end()
    {
        return NodeIterator(this, v());
    }

    class EdgeIterator : public Iterator<Edge<int>>
    {
        Graph *gptr;
        int r, c;
        void advance()
        {
            while (true)
            {
                ++c;
                if (c == gptr->v())
                {
                    ++r;
                    c = 0;
                }
                if (r == gptr->v())
                {
                    c = gptr->v();
                    break;
                }
                if (gptr->has_edge(r, c) && (gptr->is_directed() || (r < c))) break;
            }
        }
    public:
        EdgeIterator(Graph *gp) : gptr(gp), r(0), c(0)
        {
            advance();
        }
        EdgeIterator(Graph *gp, int u, int w) : gptr(gp), r(u), c(w) {}
        ~EdgeIterator() {}
        EdgeIterator(const EdgeIterator& other)
        {
            gptr = other.gptr;
            r = other.r;
            c = other.c;
        }
        EdgeIterator& operator=(const EdgeIterator& other)
        {
            if (this == &other) return *this;
            gptr = other.gptr;
            r = other.r;
            c = other.c;
            return *this;
        }
        EdgeIterator& operator++()
        {
            advance();
            return *this;
        }
        EdgeIterator operator++(int)
        {
            EdgeIterator it = *this;
            advance();
            return it;
        }
        bool operator==(const EdgeIterator& other) const
        {
            return (gptr == other.gptr) && (r == other.r) && (c == other.c);
        }
        bool operator!=(const EdgeIterator& other) const
        {
            return !(*this == other);
        }
        Edge<int> operator*() const override
        {
            return Edge<int>(r, c, gptr->weight(r, c));
        }
    };
    EdgeIterator edge_begin()
    {
        return EdgeIterator(this);
    }
    EdgeIterator edge_end()
    {
        return EdgeIterator(this, v(), v());
    }

    class AdjacentIterator : public Iterator<int>
    {
        Graph *gptr;
        int r, c;
        void advance()
        {
            while (true)
            {
                ++c;
                if ((c == gptr->v()) || (gptr->has_edge(r, c))) break;
            }
        }
    public:
        AdjacentIterator(Graph *gp, int u) : gptr(gp), r(u), c(-1)
        {
            advance();
        }
        AdjacentIterator(Graph *gp, int u, int w) : gptr(gp), r(u), c(w) {}
        ~AdjacentIterator() {}
        AdjacentIterator(const AdjacentIterator& other)
        {
            gptr = other.gptr;
            r = other.r;
            c = other.c;
        }
        AdjacentIterator& operator=(const AdjacentIterator& other)
        {
            if (this == &other) return *this;
            gptr = other.gptr;
            r = other.r;
            c = other.c;
            return *this;
        }
        AdjacentIterator& operator++()
        {
            advance();
            return *this;
        }
        AdjacentIterator operator++(int)
        {
            AdjacentIterator it = *this;
            advance();
            return it;
        }
        bool operator==(const AdjacentIterator& other) const
        {
            return (gptr == other.gptr) && (r == other.r) && (c == other.c);
        }
        bool operator!=(const AdjacentIterator& other) const
        {
            return !(*this == other);
        }
        int operator*() const override
        {
            return c;
        }
    };
    AdjacentIterator adj_begin(int u)
    {
        return AdjacentIterator(this, u);
    }
    AdjacentIterator adj_end(int u)
    {
        return AdjacentIterator(this, u, v());
    }
};

#endif // GRAPH_HPP
