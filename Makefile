all:
	g++ main.cpp shape.cpp field.cpp  -o program -O0 -ggdb -Wall -Wextra -lncurses
