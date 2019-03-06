CC = gcc
CFLAGS = -I.
DEPS = src/structs.h src/fica.h src/gross.h src/pagectrl.h
OBJ = src/lab2.o src/fica.o src/gross.o src/pagectrl.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

payroll_prgm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
