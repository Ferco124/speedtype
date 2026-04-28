profile.o: profile.h profile.cpp
	g++ -c profile.cpp
main.o: main.h profile.h main.cpp
	g++ -c main.cpp
speedtype: main.o profile.o
	g++ main.o profile.o -o speedtype
clean:
	rm -f profile.o main.o speedtype
.PHONY: clean