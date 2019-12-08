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

directionInfo Piece::getDirectionInfo(const Coords &origin, const Coords &destination) {

    //get actual difference;
    int x, y; 
    x = destination.x - origin.x; 
    y = destination.y - origin.y; 

    //get abs differences
    int xdif, ydif; 
    xdif = abs(x); 
    ydif = abs(y); 

    //directions 
    int xdir, ydir; 
    xdir = (x==0) ? 0 : xdif / x; 
    ydir = (y==0) ? 0 : ydif / y; 

    directionInfo info(x, y, xdif, ydif, xdir, ydir); 
    return info; 
}

bool Piece::isWhite() {
    return white;
}
bool Piece::isBlack() {
    return !white;
}
void Piece::setPiece(bool isWhite) {
    white = isWhite; 
}

bool Piece::hasMoved() {
    return moved; 
}

void Piece::isMoved() {
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


    directionInfo info(getDirectionInfo(origin, destination)); 


    if (origin.x > BOARD_LENGTH || origin.y > BOARD_LENGTH) {
        return false; 
    }

    //if invalid magnitudes
    if (info.absx > 2 || info.absy > 1) {
        return false; //trying to more than 2 sqaures / not 1 diagonally forwards (for taking)
    }

    //check pawns moving in the apprpriate directions
    if (isWhite() && info.xdir < 0) {
        return false; 
    }  
    else if (isBlack() && info.xdir > 0) {
        return false; 
    }

    if (hasMoved() && info.absx == 2) {
        return false;//trying to move forward 2 squares after the first move
    } 

    //its here. i am tryng to acess value of anull ponter. 
    if (info.absy > 1 && board.pieceAt(destination) == NULL) {
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
    if (info.absy == 0) {

        //if moving two spaces check the intermediate square
        if (info.absx == 2) {
            Coords c(origin.x+info.xdir, origin.y); 
            if (board.pieceAt(c)) {
                return false; // piece in the way
            }
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

    directionInfo info(getDirectionInfo(origin, destination)); 

    //if oob
    if (destination.x > BOARD_LENGTH || destination.y > BOARD_LENGTH) {
        return false; 
    }

    //as move diagonally, vector magnitudes must aways be equal. 
    //any square for which this holds true will be on same colord diagonal
    if (info.absx != info.absy) {
        
        return false; 
    }

    //trying to take same color piece
    if (board.pieceAt(destination) && sameColor(board.pieceAt(destination))) {
        return false; 
    }

    Coords intermediateSq(origin.x, origin.y); 

    intermediateSq.x += info.xdir; 
    intermediateSq.y += info.ydir; 
    while (intermediateSq != destination) {

        //there is piece in the way
        if (board.pieceAt(intermediateSq)) {
            return false; 
        }
        intermediateSq.x += info.xdir; 
        intermediateSq.y += info.ydir; 
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
    std::cout <<"\nStart of rook valid\n"; 

   if (destination.x > BOARD_LENGTH || destination.y > BOARD_LENGTH) {
       return false; 
   } 
//    //get abs differences
//    int xdif, ydif; 
//    xdif = abs(origin.x - destination.x); 
//    ydif = abs(origin.y - destination.y); 
//
//    //rooks can only move in EITHer x or y axis
//    if (xdif && ydif) {
//        return false; 
//    }
//
//    //get actual difference;
//    int x, y; 
//    x = origin.x - destination.x; 
//    y = origin.y - destination.y;
//
//    //the directions, one will be 0
//    int xdir, ydir; 
//    xdir = (x==0) ? 0 : xdif / x; 
//    ydir = (y==0) ? 0 : ydif / y; 
//


   directionInfo info = getDirectionInfo(origin, destination); 

   if (info.absx && info.absy) {
       return false; 
   }

    //only one of xdir or ydir should be non-zero btw
    Coords intermediateSq(origin.x, origin.y); 
    while (intermediateSq != destination) {
        intermediateSq.x += info.xdir; 
        intermediateSq.y += info.ydir; 
        std::cout <<"\nHello, in roovalid. sq.x = " << intermediateSq.x << " sq.y = " << intermediateSq.y << "\n"; 
        if (board.pieceAt(intermediateSq)) {
            std::cout <<"\nThere is a piece obstructing the rook at sq: " << intermediateSq.toString() <<"\n"; 
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

    directionInfo info(getDirectionInfo(origin, destination)); 

    //if trying to take own piece
    if (board.pieceAt(destination)) {
        if (sameColor(board.pieceAt(destination))) {
                return false; 
        }
    }

    Coords intermediateSq (origin.x, origin.y); 

    //if moving like a bishop
    if (info.absx == info.absy) {
        while (intermediateSq != destination) {
            intermediateSq.x += info.xdir; 
            intermediateSq.y += info.ydir; 

            //there is piece in the way
            if (board.pieceAt(intermediateSq)) {
                return false; 
            }
        }
    }
    //else if moving like rook
    else if ((info.absx && !info.absy) || (info.absy && !info.absx)) {
        while (intermediateSq != destination) {
            intermediateSq.x += info.xdir; 
            intermediateSq.y += info.ydir; 
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

bool Pawn::checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board) {
    directionInfo info (getDirectionInfo(piece, kingLocation)); 

    //if 1-to-1 
    if (info.absy == 1 && info.absx == 1 ) {

        //if white, pawns threaten forward
        if (board.pieceAt(piece)->isWhite()) {
            if (info.xdir > 0) {
                return true; 
            }
        } else {
            //if black, pawns threaten backward
            if (info.xdir < 0) {
                return true; 
            }
        }
    }

    return false; 
}
bool Bishop::checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board) {

    directionInfo info (getDirectionInfo(piece, kingLocation)); 

    //if not on same diagonal
    if (info.absx != info.absy) {
        return false; 
    }

    //if piece between bishop and king

    Coords intermediateSq(piece.x, piece.y); 

    while (intermediateSq != kingLocation) {
        intermediateSq.x += info.xdir; 
        intermediateSq.y += info.ydir; 

        //there is piece in the way
        if (board.pieceAt(intermediateSq)) {
            return false; 
        }
    }


    return true; 
}
bool Rook::checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board) {

    directionInfo info(getDirectionInfo(piece, kingLocation)); 

    //if not differing in ONLY col or row coord
    if (info.ydir && info.xdir) {
        return false; 
    }

    //only one of xdir or ydir should be non-zero, just quicker this way
    Coords intermediateSq(piece.x, piece.y); 
    while (intermediateSq != kingLocation) {
        intermediateSq.x += info.xdir; 
        intermediateSq.y += info.ydir; 
        if (board.pieceAt(intermediateSq)) {
            return false; 
        }
    }

    //if only xdir or ydir, and if no piece in the way, opposing king in check
    return true; 
}

bool Knight::checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board) {

    directionInfo info(getDirectionInfo(piece, kingLocation)); 

    //think this suffices. 
    if ((info.absx == 2 && info.absy == 1) || (info.absx == 1 && info.absy == 2)) {
        return true; 
    }

    return false; 
}


bool Queen::checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board) {
    Piece *temp; 
    Rook* rook; 
    Bishop* bishop; 

    directionInfo info(getDirectionInfo(piece, kingLocation)); 

    temp = board.pieceAt(piece); 
    
    rook = dynamic_cast<Rook*> (temp); 
    if (rook->checkingKing(piece, kingLocation, board)) {
        return true; 
    }

    bishop = dynamic_cast<Bishop*>(temp); 
    if (bishop->checkingKing(piece, kingLocation, board)) {
        return true; 
    }
    return false; 
}

//obviously not possible for a king to check a king
//but check needed to make sure that kings are not being moved next to each other
bool King::checkingKing(const Coords &piece, const Coords &kingLocation, const Board &board) {

    directionInfo info(getDirectionInfo(piece, kingLocation)); 

    //if the enemy king is one square away horizontally or diagonally 
    if (info.absx == 1 && (info.absy == 0 || info.absy == 1)) {
        return true; 
    }

    //if enemy king is one sqaure away vertically
    if (info.absx == 0 && info.absy == 1) {
        return true; 
    } 

    return false; 
}


std::string Pawn::toString() {
    std::string pawnString = ""; 
    
    if (isWhite()) {
        pawnString.append("White's "); 
    } else {
        pawnString.append("Black's "); 
    }
    pawnString.append(" pawn"); 
    return pawnString; 

}
std::string Knight::toString() {
    std::string pawnString = ""; 
    if (isWhite()) {
        pawnString.append("White's "); 
    } else {
        pawnString.append("Black's "); 
    }
    pawnString.append(" knight"); 
    return pawnString; 

}
std::string Bishop::toString() {
    std::string pawnString = ""; 
    if (isWhite()) {
        pawnString.append("White's "); 
    } else {
        pawnString.append("Black's "); 
    }
    pawnString.append(" bishop"); 
    return pawnString; 

}
std::string Rook::toString() {
    std::string pawnString = ""; 
    if (isWhite()) {
        pawnString.append("White's "); 
    } else {
        pawnString.append("Black's "); 
    }
    pawnString.append(" rook"); 
    return pawnString; 

}
std::string Queen::toString() {
    std::string pawnString = ""; 
    if (isWhite()) {
        pawnString.append("White's "); 
    } else {
        pawnString.append("Black's "); 
    }
    pawnString.append(" queen"); 
    return pawnString; 

}
std::string King::toString() {
    std::string pawnString = ""; 
    if (isWhite()) {
        pawnString.append("White's "); 
    } else {
        pawnString.append("Black's "); 
    }
    pawnString.append(" king"); 
    return pawnString; 

}


Knight::Knight(bool white_) {
    setPiece(white_); 
}
Bishop::Bishop(bool white_) {
    setPiece(white_); 
}
Queen::Queen(bool white_) {
    setPiece(white_); 
}
King::King(bool white_) {
    setPiece(white_); 
}
Rook::Rook(bool white_) {
    setPiece(white_); 
}
Pawn::Pawn(bool white_) {
    setPiece(white_); 
}

Piece::~Piece(){}
Pawn::~Pawn(){}
Bishop::~Bishop(){}
Knight::~Knight(){}
Queen::~Queen(){}
King::~King(){}
Rook::~Rook(){}



