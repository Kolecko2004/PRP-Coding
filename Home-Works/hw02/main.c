#include <stdio.h>
#define MAXNUM 10000
#define MINNUM -10000

void number_write(int number, int length) {
    if (length > 0) {
        fprintf(stdout, ", %d", number);
    } else {
        fprintf(stdout, "%d", number);
    }
}

float percent(float this, float from) {
    return this / (from / 100);
}

float average(int sum, int length) {
    return (float)sum / length;
}

int higher(int num1, int num2, int length) {
    return num1 < num2 ? num2 : num1;
}

int lower(int num1, int num2, int length) {
    return num1 > num2 ? num2 : num1;
}

void positive_negative_numbers(int number, int* positiveNum, int* negativeNum) {
    if (number > 0) {
        (*positiveNum)++;
    } else if (number < 0) {
        (*negativeNum)++;
    }
}

void even_odd_numbers(int number, int* evenNum, int* oddNum) {
    number % 2 ? (*oddNum)++ : (*evenNum)++;
}

int main () {
    int evenNum = 0, oddNum = 0, positiveNum = 0, negativeNum = 0;
    int number = 0, result = 0, sum = 0, numCount = 0;
    int maxNum = MINNUM, lowNum = MAXNUM;

    while (result != -1) {
        result = fscanf(stdin, "%d", &number);

        if (result == 0) {
            fprintf(stdout, "\n");
            fprintf(stdout, "Error: Chyba nacitani vstupu!\n");
            return 100;
        }

        if (number < MINNUM || number > MAXNUM) 
        {
            fprintf(stdout, "\n");
            fprintf(stdout, "Error: Vstup je mimo interval!\n");
            return 100;
        }

        if (result == 1) {
            positive_negative_numbers(number, &positiveNum, &negativeNum);
            even_odd_numbers(number, &evenNum, &oddNum);
            number_write(number, numCount);
            maxNum = higher(number, maxNum, numCount);
            lowNum = lower(number, lowNum, numCount);
            sum += number;
            numCount++;
        }
    }

    fprintf(stdout, "\n");
    fprintf(stdout, "Pocet cisel: %d\n", numCount);

    fprintf(stdout, "Pocet kladnych: %d\n", positiveNum);
    fprintf(stdout, "Pocet zapornych: %d\n", negativeNum);

    fprintf(stdout, "Procento kladnych: %.2f\n", percent(positiveNum, numCount));
    fprintf(stdout, "Procento zapornych: %.2f\n", percent(negativeNum, numCount));

    fprintf(stdout, "Pocet sudych: %d\n", evenNum);
    fprintf(stdout, "Pocet lichych: %d\n", oddNum);

    fprintf(stdout, "Procento sudych: %.2f\n", percent(evenNum, numCount));
    fprintf(stdout, "Procento lichych: %.2f\n", percent(oddNum, numCount));

    fprintf(stdout, "Prumer: %.2f\n", average(sum, numCount));
    fprintf(stdout, "Maximum: %d\n", maxNum);
    fprintf(stdout, "Minimum: %d\n", lowNum);
    
    return 0;
}
