#ifndef BOARD_H
#define BOARD_H
#include "piece.h"
#include <vector>

const int BOARD_LENGTH = 8; 
const int BOARD_WIDTH = 8; 

struct Coords {
    int x; 
    int y; 
}; 

class Piece; 
class Board {
    private: 
        Piece ***boardState; 
        std::vector<Piece*> takenPieces; 
    public:
        bool movePiece(int* origin, int* destination); 
        void printBoard(); 
        Piece* pieceAt(int* location); 
        Board(); 
        ~Board();
};
#endif
