#include <iostream>
#include <omp.h>

class Timer {
private:
    double start_time;

public:
    Timer() : start_time(omp_get_wtime()) {}

    // Начать отсчет времени
    void start() {
        start_time = omp_get_wtime();
    }

    // Закончить отсчет времени и вернуть прошедшее время
    double end() {
        double end_time = omp_get_wtime();
        double elapsed_time = end_time - start_time;
        start_time = end_time; // Используем end_time для сброса
        return elapsed_time;
    }
};
