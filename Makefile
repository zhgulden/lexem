all:
	g++ -std=c++11 usr/main.cpp src/lexem.cpp \-I headers/ -o bin/main -Wall -Werror
