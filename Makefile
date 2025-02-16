all: compile link

compile:
	g++ -g -Isrc/include -c main.cpp

link:
	g++ -g main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
