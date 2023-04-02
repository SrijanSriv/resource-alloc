all: main.cpp fcfs.cpp minmin.cpp maxmin.cpp
	g++ -o test fcfs.cpp minmin.cpp maxmin.cpp main.cpp -I .
fcfs: main.cpp fcfs.cpp
	g++ -o test fcfs.cpp main.cpp -I .
minmin: main.cpp minmin.cpp
	g++ -o test minmin.cpp main.cpp -I .
maxmin: main.cpp minmin.cpp
	g++ -o test maxmin.cpp main.cpp -I .
run:
	./test
clean:
	rm ./test