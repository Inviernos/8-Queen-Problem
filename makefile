queen: main.o 
	g++ main.o -o queen
main.o: main.cpp
	g++ -c main.cpp
clean: 
	rm -f *.o
remove:
	rm -f * queen
removeall:
	rm -f *.o
	rm -f queen
	ls