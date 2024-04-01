#include <vector>
#include <cmath>

class BaseMatrix {
protected:  // Изменил доступ к данным на protected для наследования
    std::vector<std::vector<int>> data;

public:
    BaseMatrix() = default;

    BaseMatrix(int rows, int cols) : data(rows, std::vector<int>(cols)) {}

    // Метод для изменения размеров матрицы
    void resize(int rows, int cols) {
        data.resize(rows, std::vector<int>(cols));
    }

    // Метод для заполнения матрицы случайными числами
    void fillRandom() {
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data[0].size(); ++j) {
                data[i][j] = std::sin(i) + std::cos(j) + std::log10(i + j + 1); // f(i,j)=sin(i)+cos(j)+lg(i+j+1)
            }
        }
    }

    BaseMatrix multiplySequential(const BaseMatrix& other) const { return other; };
    BaseMatrix multiplyParallelDynamic(const BaseMatrix& other) const { return other; };
    BaseMatrix multiplyParallelStatic(const BaseMatrix& other) const { return other; };
    BaseMatrix multiplyParallelGuided(const BaseMatrix& other) const { return other; };
    BaseMatrix multiplyParallelSections(const BaseMatrix& other) const { return other; };
    BaseMatrix multiplySequentialStrassen(const BaseMatrix& other) const { return other; };
    BaseMatrix multiplyParallelStrassen(const BaseMatrix& other) const { return other; };

};
