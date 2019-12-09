#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "piece.h"
#include <vector>
#include "coords.h"

const int BOARD_LENGTH = 8; 
const int BOARD_WIDTH = 8; 

class Piece; 
class ChessBoard {
    private: 

        /*start data members */
        /* representation of board. 2d array of pointers to pieces.*/
        Piece ***boardState; 

        /*dstructure holding pointers to pieces that have been taken */
        std::vector<Piece*> takenPieces; 
        
        int moveNumber = 0; 

        /*given how costly it is to check for these, keep track as 
        data members */
        bool isCheckMate = false; 
        bool isStaleMate = false; 
        /*end data members */

        //return true if whites turn
        bool whitesTurn(); 
        //internal helper func
        void freeBoard(); 
    public:
        //if it is logically valid for a piece to move to this square, 
        //and this move would not result in moving player (pos still) being
        //in check, return true
        bool movePiece(const Coords &origin, const Coords &destination); 

        //return pointer to piece at coordinates @location
        Piece* pieceAt(const Coords &location) const; 
        //above but overloaded to take raw int coordinates
        Piece* pieceAt(int x, int y) const; 

        //returns true if (white, if not black) is in check. 
        bool inCheck(bool white); 

        //above but takes Coords object. 
        bool inCheck(const Coords &kingLocation, bool white); 

        //returns true if @white is in checkmate
        bool isCheckmate(bool white); 

        //returns the Coords of the king of color described by @white
        Coords getKingSq(bool white); 

        //takes string input, if input valid calls movePiece(); 
        bool submitMove(std::string start, std::string end); 

        //returns true if @white has a logically valid and legal move available
        bool hasValidMove(bool white); 

        //deallocate mem for pieces, reset members and set new pieces at starting pos
        void resetBoard(); 

        //allocates memory for pieces, places at appropriate starting positions
        void setNewPieces(); 

        //reports a move from @origin to@destination to std::cout 
        void announceMove(const Coords &origin, const Coords &destination, bool takenAPiece); 

        //returns true if the @whiteKing would be in check if it moved to @destination
        bool wouldBeCheck(const Coords &origin, const Coords &destination, bool whiteKing); 

        //returns true if player is in stalemate or checkmate
        bool gameOver(); 

        //returns the current move number
        int getMoveNumber(); 

        //constructor. allocate memory for the board
        ChessBoard(); 
        //destructor. deallocate memory for all pieces and for board
        ~ChessBoard();
};
#endif
