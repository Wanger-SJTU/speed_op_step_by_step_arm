CC=${NDK_CC}
CXX=${NDK_CXX}



#
# sample makefile
#

CC         := g++
LINKER     := $(CC)
CFLAGS     := -O3
LDFLAGS    := -lm

OBJS  := main.o matmul_raw.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

matmul: $(OBJS)
	$(LINKER) $(OBJS) $(LDFLAGS)  -o main 

run:	
	make matmul
	./main 3 512 512

clean:
	rm -f *.o 
	rm main
