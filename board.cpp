#include "board.h"
#include <iomanip>
#include <cstddef> 
#include <iostream> 
#include <string> 

Board setNewpieces() {

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

    if (pieceAt(origin) == NULL) {
        return false; 
    }

    std::cout << " \bPieceat Origin is " << pieceAt(origin)->getSymbol() << "\n"; 

    if (pieceAt(origin)->isValidMove(origin, destination, *this)) {

        if (pieceAt(destination)) {
            takenPieces.push_back(pieceAt(destination)); 
        }
        boardState[destination.x][destination.y] = boardState[origin.x][origin.y]; 
        boardState[origin.x][origin.y] = NULL; 
        moveNumber++; 
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
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            //if piece present at coords which is of opposite color
            if ((pieceAt(i,j) != NULL) && (pieceAt(i, j)->isWhite() != whiteKing)) {
                Coords currentSq(i, j); 
                Coords kingSq(getKingSq(whiteKing)); 
                if (pieceAt(i, j)->checkingKing(currentSq, kingSq, *this)) {
                    return true; 
                }
            }
        }
    }
    return false; 
}

bool Board::inCheck(const Coords &kingLocation, bool whiteKing) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            //if piece present at coords which is of opposite color
            if ((pieceAt(i,j) != NULL) && (pieceAt(i, j)->isWhite() != whiteKing)) {
                Coords currentSq(i, j); 
                if (pieceAt(i, j)->checkingKing(currentSq, kingLocation, *this)) {
                    return true; 
                }
            }
        }
    }
    return false; 
}

//override inCheck to also take a Coords. 
//then, can just do the above function but for every available square to the king
//messy but would be: if valid move (for every single-squared difference) then
//check if (would be) check. if true for every square then return cmate
bool Board::isCheckmate(bool whiteKing) {
    King tempKing(whiteKing); 
    Coords kingSq(getKingSq(whiteKing)); 
    
    if (!inCheck(whiteKing)) {
        return false; 
    }

    //going methodically through every space near the king. 
    Coords tempSq(kingSq); 

    //placeholder, v ugly

    //vertical mvt
    tempSq.x += 1; 
    if(tempKing.isValidMove(kingSq, tempSq, *this)) {
        return false; 
    }
    tempSq.x -= 2; 
    if(tempKing.isValidMove(kingSq, tempSq, *this)) {
        return false; 
    }
    //horizontal mvt; 
    tempSq.x += 1; 
    tempSq.y += 1;
    if(tempKing.isValidMove(kingSq, tempSq, *this)) {
        return false; 
    }
    tempSq.y -= 2;
    if(tempKing.isValidMove(kingSq, tempSq, *this)) {
        return false; 
    }

    //lower diagonal mvt
    tempSq.x -=1; 
    if(tempKing.isValidMove(kingSq, tempSq, *this)) {
        return false; 
    }

    tempSq.x +=2; 
    if(tempKing.isValidMove(kingSq, tempSq, *this)) {
        return false; 
    }

    //upper diagonal mvt
    tempSq.y +=2; 
    if(tempKing.isValidMove(kingSq, tempSq, *this)) {
        return false; 
    }

    tempSq.y -=2; 
    if(tempKing.isValidMove(kingSq, tempSq, *this)) {
        return false; 
    }

    return true; 
}


bool Board::submitMove(std::string start, std::string end) {
    Coords origin(start); 
    Coords destination(end); 

    std::cout <<"\nHello! origin: " << origin.x << ":" << origin.y
                << " destination: " << destination.x << ":" << destination.y << "\n"; 
    //need details about the type of move. if its check, if a piece
    //has been taken, etc
    if (pieceAt(origin)) {
        std::cout <<"\nIs piece at origin.\n";

        if ((pieceAt(origin)->isWhite() && moveNumber%2 != 0) || (!pieceAt(origin)->isWhite() && moveNumber%2 ==0))  {
            std::string color; 
            pieceAt(origin)->isWhite() ? color = "white's" : color = "black's"; 
            std::cout << "It is not " << color << " turn to move."; 
            return false; 
        }


        if (movePiece(origin, destination)) {
            std::string output; 
            std::cout <<"in submit\n"; 
            output = pieceAt(destination)->toString(); 
            std::cout << output << " has moved from " 
                      << start << " to " << end; 
            return true; 
        }
    }
    return false; 
}

int Board::getMoveNumber() {
    return moveNumber; 
}


void Board::resetBoard() {

}

