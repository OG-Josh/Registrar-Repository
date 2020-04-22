all: clean myprog
myprog:
	g++ -g -Wall --std=c++11 Assignment4.cpp -o myprog
clean:
	rm -rf myprog core*