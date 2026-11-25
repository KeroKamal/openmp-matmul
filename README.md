# Parallele Matrixmultiplikation mit OpenMP

Naive Matrixmultiplikation (n × n) in C++, die äußere Schleife wird mit `#pragma omp parallel for` parallelisiert.
Das Programm misst die Laufzeit für 1, 2 und 4 Threads und prüft per Checksumme, dass das Ergebnis gleich bleibt.

## Ausführen
    g++ -O2 -fopenmp matmul.cpp -o matmul
    ./matmul 1200

## Ergebnis (n = 1200, Testrechner mit 2 Kernen)
| Threads | Zeit | Speedup |
|---|---|---|
| 1 | 1,036 s | 1,00× |
| 2 | 0,512 s | 2,02× |
| 4 | 0,492 s | 2,11× |

Mit 2 Kernen ist der Speedup nahezu ideal; mehr Threads als Kerne bringen kaum noch etwas.
Auf einem Rechner mit mehr Kernen bitte erneut messen und die Tabelle anpassen.
