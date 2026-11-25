// Matrixmultiplikation C = A * B (n x n) mit OpenMP; misst Laufzeit und Speedup.
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <omp.h>

int main(int argc, char** argv) {
    int n = argc > 1 ? std::atoi(argv[1]) : 1200;
    std::vector<double> A(n * n), B(n * n), C(n * n);
    for (int i = 0; i < n * n; ++i) { A[i] = (i % 7) * 0.5; B[i] = (i % 5) * 0.25; }

    double t1 = 0;
    for (int threads : {1, 2, 4}) {
        omp_set_num_threads(threads);
        std::fill(C.begin(), C.end(), 0.0);
        auto t0 = std::chrono::steady_clock::now();
        #pragma omp parallel for
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k) {
                double a = A[i * n + k];
                for (int j = 0; j < n; ++j) C[i * n + j] += a * B[k * n + j];
            }
        double t = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
        double checksum = 0; for (int i = 0; i < n * n; ++i) checksum += C[i];
        if (threads == 1) t1 = t;
        std::printf("n=%d threads=%d time=%.3fs speedup=%.2fx checksum=%.1f\n",
                    n, threads, t, t1 / t, checksum);
    }
}
