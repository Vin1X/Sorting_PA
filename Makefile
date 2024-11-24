SEQ_TARGET = seq
COM_TARGET = com
PAR_TARGET = par

$(SEQ_TARGET): $(SEQ_TARGET).o $(COM_TARGET).o
	gcc -o $(SEQ_TARGET).exe $(SEQ_TARGET).o $(COM_TARGET).o

$(SEQ_TARGET).o: src/$(SEQ_TARGET).c include/$(SEQ_TARGET).h
	gcc -c -o $(SEQ_TARGET).o src/$(SEQ_TARGET).c

$(PAR_TARGET).exe: $(PAR_TARGET).o $(COM_TARGET).o
	gcc -o $(PAR_TARGET).exe $(PAR_TARGET).o $(COM_TARGET).o

$(PAR_TARGET).o: src/$(PAR_TARGET).c include/$(PAR_TARGET).h
	gcc -c -o $(PAR_TARGET).o src/$(PAR_TARGET).c

$(COM_TARGET).o: src/$(COM_TARGET).c include/$(SEQ_TARGET).h
	gcc -c -o $(COM_TARGET).o src/$(COM_TARGET).c

run-seq: $(SEQ_TARGET)
	$(SEQ_TARGET).exe

run-par: $(PAR_TARGET)
	$(PAR_TARGET).exe

clean:
	del *.exe *.o
