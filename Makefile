all:
	g++ -std=c++11 -O3 -Wall Project1.cpp -lm -o p1Exe

g:
	g++ -std=c++11 -O3 -Wall gerador.cpp -lm -o gerador

clean:
	rm -f *.out p1Exe gerador *.o
