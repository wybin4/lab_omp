#include <iostream>
#include <iomanip>
#include <omp.h>
#include "PiCalculator.cpp"
#include "../lab_1_2/Timer.cpp"
#include <string>
#include <vector>
#include <functional>

void printTableHeader() {
    std::cout << std::setw(20) << std::left << "Реализация" << std::setw(10) << std::left
        << "Потоки" << std::setw(35) << std::right << "Время, с\n";
    std::cout << std::setw(45) << std::right  
        << "10000" << std::setw(10) << "20000" << std::setw(10) << "30000" << std::setw(10) << "40000" << std::endl;
}

void printTableRow(const std::string& action, int threads, Timer& timer, const std::vector<long>& num_steps_values, PiCalculator& piCalculator, std::function<double(void)> calculateFunction) {
    std::cout << std::setw(20) << std::left << action << std::setw(20) << std::left << threads;

    for (const long num_steps : num_steps_values) {
        piCalculator.setNumSteps(num_steps);
        timer.start();
        calculateFunction(); 
        double elapsed_seconds = timer.end();

        std::cout << std::setw(10) << std::left <<std::fixed<< std::setprecision(6) << elapsed_seconds;
    }

    std::cout << std::endl;
}

int main() {
    std::locale::global(std::locale(""));

    std::vector<long> num_steps_values = { 10000, 20000, 30000, 40000 };

    PiCalculator piCalculator;
    printTableHeader();

    Timer timer;
    printTableRow("Последовательно", 0, timer, num_steps_values, piCalculator, [&piCalculator]() {
        return piCalculator.calculatePiSequential(); 
        });


    for (int threads = 4; threads <= 12; threads += 4) {

        omp_set_num_threads(threads);
        printTableRow("FOR static", threads, timer, num_steps_values, piCalculator, [&piCalculator]() {
            return piCalculator.calculatePiParallelStatic();
            });

    }
    for (int threads = 4; threads <= 12; threads += 4) {

        omp_set_num_threads(threads);
        printTableRow("FOR dynamic", threads, timer, num_steps_values, piCalculator, [&piCalculator]() {
            return piCalculator.calculatePiParallelDynamic();
            });

    }
    for (int threads = 4; threads <= 12; threads += 4) {

        omp_set_num_threads(threads);
        printTableRow("FOR guided", threads, timer, num_steps_values, piCalculator, [&piCalculator]() {
            return piCalculator.calculatePiParallelGuided();
            });

    }

    return 0;
}
