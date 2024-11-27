COM_TARGET = com
SEQ_TARGET = seq
RAND_TARGET = rand_z

$(SEQ_TARGET): $(SEQ_TARGET).o $(COM_TARGET).o $(RAND_TARGET).o
	gcc -o $(SEQ_TARGET).exe $(SEQ_TARGET).o $(COM_TARGET).o $(RAND_TARGET).o

$(SEQ_TARGET).o: src/$(SEQ_TARGET).c include/$(SEQ_TARGET).h
	gcc -c -o $(SEQ_TARGET).o src/$(SEQ_TARGET).c

$(COM_TARGET).o: src/$(COM_TARGET).c include/$(SEQ_TARGET).h
	gcc -c -o $(COM_TARGET).o src/$(COM_TARGET).c

$(RAND_TARGET).o: src/$(RAND_TARGET).c include/$(RAND_TARGET).h
	gcc -c -o $(RAND_TARGET).o src/$(RAND_TARGET).c

run: $(SEQ_TARGET)
	$(SEQ_TARGET).exe

clean:
	del *.exe *.o *.log