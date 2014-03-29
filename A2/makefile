all: simProgram

simProgram: main.o Filereader.o sim.h queue.o fcfs.o rr.o common_sim.o
	gcc -o simProgram main.o Filereader.o queue.o fcfs.o rr.o common_sim.o -lfl -lm
	
main.o: main.c Filereader.o 
	gcc -Wall -c main.c

Filereader.o:Filereader.c Filereader.h queue.c queue.h fcfs.h fcfs.c rr.c rr.h common_sim.c common_sim.h
	gcc -Wall -c Filereader.c queue.c fcfs.c rr.c common_sim.c
clean:
	rm -f *.o
	rm -f simProgram
