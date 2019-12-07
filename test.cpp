#include <iostream> 
#include "piece.h"
#include "board.h"

int main() {
    Pawn testPawn(false); 

    if (testPawn.isWhite()) {
        std::cout << "\nThis pawn is white\n";
    } else {
        std::cout <<"\nThis pawn is black\n"; 
    }

    Board newBoard; 

    newBoard.printBoard();


    std::cout <<"\n=========\n"; 

    Coords m1(1, 3); 
    Coords m2(3, 3); 
    newBoard.movePiece(m1, m2); 
    newBoard.printBoard();

    return 0; 
}
