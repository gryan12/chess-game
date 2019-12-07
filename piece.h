#ifndef PIECE_H
#define PIECE_H

#include "board.h"
#include "coords.h"
class Board; 
class Piece {
    private: 
        bool white; 
        bool taken; 
        bool moved = false; 

    public: 
        virtual bool isValidMove (const Coords &origin, const Coords &destination, const Board &board)= 0; 
        virtual char getSymbol() = 0; 

        bool take(); 

        bool sameColor(Piece *piece); 

        bool isTaken(); 
        bool isWhite(); 
        bool hasMoved(); 
        bool isMoved(); 
        void setPiece(bool isWhite); 
};

class Bishop : public Piece {
    
    private: 
        const char symbol = 'B'; 

    public: 
        bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
        char getSymbol(); 
        Bishop(int rand); 
}; 

class Knight : public Piece {
    private: 
        const char symbol = 'N'; 
    public: 
        bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
        char getSymbol(); 
        Knight(int rand); 
}; 

class Rook : public Piece {
    private: 
        const char symbol = 'R'; 
    public: 
        bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
         char getSymbol(); 
        Rook(int rand); 
}; 

class Queen : public Piece {
    private: 
        const char symbol = 'Q'; 
    public: 
        bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
         char getSymbol(); 
        Queen(int rand);
}; 

class King : public Piece {
    private: 
        const char symbol = 'K'; 
    public: 
        bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
         char getSymbol(); 
        King(int rand); 

}; 
class Pawn : public Piece {
    private: 
        const char symbol = 'p'; 
        bool enpassant = false; 
    public: 
        bool isValidMove(const Coords &origin, const Coords &destination, const Board &board); 
         char getSymbol(); 
         bool  canBeEnpassant(); 
         void setEnpassant(bool whether); 

        Pawn(int rand); 
}; 
#endif
