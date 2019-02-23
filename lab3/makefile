all: A B C D

A: A.o
	g++ A.o -o A -pthread -lrt
B: B.o
	g++ B.o -o B -pthread -lrt
C: C.o
	g++ C.o -o C -pthread -lrt
D: D.o
	g++ D.o -o D -pthread -lrt
A.o: A.cpp
	g++ -std=c++11 -Wall -pthread -c A.cpp -o A.o -lrt
B.o: B.cpp
	g++ -std=c++11 -Wall -pthread -c B.cpp -o B.o -lrt
C.o: C.cpp
	g++ -std=c++11 -Wall -pthread -c C.cpp -o C.o -lrt
D.o: D.cpp
	g++ -std=c++11 -Wall -pthread -c D.cpp -o D.o -lrt
