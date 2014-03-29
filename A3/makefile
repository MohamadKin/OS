all: dine hole

dine: dinning

holes:hole

dinning: main.o
	gcc -o dinning main.o dinning.o -lfl -lm -lpthread

main.o: Pro1/common.h Pro1/main.c Pro1/dinning.c
	gcc -Wall -c Pro1/main.c Pro1/dinning.c

hole: holes.o
	gcc -o hole  holes.o memSim.o fileReader.o -lfl -lm

holes.o: Pro2/commonSim.h Pro2/fileReader.h Pro2/holes.c Pro2/fileReader.c Pro2/memSim.c
	gcc -Wall -c Pro2/holes.c Pro2/fileReader.c Pro2/memSim.c
	
clean:
	rm -f *.o
	rm -f dinning
	rm -f hole
