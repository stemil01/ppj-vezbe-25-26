main: main.o dinamicki_niz.o
	g++ main.o dinamicki_niz.o -o main

main.o: main.cpp
	g++ -c main.cpp

dinamicki_niz.o: dinamicki_niz.cpp
	g++ -c dinamicki_niz.cpp

.PHONY: clean
clean:
	rm -f *.o main
