all:
	g++ -std=c++11 -O3 -Wall Project1.cpp -lm -o p1Exe

clean:
	rm -f *.out p1Exe *.o
