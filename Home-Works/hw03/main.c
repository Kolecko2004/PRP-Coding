#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 69
#define MINNUM 3

int range_test(int num){
    if (num < MINNUM || num > MAXNUM) {
        fprintf(stderr, "Error: Vstup mimo interval!\n");
        exit(101);
    }

    return 0;
}

int inputTest(int testNum1, int testNum2, int scanInfo, int fence) {

    if (scanInfo < 1) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }

    else if (testNum1 != testNum2 && scanInfo <= 1) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }

    range_test(testNum1);
    range_test(testNum2);
    
    if (testNum1 % 2 != 1) {
        fprintf(stderr, "Error: Sirka neni liche cislo!\n");
        exit(102);
    }

    if (testNum1 == testNum2 && (fence >= testNum1 || fence >= testNum2 || fence <= 0) ) {
        fprintf(stderr, "Error: Neplatna velikost plotu!\n");
        exit(103);
    }

    return 0;
}

void top(int width) {
    for (int i = 0; i < (width / 2); ++i) {
        putchar(' ');
    }
    fprintf(stdout ,"X\n");
}

void roof(int width) {
    top(width);
    int middle_gap = 1;
    int left_gap = (width - 2 - middle_gap) / 2;
    int levels = (width - 1) / 2;
    
    for (int i = 0; i < levels - 1; ++i) {

        for (int l = 0; l < left_gap; ++l) {
            putchar(' ');
        }

        putchar('X');

        for (int m = 0; m < middle_gap; ++m) {
            putchar(' ');
        }

        fprintf(stdout, "X\n");

        middle_gap += 2;
        left_gap -= 1;
    }
}

void print_x_line(int width) {
    for (int i = 0; i < width; ++i) {
        putchar('X');
    }
}

void house_filling(int row, int column) {
    if ((row + column)% 2 == 0) {
        putchar('o');
    }

    else {
        putchar('*'); 
    }
}

void fence_build(int fence, char one, char two) {
    int line_alternate = (fence % 2 == 0)? 1 : 0;

    for (int i = 0; i < fence; ++i) {
        
        if (line_alternate % 2 == 0) {
            fprintf(stdout, "%c", one);
        }

        else {
            fprintf(stdout, "%c", two);
        }

        ++line_alternate;
    }
}

void vertical_line(int height, int width, int fence) {
    for (int i = 0; i < height - 2; ++i) {
        putchar('X');
        for (int j = 0; j < width - 2; ++j ) {
            if (height == width) {
                house_filling(j, i);
            }
            else {
                putchar(' ');
            }
        }
        putchar('X');
        if (height == width && i + fence == height - 1) {
            fence_build(fence, '|', '-');;
        }

        else if (height == width && i + fence > height - 1) {
            fence_build(fence, '|', ' ');
        }
        putchar('\n');
    }
}

void build(int width, int height, int fence) {
    roof(width);
    print_x_line(width);
    putchar('\n');
    vertical_line(height, width, fence);
    print_x_line(width);
    
    if (width == height) {
        fence_build(fence, '|', '-');
        putchar('\n');
    }

    else {
        putchar('\n');
    }
}

int main () {
    int width = 0, height = 0, fence = 0, scan1, scan2;

    scan1 = fscanf(stdin, "%d %d", &width, &height);

    if (width != height) {
        inputTest(width, height, scan1, fence);
    }

    else {
        scan2 = fscanf(stdin, "%d", &fence);
        inputTest(width, height, scan2, fence);
    }
    
    build(width, height, fence);
    
    return 0;
}
