all: knowledge

CC = g++
FLAGS = -Wall -O2

knowledge: knowledge.o
	$(CC) $(FLAGS) $^ -o $@

knowledge.o: knowledge.cpp
	$(CC) $(FLAGS) -c $<
