#include "board.h"
#include <iostream> 
#include <stdlib.h>
#include "piece.h"

//piece

bool outOfBounds(const Coords &destination) {
    if (destination.x > BOARD_LENGTH || destination.y > BOARD_LENGTH) {
        return true; 
    }
    return false; 
}


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

bool Pawn::canBeEnpassant() {
    return enpassant; 
}

bool Piece::sameColor(Piece *piece) {
    return (piece->isWhite() == isWhite()); 
}

void Pawn::setEnpassant(bool can) {
    enpassant = can; 
}
//pawn
//this... this should be static, shouldn't it?
//need to add check for when trying to move a pwn to its backrank
bool Pawn::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {

    if (origin.x > BOARD_LENGTH || origin.y > BOARD_LENGTH) {
        return false; 
    }

    //get abs difference
    int xdif, ydif; 
    ydif = abs(origin.y - destination.y); 
    xdif = abs(origin.x - destination.x); 

    //if invalid magnitudes
    if (xdif > 2 || ydif > 1) {
        return false; //trying to more than 2 sqaures / not 1 diagonally forwards (for taking)
    }

    if (hasMoved() && xdif == 2) {
        return false;//trying to move forward 2 squares after the first move
    } 

    //its here. i am tryng to acess value of anull ponter. 
    if (ydif > 1 && board.pieceAt(destination) == NULL) {
        if (!enpassant) {
            return false; //trying to take non-existant piece / own piece
        }

        else {

        }
    } 

    else if (board.pieceAt(destination) && sameColor(board.pieceAt(destination))) {
        return false; //trying to take own color piece
    }

    //if trying to advance, check there is no piece int he way. 
    //i think i cna leave checking for check in the board class, p sure
    if (ydif == 0) {

        Coords c(origin.x+1, origin.y); 

        if (board.pieceAt(c)) {
            return false; // piece in the way
        }

        if (board.pieceAt(destination)) {
            return false; //piece at endpoint
        }

    } 
    return true; 
}
char Pawn::getSymbol()  {
    return symbol;
}

//bishop
bool Bishop::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {

    //if oob
    if (destination.x > BOARD_LENGTH || destination.y > BOARD_LENGTH) {
        return false; 
    }

    //get absolute difference
    int xdif, ydif; 
    ydif = abs(origin.y - destination.y); 
    xdif = abs(origin.x - destination.x); 

    //as move diagonally, vector magnitudes must aways be equal. 
    //any square for which this holds true will be on same colord diagonal
    if (xdif != ydif) {
        return false; 
    }

    //get actual difference;
    int x, y; 
    x = origin.x - destination.x; 
    y = origin.y - destination.y;


    //the directions, either positive or negative 1
    int xdir = xdif / x; 
    int ydir = ydif / y; 

    //trying to take same color piece
    if (board.pieceAt(destination) && sameColor(board.pieceAt(destination))) {
        return false; 
    }

    Coords intermediateSq(origin.x, origin.y); 
    while (intermediateSq != destination) {
        intermediateSq.x += xdir; 
        intermediateSq.y += ydir; 

        //there is piece in the way
        if (board.pieceAt(intermediateSq)) {
            return false; 
        }
    }

    return true; 
}
char Bishop::getSymbol()  {
    return symbol;
}
//knight
bool Knight::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {

   if (destination.x > BOARD_LENGTH || destination.y > BOARD_LENGTH) {
       return false; 
   } 


    //get abs differences
    int xdif, ydif; 
    xdif = abs(origin.x - destination.x); 
    ydif = abs(origin.y - destination.y); 

    //if same-colord piece at destination
    if (board.pieceAt(destination) && sameColor(board.pieceAt(destination))) {
        return false; 
    }

    if ((xdif == 2 && ydif == 1) || (xdif == 1 && ydif == 2)) {
        return true; 
    }
    return false; 
}

