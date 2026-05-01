// dijkstra.hpp
#include <limits>
#include <queue>
#include <unordered_map>
template <typename T, typename G>
class Dijkstra
{
    G& graph;
public:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, float> distance;
    const float INF = std::numeric_limits<float>::infinity();

    Dijkstra(G& g) : graph(g)
    {
        for (auto it = graph.node_begin(); it != graph.node_end(); ++it)
        {
            distance[*it] = INF;
        }
    }
    ~Dijkstra() = default;

    void run(T u)
    {
        distance[u] = 0;

        using Entry = std::pair<float, T>;
        std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> kolejka;
        kolejka.push({0.0f, u});

        while(!kolejka.empty())
        {
            auto [dist, node] = kolejka.top();
            kolejka.pop();

            for (auto it = graph.adj_begin(node); it != graph.adj_end(node); ++it)
            {
                //float new_dist = distance[node] + weight;
                T v = *it;
                float w = graph.weight(node, v);
                float new_dist = distance[node] + w;

                if(new_dist < distance[v])
                {
                    distance[v] = new_dist;
                    parent[v] = node;
                    kolejka.push({new_dist, v});
                }
            }
        }
    }
};
// Usage:
// auto algorithm = Dijkstra<int,Graph>(G); // macierz sąsiedztwa
// auto algorithm = Dijkstra<char,Graph<char>>(G); // lista sąsiedztwa
// algorithm.run();
// for (auto& pair : algorithm.distance)
//     std::cout << pair.first << " distance : " << pair.second << std::endl;
