
CPPFLAGS := -std=c++11 # -O3 -I./

ifeq ($(target), )
	target := 0
endif

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@ 

all: perf

eval: eval.o $(target).o
	g++ $(target).o eval.o -o main

perf: main.o $(target).o
	g++ $(target).o main.o -o main

clean:
	rm *.o main