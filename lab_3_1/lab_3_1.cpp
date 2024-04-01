#include <iostream>
#include <iomanip>
#include <functional>
#include "../lab_1_2/Timer.cpp"
#include <vector>
#include <omp.h>
#include "Sort.cpp"

int num_starts = 20;
Timer timer;
std::vector<long> num_steps_values = { 1000, 2000, 3000, 4000 };

void printTableHeader() {
    std::cout << std::setw(20) << std::left << "Реализация" << std::setw(10) << std::left
        << "Потоки" << std::setw(27) << std::right << "Время по " << num_starts << " запускам\n";
    std::cout << std::setw(45) << std::right
        << "1000" << std::setw(10) << "2000" << std::setw(10) << "3000" << std::setw(10) << "4000" << std::endl;
}

void printTableRowSequence(const std::string& action, std::function<void(int, BaseSort*&)> createFunction, std::function<void(BaseSort*)> calculateFunction) {
    std::cout << std::setw(20) << std::left << action << std::setw(20) << std::left << 0;

    for (const long num_steps : num_steps_values) {
        BaseSort* sort = nullptr;
        createFunction(num_steps, sort);
        double total_elapsed_seconds = 0.0;

        for (int i = 0; i < num_starts; i++) {
            Timer timer;
            timer.start();
            calculateFunction(sort);
            total_elapsed_seconds += timer.end();
            sort->reset();
        }

        double average_elapsed_seconds = total_elapsed_seconds / num_starts;
        std::cout << std::setw(10) << std::left << std::fixed << std::setprecision(6) << average_elapsed_seconds;

        delete sort;
    }

    std::cout << std::endl;
}

void createInt(int size, BaseSort*& sort) {
    sort = new SortInt(size);
}

void createFloat(int size, BaseSort*& sort) {
    sort = new SortFloat(size);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    std::locale::global(std::locale(""));

    printTableHeader();

    std::cout << std::setw(60) << std::right << "Тип данных int, последовательно" << std::endl;
    printTableRowSequence("bubble classic", createInt,
        [](BaseSort* sort) {
            sort->bubbleSort();
        });
    printTableRowSequence("bubble odd/even", createInt,
        [](BaseSort* sort) {
            return sort->oddEvenBubbleSort();
        });
    printTableRowSequence("shell", createInt,
        [](BaseSort* sort) {
            return sort->shellSort();
        });
    printTableRowSequence("qsort", createInt,
        [](BaseSort* sort) {
            return sort->quickSort();
        });

    std::cout << std::setw(60) << std::right << "Тип данных double, последовательно" << std::endl;
    printTableRowSequence("bubble classic", createFloat,
        [](BaseSort* sort) {
            sort->bubbleSort();
        });
    printTableRowSequence("bubble odd/even", createFloat,
        [](BaseSort* sort) {
            return sort->oddEvenBubbleSort();
        });
    printTableRowSequence("shell", createFloat,
        [](BaseSort* sort) {
            return sort->shellSort();
        });
    printTableRowSequence("qsort", createFloat,
        [](BaseSort* sort) {
            return sort->quickSort();
        });

    std::cout << std::setw(60) << std::right << "Тип данных int, параллельно" << std::endl;
    printTableRowSequence("bubble classic", createInt,
        [](BaseSort* sort) {
            sort->bubbleSort(true);
        });
    printTableRowSequence("bubble odd/even", createInt,
        [](BaseSort* sort) {
            return sort->oddEvenBubbleSort(true);
        });
    printTableRowSequence("shell", createInt,
        [](BaseSort* sort) {
            return sort->shellSort(true);
        });
    printTableRowSequence("qsort", createInt,
        [](BaseSort* sort) {
            return sort->quickSort(true);
        });

    std::cout << std::setw(60) << std::right << "Тип данных double, параллельно" << std::endl;
    printTableRowSequence("bubble classic", createFloat,
        [](BaseSort* sort) {
            sort->bubbleSort(true);
        });
    printTableRowSequence("bubble odd/even", createFloat,
        [](BaseSort* sort) {
            return sort->oddEvenBubbleSort(true);
        });
    printTableRowSequence("shell", createFloat,
        [](BaseSort* sort) {
            return sort->shellSort(true);
        });
    printTableRowSequence("qsort", createFloat,
        [](BaseSort* sort) {
            return sort->quickSort(true);
        });

    return 0;
}
