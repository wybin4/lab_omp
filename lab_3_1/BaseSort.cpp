class BaseSort {
protected: 
    int size;

public:

    BaseSort(int arraySize) { size = arraySize; }

    virtual void fillRandom(bool parallel = false) { }

    virtual void reset(bool parallel = false) { }

    virtual void bubbleSort(bool parallel = false) { }

    virtual void oddEvenBubbleSort(bool parallel = false) { }

    virtual void shellSort(bool parallel = false) { }
    virtual void quickSort(bool parallel = false) { }
};