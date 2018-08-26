all: trip

CC = g++
FLAGS = -std=c++11 -O2

trip: trip.o
	$(CC) $(FLAGS) -o trip trip.o

trip.o: trip.cpp
	$(CC) $(FLAGS) -o trip.o -c trip.cpp
