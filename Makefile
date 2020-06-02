all:
	g++ usr/main.cpp src/lexem.cpp \-I headers/ -o bin/main -Wall -Werror
