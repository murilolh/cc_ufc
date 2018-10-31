all: main

main: metodos/problema.o metodos/newtonraphson.o metodos/original.o metodos/modificado.o
	g++  metodos/problema.o metodos/newtonraphson.o metodos/original.o metodos/modificado.o main.cpp -o main.o

problema.o: metodos/problema.h metodos/newtonraphson.h metodos/problema.cpp
	g++ -c metodos/problema.cpp

newtonraphson.o: metodos/newtonraphson.h metodos/newtonraphson.cpp
	g++ -c metodos/newtonraphson.cpp

original.o: metodos/newtonraphson.h metodos/original.h metodos/original.cpp
	g++ -c metodos/original.cpp

modificado.o:  metodos/newtonraphson.h metodos/modificado.h  metodos/modificado.cpp
	g++ -c metodos/modificado.cpp
