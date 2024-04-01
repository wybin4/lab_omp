#include <vector>
#include <iostream>

class VectorWrapper {
private:
    std::vector<float> data_;

public:
    VectorWrapper(const std::vector<float>& data) : data_(data) {}

    // Заполнение массива (вектора) последовательно
    void fillSequential() {
        for (int i = 0; i < data_.size(); ++i) {
            if (i % 2 == 0) { // Четный номер варианта
                data_[i] = sin(i); // Используем sin
            }
            else { // Нечетный номер варианта
                data_[i] = cos(i); // Используем cos
            }
        }
    }

    // Заполнение массива (вектора) параллельно
    void fillParallel() {
        int i;
#pragma omp parallel for private(i)
        for (i = 0; i < data_.size(); ++i) {
            if (i % 2 == 0) { // Четный номер варианта
                data_[i] = sin(i); // Используем sin
            }
            else { // Нечетный номер варианта
                data_[i] = cos(i); // Используем cos
            }
        }
    }

    // Сложение векторов последовательно
    std::vector<float> addSequential(const VectorWrapper& other) const {
        std::vector<float> result(data_.size());
        for (int i = 0; i < data_.size(); ++i) {
            result[i] = data_[i] + other.data_[i];
        }
        return result;
    }

    // Сложение векторов параллельно с использованием цикла FOR
    std::vector<float> addParallelFor(const VectorWrapper& other) const {
        std::vector<float> result(data_.size());
        int i;
#pragma omp parallel for private(i)
        for (i = 0; i < data_.size(); ++i) {
            result[i] = data_[i] + other.data_[i];
        }
        return result;
    }

    // Сложение векторов параллельно с использованием цикла Sections
    std::vector<float> addParallelSections(const VectorWrapper& other) const {
        std::vector<float> result(data_.size());
        int i;
#pragma omp parallel sections private(i)
        {
#pragma omp section
            {
                for (i = 0; i < data_.size() / 2; ++i) {
                    result[i] = data_[i] + other.data_[i];
                }
            }
#pragma omp section
            {
                for (i = data_.size() / 2; i < data_.size(); ++i) {
                    result[i] = data_[i] + other.data_[i];
                }
            }
        }
        return result;
    }

    // Подсчет суммы всех элементов итогового вектора последовательно
    float sumSequential() const {
        float sum = 0;
        for (int i = 0; i < data_.size(); ++i) {
            sum += data_[i];
        }
        return sum;
    }

    // Подсчет суммы всех элементов итогового вектора параллельно с использованием редукторов
    float sumParallelReducer() const {
        float sum = 0;
        int i;
#pragma omp parallel for reduction(+:sum) private(i)
        for (i = 0; i < data_.size(); ++i) {
            sum += data_[i];
        }
        return sum;
    }

    // Подсчет суммы всех элементов итогового вектора параллельно с использованием критических секций
    float sumParallelSections() const {
        float sum1 = 0;
        float sum2 = 0;

        int i;
#pragma omp parallel sections private(i)
        {
#pragma omp section
            {
                for (i = 0; i < data_.size() / 2; ++i) {
                    sum1 += data_[i];
                }
            }
#pragma omp section
            {
                for (i = data_.size() / 2; i < data_.size(); ++i) {
                    sum2 += data_[i];
                }
            }
        }

        return sum1 + sum2;
    }

};
