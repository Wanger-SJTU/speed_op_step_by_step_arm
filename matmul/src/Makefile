
#
# sample makefile
#

CC         := clang++
LINKER     := $(CC)
CFLAGS     := -O3
LDFLAGS    := -lm

OBJS  := main.o utils.o matmul_raw.o
# OBJS  := main.o utils.o matmul_transpose.o
# OBJS  := main.o utils.o gemm_1x4x1.o
# OBJS  := main.o utils.o gemm_4x4x1.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

matmul: clean $(OBJS) 
	$(LINKER) $(OBJS) $(LDFLAGS)  -o main 

run: clean
	make matmul
# ./main 512 512 512
	./main 2 3 4
	make clean

clean:
	rm -f *.o main
	
