#ifndef PIECE_H
#define PIECE_H

#include "board.h"
class Board; 
class Piece {
    private: 
        bool white; 
        bool taken; 

    public: 
        virtual bool isValidMove (const int origin[2], const int destination[2], const Board &board)= 0; 
        virtual char getSymbol() = 0; 

        bool take(); 
        bool isTaken(); 
        bool isWhite(); 
        void setPiece(bool isWhite); 
};

class Bishop : public Piece {
    
    private: 
        const char symbol = 'B'; 

    public: 
        bool isValidMove(const int origin[2], const int destination[2], const Board &board); 
        char getSymbol(); 
        Bishop(int rand); 
}; 

class Knight : public Piece {
    private: 
        const char symbol = 'N'; 
    public: 
        bool isValidMove(const int origin[2], const int destination[2], const Board &board); 
        char getSymbol(); 
        Knight(int rand); 
}; 

class Rook : public Piece {
    private: 
        const char symbol = 'R'; 
    public: 
        bool isValidMove(const int origin[2], const int destination[2], const Board &board); 
         char getSymbol(); 
        Rook(int rand); 
}; 

class Queen : public Piece {
    private: 
        const char symbol = 'Q'; 
    public: 
        bool isValidMove(const int origin[2], const int destination[2], const Board &board); 
         char getSymbol(); 
        Queen(int rand);
}; 

class King : public Piece {
    private: 
        const char symbol = 'K'; 
    public: 
        bool isValidMove(const int origin[2], const int destination[2], const Board &board); 
         char getSymbol(); 
        King(int rand); 

}; 
class Pawn : public Piece {
    private: 
        const char symbol = 'p'; 
    public: 
        bool isValidMove(const int origin[2], const int destination[2], const Board &board); 
         char getSymbol(); 

        Pawn(int rand); 
}; 
#endif
