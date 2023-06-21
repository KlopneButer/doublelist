main:
	g++ -std=c++17 main.cpp
	./a.out

test:
	g++ mytests.cc -std=c++17 -lgtest
	./a.out
