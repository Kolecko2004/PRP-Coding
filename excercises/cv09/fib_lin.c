int fib (int number) {
    if (number == 2 || number == 1) {
        return 1;
    }

    if (number < 1) {
        return -1;
    }

    int k_2 = 1;
    int k_1 = 1;
    int k_0 = 0;

    for (int j = 3; j < number; j++) {
        k_0 = k_1 + k_2;
        k_2 = k_1;
        k_1 = k_0;
    }

    return k_0;
}