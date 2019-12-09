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
        int moveNumber = 0; 



        bool whitesTurn(); 


    public:
        bool movePiece(const Coords &origin, const Coords &destination); 
        void printBoard(); 
        Piece* pieceAt(const Coords &location) const; 
        Piece* pieceAt(int x, int y) const; 

        bool inCheck(bool isWhiteKing); 
        bool inCheck(const Coords &kingLocation, bool white); 
        bool isCheckmate(bool isWhiteKing); 
        Coords getKingSq(bool white); 
        bool submitMove(std::string start, std::string end); 

        void resetBoard(); 
        void setNewPieces(); 
        void announceMove(const Coords &origin, const Coords &destination); 

        bool wouldBeCheck(const Coords &origin, const Coords &destination, bool whiteKing); 
        
        
        int getMoveNumber(); 

        void operator=(Board otherBoard); 

        Board(); 
        ~Board();
};
#endif
