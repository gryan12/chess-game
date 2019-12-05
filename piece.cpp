#include "board.h"
#include "piece.h"

//piece
bool Piece::isWhite() {
    return white;
}
void Piece::setPiece(bool isWhite) {
    white = isWhite; 
}
//pawn
bool Pawn::isValidMove(const int origin[2], const int destination[2], const Board &board) {
    return true; 
}
char Pawn::getSymbol()  {
    return symbol;
}

//bishop
bool Bishop::isValidMove(const int origin[2], const int destination[2], const Board &board) {
    return true; 
}
char Bishop::getSymbol()  {
    return symbol;
}
//knight
bool Knight::isValidMove(const int origin[2], const int destination[2], const Board &board) {
    return true; 
}
char Knight::getSymbol()  {
    return symbol;
}
//rook
bool Rook::isValidMove(const int origin[2], const int destination[2], const Board &board) {
    return true; 
}
char Rook::getSymbol()  {
    return symbol;
}
//queen
bool Queen::isValidMove(const int origin[2], const int destination[2], const Board &board) {
    return true; 
}
char Queen::getSymbol()  {
    return symbol;
}

//king
bool King::isValidMove(const int origin[2], const int destination[2], const Board &board) {
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




