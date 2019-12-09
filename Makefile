CC = g++
CFLAGS = -Wall -g
test: test.cpp piece.cpp chessboard.cpp 
	$(CC) $(CFLAGS) test.cpp piece.cpp chessboard.cpp -o test


