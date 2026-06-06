# Algorytm Borůvki

Algorytm Borůvki służy do wyznaczania **minimalnego drzewa rozpinającego** (MST – Minimum Spanning Tree) grafu ważonego. Jego działanie polega na stopniowym łączeniu rozłącznych składowych grafu za pomocą najtańszych dostępnych krawędzi.

## Idea działania

Na początku każdy wierzchołek tworzy osobną składową.

W każdej iteracji algorytm:

1. Dla każdej aktualnej składowej znajduje najtańszą krawędź prowadzącą do innej składowej.
2. Dodaje znalezione krawędzie do budowanego MST.
3. Łączy składowe połączone wybranymi krawędziami.
4. Powtarza proces aż wszystkie wierzchołki znajdą się w jednej składowej.

Do efektywnego zarządzania składowymi wykorzystywana jest struktura **Union-Find (Disjoint Set Union)**.

## Przykład

Graf:

```text
A --1-- B
|       |
4       2
|       |
C --3-- D
```

Początkowo:

```text
{A} {B} {C} {D}
```

Najtańsze krawędzie wychodzące ze składowych:

```text
A -> AB (1)
B -> AB (1)
C -> CD (3)
D -> BD (2)
```

Po ich dodaniu:

```text
A --1-- B
         \
          2
           \
            D
            |
            3
            |
            C
```

Wszystkie wierzchołki zostały połączone, więc otrzymaliśmy minimalne drzewo rozpinające o koszcie:

```text
1 + 2 + 3 = 6
```

## Struktura Union-Find

Implementacja wykorzystuje strukturę Union-Find do przechowywania informacji o aktualnych składowych grafu.

Dostępne operacje:

- `find(x)` – zwraca reprezentanta składowej zawierającej wierzchołek `x`,
- `unite(x, y)` – łączy dwie składowe.

Zastosowano:
- kompresję ścieżki (*path compression*),
- łączenie według rangi (*union by rank*),

co zapewnia niemal stały czas działania obu operacji.

## Złożoność obliczeniowa

| Operacja | Złożoność |
|-----------|-----------|
| Jedna iteracja | O(n) |
| Liczba iteracji | O(log m) |
| Cały algorytm | O(n log m) |

gdzie:

- `n` – liczba wierzchołków,
- `m` – liczba krawędzi.

## Wynik

Funkcja `BoruvkaMST()` zwraca wektor krawędzi należących do minimalnego drzewa rozpinającego:

```cpp
std::vector<std::tuple<float, int, int>>
```

Każdy element ma postać:

```cpp
(waga, źródło, cel)
```

i reprezentuje jedną krawędź MST.

## Uwagi

- Graf powinien być nieskierowany.
- Dla grafu spójnego wynik zawiera dokładnie `V - 1` krawędzi.
- Dla grafu niespójnego algorytm zwraca minimalny las rozpinający (MSF).



## Kompilacja

Projekt zawiera plik `Makefile`, dlatego do kompilacji wystarczy użyć polecenia:

```bash
make
```

Po poprawnym zakończeniu kompilacji zostanie utworzony plik wykonywalny zgodnie z konfiguracją zawartą w `Makefile`.

### Uruchomienie

```bash
make run
```

### Czyszczenie plików kompilacji

Aby usunąć pliki obiektowe i plik wykonywalny:

```bash
make clean
```
