fib_lin.o: fib_lin.c
	gcc -c -g -o fib_lin.o fib_lin.c

main.o: main.c
	gcc -g -o main main.c

fib_rec.o: fib_rec.c
	gcc -c -g -o fib_rec.o fib_rec.c

main: main.o fib_rec.o
	gcc &^ -o $@