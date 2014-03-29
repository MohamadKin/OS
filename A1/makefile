all: shellProgram

shellProgram: myshell.o lex.yy.c systemCmd.o
	gcc -o shellProgram myshell.o systemCmd.o lex.yy.c -lfl -lm
	
myshell.o: myshell.c systemCmd.o
	gcc -Wall -c myshell.c

lex.yy.c: lex.c
	flex lex.c

systemCmd.o:systemCmd.c systemCmd.h
	gcc -Wall -c systemCmd.c
clean:
	rm -f *.o
	rm -f lex.yy.c
	rm -f shellProgram
