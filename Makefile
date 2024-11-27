CC = gcc
CFLAGS = -Wall -pthread -Iinclude -O2

SEQ_TARGET = seq
PAR_TARGET = par
COM_TARGET = com

SEQ_OBJ = src/seq.o
PAR_OBJ = src/par.o
COM_OBJ = src/com.o

$(SEQ_TARGET): $(SEQ_OBJ) $(COM_OBJ)
	$(CC) $(CFLAGS) -o $(SEQ_TARGET) $(SEQ_OBJ) $(COM_OBJ)

src/seq.o: src/seq.c include/seq.h include/com.h
	$(CC) $(CFLAGS) -c -o src/seq.o src/seq.c

$(PAR_TARGET): $(PAR_OBJ) $(COM_OBJ)
	$(CC) $(CFLAGS) -o $(PAR_TARGET) $(PAR_OBJ) $(COM_OBJ)

src/par.o: src/par.c include/par.h include/com.h
	$(CC) $(CFLAGS) -c -o src/par.o src/par.c

$(COM_OBJ): src/com.c include/com.h
	$(CC) $(CFLAGS) -c -o src/com.o src/com.c

run-seq: $(SEQ_TARGET)
	./$(SEQ_TARGET)

run-par: $(PAR_TARGET)
	./$(PAR_TARGET)

clean:
	del src\*.o $(SEQ_TARGET) $(PAR_TARGET)
