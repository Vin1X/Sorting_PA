COM_TARGET = com
PAR_TARGET = par
RAND_TARGET = rand_z

$(PAR_TARGET): $(PAR_TARGET).o $(COM_TARGET).o $(RAND_TARGET).o
	gcc -o $(PAR_TARGET).exe $(PAR_TARGET).o $(COM_TARGET).o $(RAND_TARGET).o

$(PAR_TARGET).o: src/$(PAR_TARGET).c include/$(PAR_TARGET).h
	gcc -c -o $(PAR_TARGET).o src/$(PAR_TARGET).c

$(COM_TARGET).o: src/$(COM_TARGET).c include/$(PAR_TARGET).h
	gcc -c -o $(COM_TARGET).o src/$(COM_TARGET).c

$(RAND_TARGET).o: src/$(RAND_TARGET).c include/$(RAND_TARGET).h
	gcc -c -o $(RAND_TARGET).o src/$(RAND_TARGET).c

run: $(PAR_TARGET)
	$(PAR_TARGET).exe

clean:
	del *.exe *.o *.log