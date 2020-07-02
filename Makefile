run: main.o threads.o
	g++ -std=c++11 main.o threads.o -o run -lpthread

main.o: main.cpp Vector.h
	g++ -c -std=c++11 main.cpp

threads.o: threads.cpp threads.h Vector.h
	g++ -c -std=c++11 threads.cpp

clean:
	rm *.o run