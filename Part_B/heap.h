#pragma once

template <class T>
class heap
{
private:
    std::vector<T> Heap;
    int heap_size;
    int length;
public:
    heap();
    T getItem(const int& n);
    int parent(const int& n);
    int left(const int& n);
    int right(const int& n);
    int getHeapSize();
    void initializeMaxHeap(const std::vector<T>& list);
    void maxHeapify(int i);
    void buildMaxHeap();

    void heapsort();
};

