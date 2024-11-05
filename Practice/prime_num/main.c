#include <stdio.h>
#include <math.h>
#define N 100

int main()
{
    int cisla[N], i, j;
    for (i = 2; i < N; i++) {
        cisla[i] = 1; // Není prvočíslo
        // vsude se priradi 1
        printf("1. %d -- cisla[i] = %d\n", i, cisla[i]);
    }
      

    for (i = 2; i < sqrt(N); i++) {
        printf("2. %d -- cisla[i] = %d\n", i, cisla[i]);
        if (cisla[i] == 0) {
            continue;
        }

        for(j = 2 * i; j < N; j += i) {
            printf("3. %d -- cisla[j] = %d\n", j, cisla[j]);
            cisla[j] = 0;
            printf("4. %d -- cisla[j] = %d\n", j, cisla[j]);
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