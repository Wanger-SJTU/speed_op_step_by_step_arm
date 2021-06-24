all: test.S main.c clean
	${NDK_AS} -o test.o test.S
	${NDK_CC} -c main.c
	${NDK_CC} -o main main.o test.o 

clean:
	rm -rf main *.o