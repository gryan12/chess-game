#include "board.h"
#include <stdlib.h>
#include "piece.h"

//piece
bool Piece::isWhite() {
    return white;
}
void Piece::setPiece(bool isWhite) {
    white = isWhite; 
}

bool Piece::hasMoved() {
    return moved; 
}

bool Piece::isMoved() {
    moved = true; 
}
//pawn
bool Pawn::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {

    int xdif, ydif; 
    ydif = abs(origin.y - destination.y); 
    if (ydif) {
        return false; //do exceptions here e.g. throw ILLEGAL_MOVE
    }

    xdif = abs(origin.x - destination.x); 
    if (xdif > 2) {
        return false;
    }
    if (hasMoved && xdif == 2) {
        return false
    }

    Coords c(origin+1, origin); 
    if (board.pieceAt(c)) {
        return false; // piece in the way
    }
    
    if (board.pieceAt(destination)) {
        return false; //piece at endpoint
    }

    
    
    return true; 
}
char Pawn::getSymbol()  {
    return symbol;
}

//bishop
bool Bishop::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {
    return true; 
}
char Bishop::getSymbol()  {
    return symbol;
}
//knight
bool Knight::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {
    return true; 
}
char Knight::getSymbol()  {
    return symbol;
}
//rook
bool Rook::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {
    return true; 
}
char Rook::getSymbol()  {
    return symbol;
}
//queen
bool Queen::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {
    return true; 
}
char Queen::getSymbol()  {
    return symbol;
}

//king
bool King::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {
    return true; 
}
char King::getSymbol()  {
    return symbol;
}

Knight::Knight(int rand) {
    setPiece(rand); 
}
Bishop::Bishop(int rand) {
    setPiece(rand); 
}
Queen::Queen(int rand) {
    setPiece(rand); 
}
King::King(int rand) {
    setPiece(rand); 
}
Rook::Rook(int rand) {
    setPiece(rand); 
}
Pawn::Pawn(int rand) {
    setPiece(rand); 
}




