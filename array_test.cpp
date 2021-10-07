#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "tqdm/tqdm.h"

int main()
{
    int limit = 200000;
    int times = 10;
    clock_t start, stop;
    double best = -9999999999, worst = 0, avg = 0;
    for (int i : tqdm::range(times))
    {
        start = clock();
        int *arr = (int *)malloc(sizeof(int) * limit);
        for (int j : tqdm::range(limit))
        {
            arr[j] = 1;
        }
        free(arr);
        stop = clock();
        double time_spent = (double)(stop - start) / CLOCKS_PER_SEC;
        avg += time_spent;
        if (best == -9999999999)
        {
            best = time_spent;
            worst = time_spent;
        }
        else
        {
            if (time_spent < best)
            {
                best = time_spent;
            }
            if (time_spent > worst)
            {
                worst = time_spent;
            }
        }
    }
    avg = avg / times;
    std::cout << "Best time    :: \t" << best << " seconds" << std::endl;
    std::cout << "Worst time   :: \t" << worst << " seconds" << std::endl;
    std::cout << "Avg time     :: \t" << avg << " seconds" << std::endl;
    return 0;
}