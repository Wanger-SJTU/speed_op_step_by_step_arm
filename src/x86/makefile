
CPPFLAGS := -std=c++11  -mavx -mavx2 -O2

ifeq ($(target), )
	target := 0
endif

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@ 

all: perf

eval: eval.o $(target).o
	g++ $(target).o eval.o -o main

perf: perf.o $(target).o
	g++ $(target).o perf.o -o main

clean:
	rm *.o main