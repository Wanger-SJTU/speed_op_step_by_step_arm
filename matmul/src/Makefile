
#
# sample makefile
#

CC         := clang++
LINKER     := $(CC)
CFLAGS     := -O3
LDFLAGS    := -lm

# OBJS  := main.o matmul_raw.o
OBJS  := main.o matmul_transpose.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

matmul: clean $(OBJS) 
	$(LINKER) $(OBJS) $(LDFLAGS)  -o main 

run: clean
	make matmul
	./main 512 512 512

clean:
	rm -f *.o main
	
