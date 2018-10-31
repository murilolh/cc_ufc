all: main

main: metodos/contexto.o metodos/metodo.o metodos/gaussjacob.o metodos/gaussseidel.o
	g++  metodos/contexto.o metodos/metodo.o metodos/gaussjacob.o metodos/gaussseidel.o main.cpp -o main.o


contexto.o: metodos/contexto.h metodos/metodo.h metodos/contexto.cpp
	g++ -c metodos/contexto.cpp

metodo.o: metodos/metodo.h metodos/metodo.cpp
	g++ -c metodos/metodo.cpp

gaussjacob.o: metodos/metodo.h metodos/gaussjacob.h metodos/gaussjacob.cpp
	g++ -c metodos/gaussjacob.cpp

gaussseidel.o: metodos/metodo.h metodos/gaussseidel.h metodos/gaussseidel.cpp
	g++ -c metodos/gaussseidel.cpp
