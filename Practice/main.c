#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Directly print the input number
    printf("%d\n", ({ int num; scanf("%d", &num); num; }));

    return 0;
}
