#include <stdio.h>
#define MAXNUM 10000
#define MINNUM -10000

int inputTest(int testNum1, int testNum2, int scanInfo) {
    
    if (scanInfo <= 1) {
        fprintf(stderr, "Chyba nacitani vstupu!\n");
        return 100;
    }

    else if (testNum1 < MINNUM || testNum1 > MAXNUM) 
    {
        fprintf(stderr, "Error: Vstup je mimo interval!\n");
        return 100;
    }

    else if (testNum2 < MINNUM || testNum2 > MAXNUM) 
    {
        fprintf(stderr, "Error: Vstup je mimo interval!\n");
        return 100;
    }

    return 0;
}

int main () {
    int num1 = 0;
    int num2 = 0;
    int exitCode = 0;

    fprintf(stdin, "Enter two numbers between %d and %d: ",MINNUM, MAXNUM);
    
    int result = scanf("%d %d", &num1, &num2);
    
    double average = (double)(num1 + num2) / 2.0;
    int test = inputTest(num1, num2, result);
    test != 0 ? return 100 : test;

    fprintf(stdout, "Desitkova soustava: %d %d\n", num1, num2);
    fprintf(stdout, "Sestnactkova soustava: %x %x\n", num1, num2);
    fprintf(stdout, "Soucet: %d + %d = %d\n", num1, num2, num1 + num2);
    fprintf(stdout, "Rozdil: %d - %d = %d\n", num1, num2, num1 - num2);
    fprintf(stdout, "Soucin: %d * %d = %d\n", num1, num2, num1 * num2);

    if (num2 == 0) {
        fprintf(stdout, "Podil: %d / %d = NaN\n", num1, num2);
        fprintf(stderr, "Error: Nedefinovany vysledek!\n");
        exitCode = 101;
    }
    else {
        fprintf(stdout, "Podil: %d / %d = %d\n", num1, num2, num1 / num2);
    }
    
    fprintf(stdout, "Prumer: %.1f\n", average);

	return exitCode;
}


