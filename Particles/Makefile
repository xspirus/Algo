all: particles particles_v2 particles_final

particles_final: particles_final.o
	g++ -o particles_final particles_final.o

particles: particles.o
	g++ -o particles particles.o

particles_v2: particles_v2.o
	g++ -o particles_v2 particles_v2.o

particles_final.o: particles_final.cpp
	g++ -c -Wall -O2 particles_final.cpp

particles.o: particles.cpp
	g++ -c -Wall -O2 particles.cpp

particles_v2.o: particles_v2.cpp
	g++ -c -Wall -O2 particles_v2.cpp
