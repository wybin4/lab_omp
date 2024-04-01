#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include "VectorWrapper.cpp"
#include <iomanip>
#include "Timer.cpp"
#include <omp.h>

void printTableRow(const std::string& action, const std::string& variant, Timer& timer) {
    double elapsed_seconds = timer.end();

    // Преобразование времени в наносекунды
    long long elapsed_nanoseconds = static_cast<long long>(elapsed_seconds * 1e9);

    std::cout << std::setw(30) << std::left << action << std::setw(30) << std::left << variant
        << std::setw(20) << std::left << elapsed_nanoseconds << " наносекунд." << std::endl;
}

std::vector<float> generateRandomVector(size_t size) {
    std::vector<float> randomVector(size);
    for (size_t i = 0; i < size; ++i) {
        randomVector[i] = static_cast<float>(std::rand()) / RAND_MAX;
    }
    return randomVector;
}

int main()
{
    std::locale::global(std::locale(""));
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<float> data1 = generateRandomVector(1000000);
    std::vector<float> data2 = generateRandomVector(1000000);

    VectorWrapper vector1(data1);
    VectorWrapper vector2(data2);

    // Измерение времени для fillSequential
    Timer timer;
    vector1.fillSequential();
    printTableRow("Заполнение вектора", "Последовательно", timer);


    // Измерение времени для fillParallel
    vector1.fillParallel();
    printTableRow("Заполнение вектора", "Параллельно", timer);


    // Измерение времени для addSequential
    std::vector<float> resultSequential = vector1.addSequential(vector2);
    printTableRow("Сложение векторов", "Последовательно", timer);


    // Измерение времени для addParallelFor
    std::vector<float> resultParallelFor = vector1.addParallelFor(vector2);
    printTableRow("Сложение векторов", "for", timer);


    // Измерение времени для addParallelSections
    std::vector<float> resultParallelSections = vector1.addParallelSections(vector2);
    printTableRow("Сложение векторов", "sections", timer);


    // Измерение времени для sumSequential
    float sumSequential = vector1.sumSequential();
    printTableRow("Итоговая сумма элементов", "Последовательно", timer);


    // Измерение времени для sumParallelReducer
    float sumParallelReducer = vector1.sumParallelReducer();
    printTableRow("Итоговая сумма элементов", "reduction", timer);


    // Измерение времени для sumParallelCritical
    float sumParallelCritical = vector1.sumParallelSections();
    printTableRow("Итоговая сумма элементов", "sections", timer);


    return 0;
}
