#ifndef PIECE_H
#define PIECE_H

#include "chessboard.h"
#include "coords.h"


/* this file declares the abstract class Piece and all of its derived classes: 
 * Pawn, Knight, Bishop, Rook, Queen, King  */ 


//struct containing result of useful calcs for difference
//between two squares
struct directionInfo {
    int x; 
    int y; 
    int absx; 
    int absy; 
    int xdir; 
    int ydir; 

    directionInfo(int x_, int y_, int absx_, int absy_, int xdir_, int ydir_) : x(x_), y(y_), absx(absx_), absy(absy_), xdir(xdir_), ydir(ydir_) {}
}; 

class ChessBoard; 
//abstract class. contains three pure virtual fucns
class Piece {
    private: 
        /*start data members */
        bool white; 
        bool taken; 
        bool moved = false; 
        /* end data members */ 

    public: 
        //when overriden should return true if movement from @origin to @destination is in accordance
        //with the movment patterns of the derived piece, and if there are no pieces blocking the path
        //of the piece. NB: function does not give any consideration to the safety of either king. 
        virtual bool isValidMove (const Coords &origin, const Coords &destination, const ChessBoard &board)= 0; 
        virtual char getSymbol() = 0; 

        //should return true if the piece is putting the opposing king in check. 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const ChessBoard &board) = 0; 

        virtual std::string toString() = 0; 

        bool take(); 
        bool sameColor(Piece *piece); 
        bool isTaken(); 
        bool isWhite(); 
        bool isBlack(); 
        bool hasMoved(); 
        void isMoved(); 
        void setPiece(bool isWhite); 

        static directionInfo getDirectionInfo(const Coords &origin, const Coords &destination); 

        virtual ~Piece(); 
};

class Bishop : public Piece {
    
    private: 
        const char symbol = 'B'; 

    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const ChessBoard &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const ChessBoard &board); 
        virtual std::string toString(); 
        char getSymbol(); 
        Bishop(bool white); 


        ~Bishop(); 
}; 

class Knight : public Piece {
    private: 
        const char symbol = 'N'; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const ChessBoard &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const ChessBoard &board); 
        virtual std::string toString(); 

        char getSymbol(); 

        Knight(bool white); 

        ~Knight(); 

}; 

class Rook : public Piece {
    private: 
        const char symbol = 'R'; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const ChessBoard &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const ChessBoard &board); 
        virtual std::string toString(); 
        char getSymbol(); 
        Rook(bool white); 

        ~Rook(); 
}; 

class Queen : public Piece {
    private: 
        const char symbol = 'Q'; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const ChessBoard &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const ChessBoard &board); 
        virtual std::string toString(); 
        char getSymbol(); 
        Queen(bool white);
        ~Queen(); 
}; 

class King : public Piece {
    private: 
        const char symbol = 'K'; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const ChessBoard &board); 
        //worth noting that not legal/possible for a king to actually check a king
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const ChessBoard &board); 
        virtual std::string toString(); 
        char getSymbol(); 
        King(bool white); 
        ~King(); 

}; 
class Pawn : public Piece {
    private: 
        const char symbol = 'p'; 
        bool enpassant = false; 
    public: 
        virtual bool isValidMove(const Coords &origin, const Coords &destination, const ChessBoard &board); 
        virtual bool checkingKing(const Coords &piece, const Coords &kingLocation, const ChessBoard &board); 
        virtual std::string toString(); 
        char getSymbol(); 
        bool  canBeEnpassant(); 
        void setEnpassant(bool whether); 
        Pawn(bool white); 
        ~Pawn(); 
}; 
#endif
