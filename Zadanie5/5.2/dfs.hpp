// dfs.hpp
#include <unordered_map>
#include <vector>
#include <stack>

template<typename T, typename G> // node type, graph type
class DFS
{
    G& graph;
    std::unordered_map<T, bool> visited;
public:
    std::vector<T> preorder;
    std::vector<T> postorder;
    DFS(G& g) : graph(g)
    {
        for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it)
        {
            visited[*n_it] = false;
        }
    }
    ~DFS() = default; // destruktor
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
                {
                    visit(*n_it);
                }
            } // for
        } // if
    }
    void visit(T u);
};
// Usage:
// auto algorithm = DFS<int,Graph>(graph); // macierz sąsiedztwa
// auto algorithm = DFS<char,Graph<char>>(graph); // lista sąsiedztwa
// algorithm.run(start_node);
// for (auto& node : algorithm.preorder) { ... }
// for (auto& node : algorithm.postorder) { ... }

template<typename T, typename G>
void DFS<T, G>::visit(T u)
{
    visited[u] = true;
    preorder.push_back(u);      // odwiedzony na wejściu

    for (T neighbor : graph.neighbors(u))
    {
        if (!visited[neighbor])
        {
            visit(neighbor);    // rekurencja w głąb
        }
    }

    postorder.push_back(u);     // odwiedzony po przetworzeniu wszystkich sąsiadów
}
