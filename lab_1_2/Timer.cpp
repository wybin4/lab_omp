#include <iostream>
#include <omp.h>

class Timer {
private:
    double start_time;

public:
    Timer() : start_time(omp_get_wtime()) {}

    // ������ ������ �������
    void start() {
        start_time = omp_get_wtime();
    }

    // ��������� ������ ������� � ������� ��������� �����
    double end() {
        double end_time = omp_get_wtime();
        double elapsed_time = end_time - start_time;
        start_time = end_time; // ���������� end_time ��� ������
        return elapsed_time;
    }
};
