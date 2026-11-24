# MergeSort

Program C++17 implementujący sortowanie przez scalanie
w klasie szablonowej MergeSort<T>.

## Funkcjonalność

- Sortowanie rosnące.
- Obsługa int, long int, double i float.
- Program demonstracyjny z tablicami int i double.
- Obsługa pustych tablic, pojedynczych elementów i duplikatów.
- 66 testów GoogleTest.
- Dokumentacja LaTeX i Doxygen.

## Pliki

- MergeSort.h - szablon klasy i implementacja algorytmu.
- main.cpp - program demonstracyjny.
- MergeSortTests.cpp - testy jednostkowe.
- CMakeLists.txt - konfiguracja budowania.
- Doxyfile - konfiguracja dokumentacji API.
- docs/latex - źródła dokumentacji projektu.

## Budowanie i testy

```bash
cmake -S . -B cmake-build-debug -DBUILD_TESTING=ON
cmake --build cmake-build-debug
ctest --test-dir cmake-build-debug --output-on-failure
```

## Uruchomienie programu

```bash
./cmake-build-debug/mergesort
```

## Dokumentacja API

```bash
doxygen Doxyfile
```

Dokumentacja HTML: docs/doxygen/html/index.html.

## Dokumentacja LaTeX

W katalogu docs/latex wykonaj dwukrotnie:

```bash
pdflatex main.tex
```

Wynik: docs/latex/main.pdf.