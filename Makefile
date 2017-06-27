all: program1

program1: util.cpp commands.cpp shell.cpp
	g++ -std=c++11 util.cpp commands.cpp shell.cpp -o shell
