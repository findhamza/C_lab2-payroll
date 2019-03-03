CC=gcc
CFLAGS=-I.

lab1: lab2.o
	$(CC) -o payroll_prgm lab2.o gross.c fica.c pagectrl.c
