#include <stdio.h>
#include <math.h>
#define N 999999

int main()
{
    int cisla[N], i, j;
    for (i = 2; i < N; i++) {
        cisla[i] = 1; // Není prvočíslo
        // vsude se priradi 1
    }
      

    for (i = 2; i < sqrt(N); i++) {
        if (cisla[i] == 0) {
            continue;
        }

        for(j = 2 * i; j < N; j += i) {
            cisla[j] = 0;
        }
    }

    for (i = 2; i < N; i++) {
        if (cisla[i] == 1) {
            printf("%d\n", i);
        }
            
    }
//  getchar();
    return 0;
}