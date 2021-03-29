#include <iostream>
#include <chrono>
#include "size.h"
#include "Array.h"

using namespace std;


int main() {
    float percent[8] = {0, 25, 50, 75, 95, 99, 99.7, 0};
    char param = 'u';

    int k =0;
    while (k<3) {
        int used_time[8] = {0, 0, 0, 0, 0, 0, 0, 0};

        int i = 0;
        while (i < 100) {
            for (int j = 0; j < 8; j++) {
                Array<int, SIZE> Arr;
                if (j == 0) {
                    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                    if (k==0) Arr.Sort_quicksort();
                    else if (k==1) Arr.Sort_heapsort();
                    else if (k==2) Arr.Sort_mergesort();
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    used_time[j] += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    Arr.Is_correct(param);
                } else if (j == 7) {

                    Arr.Reverse();
                    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                    if (k==0) Arr.Sort_quicksort();
                    else if (k==1) Arr.Sort_heapsort();
                    else if (k==2) Arr.Sort_mergesort();
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    used_time[j] += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    Arr.Is_correct(param);
                } else {
                    Arr.Part_sort(percent[j]);
                    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                    if (k==0) Arr.Sort_quicksort();
                    else if (k==1) Arr.Sort_heapsort();
                    else if (k==2) Arr.Sort_mergesort();
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    used_time[j] += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                    Arr.Is_correct(param);
                }
            }
            i++;
        }
        for (int j = 0; j < 8; j++) {
            cout << used_time[j] << "\t";
        }
        cout <<"\n";
        k++;
    }


return 0;
}