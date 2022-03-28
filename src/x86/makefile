
CPPFLAGS := -std=c++11 -O3 -Iinc.h

ifeq ($(target), )
	target := 0
endif

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@ 

all: main.o $(target).o
	g++ $(target).o main.o -o main
