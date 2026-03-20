#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>   // make_heap, push_heap, pop_heap

template <typename T>
class MyPriorityQueue
{
    std::vector<T> lst; // działa domyślny konstruktor dla std::vector
public:
    MyPriorityQueue(std::size_t s=10)
    {
        lst.reserve(s);    // default constructor
    }

    ~MyPriorityQueue()
    {
        lst.clear();
    }

    MyPriorityQueue(const MyPriorityQueue& other) // copy constructor
    {
        lst = other.lst;
    }

    MyPriorityQueue(MyPriorityQueue&& other) // move constructor
    {
        lst = std::move(other.lst);
    }

    MyPriorityQueue& operator=(const MyPriorityQueue& other) // copy assignment operator, return *this
    {
        if(this == &other)
        {
            return *this;
        }

        lst = other.lst;
        return *this;
    }

    MyPriorityQueue& operator=(MyPriorityQueue&& other) // move assignment operator, return *this
    {
        if(this == &other)
        {
            return *this;
        }

        lst = std::move(other.lst);
        return *this;
    }

    bool empty() const
    {
        return lst.empty();
    }

    std::size_t size() const
    {
        return lst.size();    // liczba elementów w kolejce
    }

    void push(const T& item)   // dodanie do kolejki
    {
        lst.push_back(item);
        std::push_heap(lst.begin(), lst.end());
    }

    void push(T&& item)   // dodanie do kolejki
    {
        lst.push_back(std::move(item));
        std::push_heap(lst.begin(), lst.end());
    }

    T& top()
    {
        return lst.front();    // zwraca element największy, nie usuwa
    }

    void pop()   // usuwa element największy
    {
        std::pop_heap(lst.begin(), lst.end());
        lst.pop_back();
    }

    void clear()
    {
        lst.clear();    // czyszczenie listy z elementów
    }

    void display() // nie oczekujemy jakiegoś uporządkowania elementów
    {
        for(const T& item : lst)
        {
            std::cout<<item<<" ";
        }
        std::cout<<std::endl;
    }
};

int main()
{
    MyPriorityQueue<int> kolejka;
    assert(kolejka.empty());

    kolejka.push(3);
    kolejka.push(7);
    kolejka.push(1);
    kolejka.push(10);
    kolejka.push(5);

    assert(kolejka.size() == 5);
    assert(kolejka.top() == 10);

    std::cout << "Rozmiar: " << kolejka.size() << std::endl; // 5
    std::cout << "Najwiekszy element: " << kolejka.top() << std::endl; // 10
    std::cout << "Zawartosc: ";
    kolejka.display();

     // --- Pop ---
    kolejka.pop(); // usuwa 10
    std::cout << "Po pop(), najwiekszy: " << kolejka.top() << std::endl; // 7
    assert(kolejka.size() == 4);
    assert(kolejka.top() == 7);

    // --- Konstruktor kopiujący ---
    MyPriorityQueue<int> kopia(kolejka);
    assert(kopia.size() == kolejka.size());
    assert(kopia.top() == kolejka.top());
    std::cout << "Kopia, najwiekszy: " << kopia.top() << std::endl; // 7
    kopia.pop(); // usuwa z kopii, oryginał niezmieniony
    std::cout << "Oryginal po zmianie kopii, najwiekszy: " << kolejka.top() << std::endl; // nadal 7

    // --- Konstruktor przenoszący ---
    MyPriorityQueue<int> przeniesiona(std::move(kopia));
    std::cout << "Przeniesiona, najwiekszy: " << przeniesiona.top() << std::endl;
    std::cout << "Kopia po move, rozmiar: " << kopia.size() << std::endl; // 0

    // --- Copy assignment operator ---
    MyPriorityQueue<int> q1;
    q1.push(100);
    q1.push(200);
    MyPriorityQueue<int> q2;
    q2 = q1; // copy assignment
    assert(q2.top() == 200);
    std::cout << "q2 po copy assignment, najwiekszy: " << q2.top() << std::endl; // 200
    q1.pop();
    std::cout << "q2 po zmianie q1, najwiekszy: " << q2.top() << std::endl; // nadal 200

    // --- Move assignment operator ---
    MyPriorityQueue<int> q3;
    q3 = std::move(q1); // move assignment
    assert(q1.empty());
    std::cout << "q3 po move assignment, rozmiar: " << q3.size() << std::endl;
    std::cout << "q1 po move assignment, rozmiar: " << q1.size() << std::endl; // 0

    // --- Self-assignment ---
    q2 = q2; // nie powinno crashować
    std::cout << "q2 po self-assignment, najwiekszy: " << q2.top() << std::endl; // 200

    // --- Clear ---
    kolejka.clear();
    assert(kolejka.empty());
    std::cout << "Kolejka po clear(), rozmiar: " << kolejka.size() << std::endl; // 0

    std::cout<<std::endl;

    std::cout<<"Wszystkie testy zostaly zaliczone"<<std::endl;

    return 0;
}
