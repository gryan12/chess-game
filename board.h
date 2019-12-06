#ifndef BOARD_H
#define BOARD_H
#include "piece.h"
#include <vector>
#include "coords.h"

const int BOARD_LENGTH = 8; 
const int BOARD_WIDTH = 8; 

class Piece; 
class Board {
    private: 
        Piece ***boardState; 
        std::vector<Piece*> takenPieces; 
    public:
        bool movePiece(const Coords &origin, const Coords &destination); 
        void printBoard(); 
        Piece* pieceAt(const Coords &location) const; 
        Board(); 
        ~Board();
};
#endif
