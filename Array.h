#ifndef TAB_H
#define TAB_H

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
#include <chrono>
#include "size.h"



template <class TYPE, int Size>
class Array
{
private:
    TYPE extra_elem[Size];
    void Heapify(int heapSize, int parentIndex);
    void Quick_sort(int left, int right);
    int Quick_partition(int left, int right);
    TYPE Quick_chose_pivot(int left, int right);
    void Merge_sort(int leftIndex, int rightIndex);
    void Merge(int leftIndex, int middlIndex, int rightIndex);
    void Unsorted_part(float percent);

public:
    TYPE element[Size];
    Array();
    Array( const Array & Arr_to_copy );

    const TYPE & operator[] (int index) const;
    TYPE & operator[] (int index);

    void Part_sort(float percent);
    void Is_correct(char parameter) const;
    void Reverse();

    void Sort_heapsort();
    void Sort_quicksort();
    void Sort_mergesort();
};

/* Wsywietla na standardowym wyjsciu tablice.*/
template <class TYPE, int Size>
std::ostream& operator << (std::ostream & Strm, const Array<TYPE, Size> & Arr);

#endif