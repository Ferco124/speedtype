game.o: game.h game.cpp
	g++ -c game.cpp
profile.o: profile.h profile.cpp
	g++ -c profile.cpp
main.o: game.h profile.h main.cpp
	g++ -c main.cpp
speedtype: game.o main.o profile.o
	g++ game.o main.o profile.o -o speedtype
clean:
	rm -f game.o profile.o main.o speedtype
.PHONY: clean