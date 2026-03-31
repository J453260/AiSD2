// edge.hpp
template<typename T>
class Edge {
public:
    T source;
    T target;
    float weight;
    Edge(T s, T t, float w=1.0) : source(s), target(t), weight(w) {}
    ~Edge() {}                // destruktor
    Edge(const Edge& edge) : source(edge.source), target(edge.target),
        weight(edge.weight) {}  // copy-constructor
    // Operator negacji bitowej, ale tu pasuje.
    Edge operator~() const { return Edge(target, source, weight); }
    Edge& operator=(const Edge& other); // return *this;
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge);
    bool operator==(const Edge& edge);
    bool operator!=(const Edge& edge);
};
