#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>
#include "Matrix.cpp"
#include <iomanip>
#include <functional>
#include "../lab_1_2/Timer.cpp"

Timer timer;
std::vector<long> num_steps_values = { 1000, 2000, 3000, 4000 };

void printTableHeader() {
    std::cout << std::setw(20) << std::left << "Реализация" << std::setw(10) << std::left
        << "Потоки" << std::setw(35) << std::right << "Время, с\n";
    std::cout << std::setw(45) << std::right
        << "1000" << std::setw(10) << "2000" << std::setw(10) << "3000" << std::setw(10) << "4000" << std::endl;
}

void printTableRow(const std::string& action, int threads, std::function<void(BaseMatrix&, BaseMatrix&, int)> createFunction, std::function<BaseMatrix(BaseMatrix&, BaseMatrix&)> calculateFunction) {
    std::cout << std::setw(20) << std::left << action << std::setw(20) << std::left << threads;

    for (const long num_steps : num_steps_values) {
        BaseMatrix A, B;
        createFunction(A, B, num_steps);

        timer.start();
        BaseMatrix result = calculateFunction(A, B);
        double elapsed_seconds = timer.end();

        std::cout << std::setw(10) << std::left << std::fixed << std::setprecision(6) << elapsed_seconds;
    }

    std::cout << std::endl;
}

void initializeMatrices(BaseMatrix& A, BaseMatrix& B, int n) {
    A.resize(n, n);
    B.resize(n, n);

    A.fillRandom();
    B.fillRandom();
}

int main() {
    std::locale::global(std::locale(""));

    printTableHeader();

    std::cout << std::setw(60) << std::right << "Классический алгоритм перемножения матриц" << std::endl;

    printTableRow("Последовательно", 0, initializeMatrices, [](BaseMatrix& A, BaseMatrix& B) {
            return A.multiplySequential(B);
            });

    for (int threads = 4; threads <= 12; threads += 4) {

        omp_set_num_threads(threads);
        printTableRow("FOR static", threads, initializeMatrices, [](BaseMatrix& A, BaseMatrix& B) {
            return A.multiplyParallelStatic(B);
            });

    }
    for (int threads = 4; threads <= 12; threads += 4) {

        omp_set_num_threads(threads);
        printTableRow("FOR dynamic", threads, initializeMatrices, [](BaseMatrix& A, BaseMatrix& B) {
            return A.multiplyParallelDynamic(B);
            });

    }
    for (int threads = 4; threads <= 12; threads += 4) {

        omp_set_num_threads(threads);
        printTableRow("FOR guided", threads, initializeMatrices, [](BaseMatrix& A, BaseMatrix& B) {
            return A.multiplyParallelGuided(B);
            });
    }
    for (int threads = 4; threads <= 12; threads += 4) {

        omp_set_num_threads(threads);
        printTableRow("sections", threads, initializeMatrices, [](BaseMatrix& A, BaseMatrix& B) {
            return A.multiplyParallelSections(B);
            });
    }

    std::cout << std::setw(65) << std::right << "Быстрое перемножение матриц: алгоритм Штрассена" << std::endl;
    printTableRow("Последовательно", 0, initializeMatrices, [](BaseMatrix& A, BaseMatrix& B) {
        return A.multiplySequentialStrassen(B);
        });
    for (int threads = 4; threads <= 12; threads += 4) {

        omp_set_num_threads(threads);
        printTableRow("Параллельно", threads, initializeMatrices, [](BaseMatrix& A, BaseMatrix& B) {
            return A.multiplyParallelStrassen(B);
            });
    }

    return 0;
}
