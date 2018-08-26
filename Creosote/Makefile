all: creosote creosote_v2

CC = g++
FLAGS = -Wall -O2

creosote_v2: creosote_v2.o
	$(CC) $(FLAGS) $^ -o $@

creosote_v2.o: creosote_v2.cpp
	$(CC) $(FLAGS) -c $<

creosote: creosote.o
	$(CC) $(FLAGS) $^ -o $@

creosote.o: creosote.cpp
	$(CC) $(FLAGS) -c $<
