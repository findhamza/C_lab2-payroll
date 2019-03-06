CC=gcc
CFLAGS=-I.

lab1: src/lab2.o
	$(CC) -o payroll_prgm src/lab2.o src/gross.c src/fica.c src/pagectrl.c
