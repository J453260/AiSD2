#include <iostream>
#include <list>
using namespace std;

template<typename T>
class MySet
{
    int BUCKET;
    list<int> *table;
    bool *Tablica;

public:
    MySet(int b) : BUCKET(b)
    {
        table = new list<int>[BUCKET];
        Tablica = new bool[BUCKET];
        fill(Tablica, Tablica + BUCKET, false);
    }

    ~MySet()
    {
        clear();
        delete[] table;
        delete[] Tablica;
    }

    int hash(int key) const
    {
        return (int(key) % BUCKET);
    }

    bool empty() const
    {
        for (int i = 0; i < BUCKET; i++)
            if (Tablica[i] != 0)
                return false;
        return true;
    }

    int size() const
    {
        int count = 0;
        for (int i = 0; i < BUCKET; i++)
            count += table[i].size();
        return count;
    }

    void insert(int key)
    {
        int idx = hash(key);

        for (int item : table[idx])
        {
            if (item == key)
            {
                return;
            }
        }

        table[idx].push_back(key);
        Tablica[idx] = 1;
    }

    int* find(int key)
    {
        int idx = hash(key);

        for (int& item : table[idx])
            if (item == key)
                return &item;

        return nullptr;
    }

    bool contains(int key)
    {
        return find(key) != nullptr;
    }

    void remove(int key)
    {
        int idx = hash(key);

        auto& bucket = table[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (*it == key)
            {
                bucket.erase(it);
                if (bucket.empty())
                {
                    Tablica[idx] = 0;
                }
                return;
            }
        }
    }

    void clear()
    {
        for (int i = 0; i < BUCKET; i++)
        {
            table[i].clear();
            Tablica[i] = 0;
        }
    }

    void display() const
    {
        cout << "{ ";
        bool first = true;
        for (int i = 0; i < BUCKET; i++)
        {
            for (int item : table[i])
            {
                if (!first) cout << ", ";
                cout << item;
                first = false;
            }
        }
        cout << " }" << endl;
    }
};

int main()
{
    cout << "Tworzenie zbioru (5 kubelkow)" << endl;
    MySet<int> s(5);

    cout << "Wstawianie: 10, 20, 15, 7, 3, 20, 10" << endl;
    s.insert(10);
    s.insert(20);
    s.insert(15);
    s.insert(7);
    s.insert(3);
    s.insert(20);   // duplikat
    s.insert(10);   // duplikat
    s.display();

    cout <<endl<< "Rozmiar zbioru: " << s.size() << " ---" << endl;
    cout <<endl<< "Czy pusty? " << (s.empty() ? "TAK" : "NIE") << endl;

    cout << "\nSzukanie elementow" << endl;
    int* ptr = s.find(15);
    cout << "find(15): " << (ptr ? "znaleziono -> " + to_string(*ptr) : "nullptr") << endl;
    cout << "find(99): " << (s.find(99) ? "znaleziono" : "nullptr") << endl;

    cout <<endl<< "Zawieranie" << endl;
    cout << "contains(7):  " << (s.contains(7)  ? "TAK" : "NIE") << endl;
    cout << "contains(99): " << (s.contains(99) ? "TAK" : "NIE") << endl;

    cout << endl <<"Usuniecie 15 i 7" << endl;
    s.remove(15);
    s.remove(7);
    s.display();
    cout << "Rozmiar po usunieciu: " << s.size() << endl;

    cout << endl << "Czyszczenie" << endl;
    s.clear();
    cout << "Czy pusty po clear()? " << (s.empty() ? "TAK" : "NIE") << endl;
    s.display();

    cout << endl << "Char" << endl;
    MySet<char> sc(7);
    sc.insert('A');
    sc.insert('B');
    sc.insert('C');
    sc.insert('A');  // duplikat
    sc.display();
    cout << "Rozmiar: " << sc.size() << endl;

    return 0;
}
