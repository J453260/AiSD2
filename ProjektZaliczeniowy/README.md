# Algorytm Borůvki

Algorytm Borůvki wyznacza **minimalne drzewo rozpinające** (MST) grafu nieskierowanego z wagami. Został opublikowany przez Otakara Borůvkę w 1926 roku — jest jednym z najstarszych algorytmów grafowych.

---

## Idea

W odróżnieniu od algorytmu Prima (rozrasta jedną składową) i Kruskala (przetwarza krawędzie po kolei), Borůvka działa **równolegle na wszystkich składowych naraz**. W każdej rundzie każda składowa dokłada do MST swoją najtańszą krawędź wychodzącą na zewnątrz.

---

## Wymagania

- Graf musi być **nieskierowany**
- Graf musi być **spójny** (inaczej otrzymamy minimalne drzewo rozpinające lasu)
- Wagi krawędzi muszą być **nieujemne**

---

## Pseudokod

```
procedura BoruvkaMST(G, weight):
    T ← puste drzewo
    uf ← Union-Find dla wszystkich wierzchołków V(G)
    forest ← V(G)               # zbiór reprezentantów składowych
    new_len ← |forest|
    old_len ← new_len + 1

    dopóki old_len > new_len:
        old_len ← new_len
        MinEdge[u] ← (∞, None, None)  dla każdego u w forest

        # Faza 1: znajdź najtańszą krawędź wychodzącą z każdej składowej
        dla każdej krawędzi (s, t) w E(G):
            s2 ← uf.find(s)
            t2 ← uf.find(t)
            jeśli s2 ≠ t2:
                jeśli weight(s,t) < MinEdge[s2].waga:
                    MinEdge[s2] ← (weight(s,t), s, t)
                jeśli weight(s,t) < MinEdge[t2].waga:
                    MinEdge[t2] ← (weight(s,t), s, t)

        # Faza 2: połącz składowe przez wybrane krawędzie
        dla każdego u w forest:
            (edge_weight, s, t) ← MinEdge[u]
            jeśli edge_weight == ∞: kontynuuj   # graf niespójny
            jeśli uf.find(s) ≠ uf.find(t):
                uf.union(s, t)
                dodaj (s, t) do T

        # Zaktualizuj zbiór reprezentantów
        forest ← { uf.find(v) : v w forest }
        new_len ← |forest|
        jeśli new_len == 1: przerwij

    zwróć T
```

---

## Przykład działania

Rozważmy graf o 5 wierzchołkach:

```
    2       5
A ───── B ───── E
│       │       │
4       1       3
│       │       │
C ───── D ──────┘
    6
```

### Stan początkowy

Każdy wierzchołek tworzy osobną składową. Union-Find zawiera pięć rozłącznych zbiorów:

```
{A}  {B}  {C}  {D}  {E}
```

### Runda 1 — faza 1: szukanie najtańszych krawędzi

Dla każdej krawędzi grafu sprawdzamy, czy łączy dwie różne składowe.
Każda składowa zapamiętuje najtańszą znalezioną krawędź wychodzącą:

| Składowa | Kandydaci            | Wybrana krawędź |
|----------|----------------------|-----------------|
| `{A}`    | A–B (2), A–C (4)     | A–B (waga 2)    |
| `{B}`    | A–B (2), B–D (1), B–E (5) | B–D (waga 1) |
| `{C}`    | A–C (4), C–D (6)     | A–C (waga 4)    |
| `{D}`    | B–D (1), C–D (6), D–E (3) | B–D (waga 1) |
| `{E}`    | B–E (5), D–E (3)     | D–E (waga 3)    |

### Runda 1 — faza 2: łączenie składowych

Przetwarzamy wybrane krawędzie i łączymy składowe przez Union-Find.
Sprawdzamy za każdym razem, czy obie strony krawędzi są nadal w różnych składowych
(kilka składowych mogło wybrać tę samą krawędź):

