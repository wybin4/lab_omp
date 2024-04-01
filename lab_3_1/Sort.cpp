#include "BaseSort.cpp"
#include "SortStrategy.cpp"

class SortInt : public BaseSort {
private:
    int* arr;
    int* original_array;
    SequenceSortStrategy<int> sequence_strategy;
    ParallelSortStrategy<int> parallel_strategy;

public:
    SortInt(int arraySize) : BaseSort(arraySize) {
        arr = new int[arraySize];
        original_array = new int[arraySize];
        fillRandom();
    }

    ~SortInt() {
        delete[] arr;
        delete[] original_array;
    }

    void fillRandom() {
        for (int i = 0; i < size; ++i) {
            arr[i] = std::rand() % 100; // «аполн€ем случайными числами от 0 до 99
            original_array[i] = arr[i];
        }
    }

    void reset(bool parallel = false) override {
        parallel ? parallel_strategy.reset(arr, original_array, size) : sequence_strategy.reset(arr, original_array, size);
    }

    void bubbleSort(bool parallel = false) override {
        parallel ? parallel_strategy.bubbleSort(arr, size) : sequence_strategy.bubbleSort(arr, size);
    }

    void oddEvenBubbleSort(bool parallel = false) override {
        parallel ? parallel_strategy.oddEvenBubbleSort(arr, size) : sequence_strategy.oddEvenBubbleSort(arr, size);
    }

    void shellSort(bool parallel = false) override {
        parallel ? parallel_strategy.shellSort(arr, size) : sequence_strategy.shellSort(arr, size);
    }

    void quickSort(bool parallel = false) override {
        parallel ? parallel_strategy.quickSort(arr, size) : sequence_strategy.quickSort(arr, size);
    }

};

class SortFloat : public BaseSort {
private:
    float* arr;
    float* original_array;
    SequenceSortStrategy<float> sequence_strategy;
    ParallelSortStrategy<float> parallel_strategy;

public:
    SortFloat(int arraySize) : BaseSort(arraySize) {
        arr = new float[arraySize];
        original_array = new float[arraySize];
        fillRandom();
    }

    ~SortFloat() {
        delete[] arr;
        delete[] original_array;
    }

    void fillRandom() {
        for (int i = 0; i < size; ++i) {
            arr[i] = static_cast<float>(rand()) / RAND_MAX * 100.0f;  // «аполн€ем случайными числами от 0 до 99 в формате float
            original_array[i] = arr[i];
        }
    }

    void reset(bool parallel = false) override {
        parallel ? parallel_strategy.reset(arr, original_array, size) : sequence_strategy.reset(arr, original_array, size);
    }

    void bubbleSort(bool parallel = false) override {
        parallel ? parallel_strategy.bubbleSort(arr, size) : sequence_strategy.bubbleSort(arr, size);
    }

    void oddEvenBubbleSort(bool parallel = false) override {
        parallel ? parallel_strategy.oddEvenBubbleSort(arr, size) : sequence_strategy.oddEvenBubbleSort(arr, size);
    }

    void shellSort(bool parallel = false) override {
        parallel ? parallel_strategy.shellSort(arr, size) : sequence_strategy.shellSort(arr, size);
    }

    void quickSort(bool parallel = false) override {
        parallel ? parallel_strategy.quickSort(arr, size) : sequence_strategy.quickSort(arr, size);
    }
};
