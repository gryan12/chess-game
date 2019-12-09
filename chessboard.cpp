#include "chessboard.h"
#include "utils.h" 
#include <iomanip>
#include <cstddef> 
#include <iostream> 
#include <string> 

int ChessBoard::getMoveNumber() {
    return moveNumber; 
}

bool ChessBoard::whitesTurn() {
    return (!moveNumber%2); 
}

/* pointer to piece (or null pointer) at given board
 * coords */
Piece* ChessBoard::pieceAt(const Coords &location) const {
    return boardState[location.x][location.y]; 
}

Piece* ChessBoard::pieceAt(int x, int y) const {
    return boardState[x][y]; 
}

Coords ChessBoard::getKingSq(bool white) {
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


//constructor
ChessBoard::ChessBoard()  {
    //init
    boardState = new Piece**[BOARD_LENGTH]; 
    setNewPieces(); 

}

//destructor
ChessBoard::~ChessBoard() {
    //delete piece
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (boardState[i][j]) {
                delete boardState[i][j]; 
            }
        }
        delete[] boardState[i]; 
    }
    delete[] boardState; 

    //delete peices off the board
    for (auto piece: takenPieces) {
        delete piece; 
    }
}


bool ChessBoard::submitMove(std::string start, std::string end) {
    Coords origin(start); 
    Coords destination(end); 

    //need details about the type of move. if its check, if a piece
    //has been taken, etc
    if (pieceAt(origin)) {
        bool taking = false; 
        if (pieceAt(destination)) {
            taking = true;
        }

        if ((pieceAt(origin)->isWhite() && moveNumber%2 != 0) || (pieceAt(origin)->isBlack() && moveNumber%2 ==0))  {

            if (pieceAt(origin)->isWhite()) {
                alert(NOT_WHITES_TURN); 
            } else {
                alert(NOT_BLACKS_TURN); 
            }
            return false; 
        }
        if (movePiece(origin, destination)) {

        announceMove(origin, destination, taking); 

        std::string color;
        bool white = !pieceAt(destination)->isWhite(); 
        pieceAt(destination)->isWhite() ? color = "Black" : color = "White"; 
        if (inCheck(white)) {
            if (isCheckmate(white)) {
                alert(CHECKMATE, "", color); 
            } else {
                alert(CHECK, "", color); 
            }
        }
            return true; 
        } else {
            alert(CANNOT_MOVE, destination.toString(), pieceAt(origin)->toString()); 
            //std::cout << pieceAt(origin)->toString() << " can not move to : " << destination.toString() << "!"; 
            return false; 
        }

    } else {
        alert(NO_PIECE, origin.toString()); 
    }

    return false; 
}

bool ChessBoard::movePiece(const Coords &origin, const Coords &destination) {

    if (pieceAt(origin) == NULL) {
        return false; 
    }



    if (pieceAt(origin)->isValidMove(origin, destination, *this)) {

        if (pieceAt(destination)) {
            takenPieces.push_back(pieceAt(destination)); 
        }
        //here do the check check
        
        std::string color; 
        if (wouldBeCheck(origin, destination, pieceAt(origin)->isWhite())) {
            pieceAt(origin)->isWhite() ? color = "White" : color = "Black"; 
            alert(CHECK, " still", color); 
            return false; 
        }

        boardState[destination.x][destination.y] = boardState[origin.x][origin.y]; 
        boardState[origin.x][origin.y] = NULL; 
        moveNumber++; 

        return true; 
    }
    return false; 
}






void ChessBoard::announceMove(const Coords &origin, const Coords &destination, bool tookAPiece = false) {

    std::string output; 
    output = pieceAt(destination)->toString(); 
    std::cout << output << " has moved from " 
              << origin.toString() << " to " << destination.toString(); 

    if (tookAPiece) {
        std::cout << " taking " << takenPieces.back()->toString(); 
    }

    std::cout << '\n'; 
}

bool ChessBoard::inCheck(bool whiteKing) {
    Coords kingSq(getKingSq(whiteKing)); 
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            //if piece present at coords which is of opposite color
            if ((pieceAt(i,j) != NULL) && (pieceAt(i, j)->isWhite() != whiteKing)) {
                Coords currentSq(i, j); 
                if (pieceAt(i, j)->checkingKing(currentSq, kingSq, *this)) {
                    return true; 
                }
            }
        }
    }
    return false; 
}

bool ChessBoard::inCheck(const Coords &kingLocation, bool whiteKing) {
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


//for same color as those moving. move must
bool ChessBoard::wouldBeCheck(const Coords &origin, const Coords &destination, bool whiteKing) {


    if ((destination.x > 7 || destination.x < 0) || (destination.y > 7 || destination.y < 0)) {
        return false; 
    }


    bool wouldBeCheck = false; 

    takenPieces.push_back(pieceAt(destination)); 
    boardState[destination.x][destination.y] = pieceAt(origin); 
    boardState[origin.x][origin.y] = NULL;

    Coords kingLocation = getKingSq(whiteKing); 

    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            //if piece present at coords which is of opposite color
            if ((pieceAt(i,j) != NULL) && (pieceAt(i, j)->isWhite() != whiteKing)) {
                Coords currentSq(i, j); 
                if (pieceAt(i, j)->checkingKing(currentSq, kingLocation, *this)) {
                    wouldBeCheck = true; 
                }
            }
        }
    }

    boardState[origin.x][origin.y] = boardState[destination.x][destination.y]; 
    boardState[destination.x][destination.y] = takenPieces.back(); 
    takenPieces.pop_back(); 

    return wouldBeCheck; 
}

bool ChessBoard::isCheckmate(bool whiteKing) {

    Coords kingSq(getKingSq(whiteKing)); 
    
    if (!inCheck(whiteKing)) {
        return false; 
    }

    if (hasValidMove(whiteKing)) {
        return false; 
    }

    return true; 
}

bool ChessBoard::hasValidMove(bool white) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (pieceAt(i,j) && (pieceAt(i, j)->isWhite() == white)) {
                Coords origin(i,j); 

                for (int m = 0; m < BOARD_LENGTH; m++) {
                    for (int n = 0; n < BOARD_LENGTH; n++) {
                        Coords destination(m, n); 
                        if (pieceAt(i,j)->isValidMove(origin, destination, *this)) {
                            if (!wouldBeCheck(origin, destination, white)) {
                                return true; 
                            }

                        }

                    }
                }

            }
        }
    }
    return false; 
}


bool ChessBoard::gameOver() {
    return (isCheckMate || isStaleMate); 
}

//deallocate all pieces, reallocate and put at starting pos
//set move number back to 
void ChessBoard::resetBoard() {
    freeBoard(); 
    setNewPieces(); 
    isCheckMate = false;
    isStaleMate = false; 
    moveNumber = 0; 
}
void ChessBoard::freeBoard() {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (boardState[i][j]) {
                delete boardState[i][j];
            }
        }
        delete[] boardState[i]; 
    }

    //delete peices off the board
    for (auto piece: takenPieces) {
        delete piece; 
    }
}

void ChessBoard::setNewPieces() {

    alert(NEW_GAME); 

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
