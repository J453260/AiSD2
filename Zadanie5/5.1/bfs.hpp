// bfs.hpp
#include <unordered_map>
#include <vector>
#include <queue>
template<typename T, typename G> // node type, graph type
class BFS
{
    G& graph;
    std::unordered_map<T, bool> visited;
public:
    std::vector<T> preorder;
    std::vector<T> postorder;
    BFS(G& g) : graph(g)
    {
        for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it)
        {
            visited[*n_it] = false;
        }
    }
    ~BFS() = default; // destruktor
    void run(T u = T())
    {
        if (u != T())   // badamy jedną składową spójną
        {
            visit(u);
        }
        else
        {
            for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it)
            {
                if (!visited[*n_it])
                    visit(*n_it);
            } // for
        } // if
    }

    void visit(T s)
    {
        std::queue<T> q;
        visited[s] = true;
        q.push(s);
        preorder.push_back(s); // odwiedzony na wejściu

        while (!q.empty())
        {
            T u = q.front();
            q.pop();

            for (T neighbor : graph.neighbors(u))
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    preorder.push_back(neighbor);
                    q.push(neighbor);
                }
            }
            postorder.push_back(u); // odwiedzony po przetworzeniu
        }
    }
};
// Usage:
// auto algorithm = BFS<int,Graph>(graph); // macierz sąsiedztwa
// auto algorithm = BFS<char,Graph<char>>(graph); // lista sąsiedztwa
// algorithm.run(start_node);
// for (auto& node : algorithm.preorder) { ... }
// for (auto& node : algorithm.postorder) { ... }