char Knight::getSymbol()  {
    return symbol;
}
//rook
bool Rook::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {

   if (destination.x > BOARD_LENGTH || destination.y > BOARD_LENGTH) {
       return false; 
   } 
    //get abs differences
    int xdif, ydif; 
    xdif = abs(origin.x - destination.x); 
    ydif = abs(origin.y - destination.y); 

    //rooks can only move in EITHer x or y axis
    if (xdif && ydif) {
        return false; 
    }

    //get actual difference;
    int x, y; 
    x = origin.x - destination.x; 
    y = origin.y - destination.y;

    //the directions, one will be 0
    int xdir, ydir; 
    xdir = (x==0) ? 0 : xdif / x; 
    ydir = (y==0) ? 0 : ydif / y; 


    //only one of xdir or ydir should be non-zero, just quicker this way
    Coords intermediateSq(origin.x, origin.y); 
    while (intermediateSq != destination) {
        intermediateSq.x += xdir; 
        intermediateSq.y += ydir; 
        if (board.pieceAt(intermediateSq)) {
            return false; 
        }
    }

    return true; 
}
char Rook::getSymbol()  {
    return symbol;
}
//queen
bool Queen::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {

    if (outOfBounds(destination)) {
        return false; 
    }

    //get abs differences
    int xdif, ydif; 
    xdif = abs(origin.x - destination.x); 
    ydif = abs(origin.y - destination.y); 

    //get actual difference;
    int x, y; 
    x = origin.x - destination.x; 
    y = origin.y - destination.y;

    //directions - warning, could be 0
    int xdir, ydir; 
    xdir = (x==0) ? 0 : xdif / x; 
    ydir = (y==0) ? 0 : ydif / y; 


    //if trying to take own piece
    if (board.pieceAt(destination)) {
        if (sameColor(board.pieceAt(destination))) {
                return false; 
        }
    }

    Coords intermediateSq (origin.x, origin.y); 

    //if moving like a bishop
    if (xdif == ydif) {
        while (intermediateSq != destination) {
            intermediateSq.x += xdir; 
            intermediateSq.y += ydir; 

            //there is piece in the way
            if (board.pieceAt(intermediateSq)) {
                return false; 
            }
        }
    }
    //else if moving like rook
    else if (xdif && !ydif || ydif && !xdif) {
        while (intermediateSq != destination) {
            intermediateSq.x += xdir; 
            intermediateSq.y += ydir; 
            if (board.pieceAt(intermediateSq)) {
                return false; 
            }
        }
    }

    //if moving like neither a bishop or a rook
    else {
        return false; 
    }

    return true; 
}
char Queen::getSymbol()  {
    return symbol;
}

//king
bool King::isValidMove(const Coords &origin, const Coords &destination, const Board &board) {
    if (outOfBounds(destination)) {
        return false; 
    }

    int xdif, ydif;
    xdif = abs(origin.x - destination.x); 
    ydif = abs(origin.y - destination.y); 

    if (xdif > 1 || ydif > 1) {
        return false; 
    }

    //get actual difference (which is also direction)
    int xdir, ydir; 
    xdir = origin.x - destination.x; 
    ydir = origin.y - destination.y;

    bool kingSide; 

    //trying to castle
    //king must not have moved; releavn rook must not have moved; must be no pieces in the way 
    //nb all check logic to be handled by board
    if (!hasMoved() && (xdir == 0 && ydir == 2)) {

        bool queenSide = (ydir < 0); 

        Coords endSq(destination.x, destination.y+1); 

        if (queenSide) {
            endSq.y -= 7; 
        }
        //should be rook
        Piece *endPiece = board.pieceAt(endSq); 

        Coords intermediateSq(origin.x, origin.y); 
        if (endPiece) {
            if (endPiece->getSymbol() == 'R') {
                if (!endPiece->hasMoved()) {
                    int n = 3; 
                    //if pieces in the way
                    if (queenSide) {
                        while (n--) {
                            //if nay piece between rook and king
                            if (board.pieceAt(destination.x, endSq.y+n)) {
                                return false; 
                            }
                        }
                    } else {

                        n = 2; 
                        while (n--) {
                            if (board.pieceAt(destination.x, destination.y-n)) {
                                return false; 
                            }
                        }
                    }
                    return true; 
                }
            }
        }
        return false; 
    }

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