```
A–B (2): find(A)≠find(B) → union(A,B), dodaj do MST   składowe: {A,B} {C} {D} {E}
B–D (1): find(B)≠find(D) → union(B,D), dodaj do MST   składowe: {A,B,D} {C} {E}
A–C (4): find(A)≠find(C) → union(A,C), dodaj do MST   składowe: {A,B,C,D} {E}
B–D (1): find(B)==find(D) → pomiń (już połączone)
D–E (3): find(D)≠find(E) → union(D,E), dodaj do MST   składowe: {A,B,C,D,E}
```

### Wynik

Po rundzie 1 mamy jedną składową — algorytm kończy działanie.

```
MST: A–B (2) + B–D (1) + A–C (4) + D–E (3) = suma wag: 10
```

```
    2
A ───── B
│       │
4       1
│       │
C       D
        │
        3
        │
        E
```

---

## Struktura Union-Find

Algorytm korzysta ze struktury **Union-Find** (zbiory rozłączne) do śledzenia składowych spójności.

| Operacja      | Opis                             | Złożoność      |
|---------------|----------------------------------|----------------|
| `find(x)`     | Zwraca reprezentanta składowej x | O(α(n)) ≈ O(1) |
| `union(x, y)` | Łączy składowe zawierające x i y | O(α(n)) ≈ O(1) |

Gdzie α to odwrotna funkcja Ackermanna — w praktyce nie przekracza 4 dla żadnych realistycznych danych.

Dwie kluczowe optymalizacje Union-Find stosowane w algorytmie:

- **Kompresja ścieżki** — `find` spłaszcza drzewo, podłączając każdy węzeł bezpośrednio do korzenia
- **Łączenie według rangi** — `union` zawsze podłącza mniejsze drzewo pod większe, zapobiegając degeneracji

---

## Dlaczego algorytm jest poprawny?

Poprawność opiera się na **twierdzeniu o przekroju**: dla każdego podziału wierzchołków na dwa rozłączne zbiory S i V\S, najtańsza krawędź przekrojowa należy do pewnego MST.

Każda składowa wyznacza naturalny przekrój — najtańsza krawędź wychodząca z niej jest **bezpieczna**, tzn. można ją dodać do MST bez utraty optymalności. Ponieważ w każdej rundzie każda składowa dodaje dokładnie jedną bezpieczną krawędź, cały wynik jest optymalny.

---

## Dlaczego algorytm się zatrzymuje?

W każdej rundzie każda składowa łączy się z co najmniej jedną inną — liczba składowych **co najmniej się zmniejsza o połowę**. Przy n składowych na początku po co najwyżej log₂(n) rundach zostanie jedna. Warunek `old_len > new_len` wykrywa również graf niespójny — jeśli żadna składowa nie znalazła krawędzi wychodzącej, liczba składowych się nie zmienia i pętla kończy działanie.

---

## Złożoność

| | Złożoność |
|---|---|
| Jedna runda (faza 1 + faza 2) | O(E) |
| Liczba rund | O(log V) |
| **Łącznie** | **O(E log V)** |
| Pamięć | O(V + E) |

---

## Zastosowania

- **Obliczenia równoległe i rozproszone** — składowe w każdej rundzie działają niezależnie, co łatwo zrównoleglić
- **Grafy o bardzo dużej liczbie krawędzi** — liniowy koszt każdej rundy dobrze sprawdza się przy gęstych grafach
- **Sieci komputerowe** — wyznaczanie minimalnego drzewa połączeń
- **Klasteryzacja danych** — MST jako podstawa algorytmów grupowania

---

## Uwagi implementacyjne

- Graf musi być **nieskierowany**
- Przy grafie niespójnym algorytm zwraca **minimalne drzewo rozpinające lasu** — osobne MST dla każdej składowej spójności
- Wynik zawiera dokładnie **V − 1 krawędzi** dla grafu spójnego
- Przy równych wagach wynik może się różnić między uruchomieniami, ale suma wag pozostaje minimalna
