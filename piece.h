#ifndef PIECE_H
#define PIECE_H

#include "board.h"
#include "coords.h"
class Board; 


struct directionInfo {
    int x; 
    int y; 
    int absx; 
    int absy; 
    int xdir; 
    int ydir; 

    directionInfo(int x_, int y_, int absx_, int absy_, int xdir_, int ydir_) : x(x_), y(y_), absx(absx_), absy(absy_), xdir(xdir_), ydir(ydir_) {}
}; 


class Piece {
    private: 
        bool white; 
        bool taken; 
        bool moved = false; 

    public: 
        virtual bool isValidMove (const Coords &origin, const Coords &destination, const Board &board)= 0; 
        virtual char getSymbol() = 0; 

        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board) = 0; 

        bool take(); 

        bool sameColor(Piece *piece); 

        bool isTaken(); 
        bool isWhite(); 
        bool hasMoved(); 
        bool isMoved(); 
        void setPiece(bool isWhite); 

        static directionInfo getDirectionInfo(const Coords &origin, const Coords &destination); 
};

class Bishop : public Piece {
    
    private: 
        const char symbol = 'B'; 

    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board); 
        char getSymbol(); 
        Bishop(bool white); 


}; 

class Knight : public Piece {
    private: 
        const char symbol = 'N'; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board); 
        char getSymbol(); 
        Knight(bool white); 

}; 

class Rook : public Piece {
    private: 
        const char symbol = 'R'; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board); 
         char getSymbol(); 
        Rook(bool white); 
}; 

class Queen : public Piece {
    private: 
        const char symbol = 'Q'; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board); 
         char getSymbol(); 
        Queen(bool white);
}; 

class King : public Piece {
    private: 
        const char symbol = 'K'; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board); 
         char getSymbol(); 
        King(bool white); 

}; 
class Pawn : public Piece {
    private: 
        const char symbol = 'p'; 
        bool enpassant = false; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board); 
         char getSymbol(); 
         bool  canBeEnpassant(); 
         void setEnpassant(bool whether); 

        Pawn(bool white); 
}; 
#endif
