hotelFinder: main.o functions.o 
	g++ main.o functions.o -o hotelFinder
myfunctions.o: main.cpp functions.o
	g++ -c myfunctions.cpp
2project2.o: main.cpp functions.h 
	g++ -c main.cpp
Clean:
	rm main.o functions.o hotelFinder