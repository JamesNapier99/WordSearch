#pragma once

template <class T>
class heap
{
private:
    std::vector<T> Heap;
    int heapsize;
    int length;
public:
    heap();
    T getItem(const int& n);
    int parent(const int& n);
    int left(const int& n);
    int right(const int& n);
    void initializeMaxHeap();
    void maxHeapify(std::vector<T>& list, int& i);
    void buildMaxHeap(const std::vector<T>& list);

    void heapsort();
};

