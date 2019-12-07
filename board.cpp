#include "board.h"
#include <iomanip>
#include <cstddef> 
#include <iostream> 
#include <string> 

Board::Board()  {

    //init
    boardState = new Piece**[BOARD_LENGTH]; 

    //init rows of poitners 
    for (int i = 0; i < BOARD_LENGTH; i++) {
        boardState[i] = new Piece*[BOARD_LENGTH]; 
    }

    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {

            boardState[i][j] = NULL; 

            if (i == 1) {
                boardState[i][j] = new Pawn(true); 
            }  

            if (i == 6) {
                boardState[i][j] = new Pawn(false); 
            }

            if (i == 0) {
                if (j == 0 || j == 7) {
                    boardState[i][j] = new Rook(true); 
                }

                if (j == 1 || j == 6) {
                    boardState[i][j] = new Knight(true); 
                }

                if (j == 2 || j == 5) {
                    boardState[i][j] = new Bishop(true); 
                }
                if (j == 3) {
                    boardState[i][j] = new Queen(true); 
                }
                if (j == 4) {
                    boardState[i][j] = new King(true); 
                }
            }

            if (i == 7) {
                if (j == 0 || j == 7) {
                    boardState[i][j] = new Rook(false); 
                }

                if (j == 1 || j == 6) {
                    boardState[i][j] = new Knight(false); 
                }

                if (j == 2 || j == 5) {
                    boardState[i][j] = new Bishop(false); 
                }
                if (j == 3) {
                    boardState[i][j] = new Queen(false); 
                }
                if (j == 4) {
                    boardState[i][j] = new King(false); 
                }
                
            }
        }
    }

}

Board::~Board() {
    //delete pieces on the board
    for (int i = 0; i < BOARD_LENGTH; i++) {
        delete[] boardState[i]; 
    }
    delete[] boardState; 

    //delete peices off the board
    for (auto piece: takenPieces) {
        delete piece; 
    }
}

void Board::printBoard() {

    std::cout <<'\n'; 
    for (int i = 0; i < BOARD_LENGTH; i++) {
       
            for (int j = 0; j < BOARD_LENGTH; j++) {
                if (boardState[i][j] != NULL) {
                    std::cout << boardState[i][j]->getSymbol(); 
                } else {
                    std::cout << " "; 
                }
                std::cout << "\t"; 
            }
        std::cout << '\n'; 
    }
}

/* pointer to piece (or null pointer) at given board
 * coords */
Piece* Board::pieceAt(const Coords &location) const {
    return boardState[location.x][location.y]; 
}
Piece* Board::pieceAt(int x, int y) const {
    return boardState[x][y]; 
}



bool Board::movePiece(const Coords &origin, const Coords &destination) {
    std::cout << "\nin move\n"; 

    if (pieceAt(origin) == NULL) {
        return false; 
    }

    std::cout << "\nin move\n"; 
    if (pieceAt(origin)->isValidMove(origin, destination, *this)) {

        if (pieceAt(destination)) {
            takenPieces.push_back(pieceAt(destination)); 
        }
        boardState[destination.x][destination.y] = boardState[origin.x][origin.y]; 
        boardState[origin.x][origin.y] = NULL; 
        return true; 
    }
    return false; 
}

Coords Board::getKingSq(bool white) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            Coords kingSq(i, j); 
            Piece *temp = pieceAt(kingSq); 
            if (temp && temp->getSymbol() == 'K') {
                if (temp->isWhite() == white) {
                    return kingSq; 
                }
            }
        }
    }
    //should never be reached. make exception
    Coords failed(9,9) ;
    return failed; 
}

bool Board::inCheck(bool whiteKing) {
    Coords kingSq; 
    kingSq = getKingSq(whiteKing); 

    return true; 
}

