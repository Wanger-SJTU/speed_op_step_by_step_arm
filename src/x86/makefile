
CPPFLAGS := -std=c++11

ifeq ($(target), )
	target := 0
endif

ifeq ($(target), 6)
	CPPFLAGS += -mavx -mavx2 -O2
endif


%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@ 

all: perf

eval: eval.o $(target).o utils.o
	g++ $(target).o eval.o utils.o -o eval

perf: perf.o $(target).o utils.o
	g++ $(target).o perf.o utils.o -o main

clean:
	rm *.o main