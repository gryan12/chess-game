CC = g++
CFLAGS = -Wall -g
test: test.cpp piece.cpp board.cpp 
	$(CC) $(CFLAGS) test.cpp piece.cpp board.cpp -o test


