all: gridmeeting students

students: students.o
	g++ -o students students.o

students.o: students.cpp
	g++ -c -std=c++11 -O2 students.cpp

gridmeeting: gridmeeting.o mergesort.o distance.o
	g++ -o gridmeeting gridmeeting.o mergesort.o distance.o

gridmeeting.o: gridmeeting.cpp
	g++ -c -O2 gridmeeting.cpp

mergesort.o: mergesort.cpp
	g++ -c -O2 mergesort.cpp

distance.o: distance.cpp
	g++ -c -O2 distance.cpp

clean:
	rm students gridmeeting students.o gridmeeting.o mergesort.o distance.o
