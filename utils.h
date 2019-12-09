
#ifndef UTILS_H
#define UTILS_H

#include <map> 
#include <string> 
#include <iostream> 


enum moveType {
    NOT_WHITES_TURN, 
    NOT_BLACKS_TURN, 
    CANNOT_MOVE,
    NO_PIECE, 
    CHECK, 
    CHECKMATE, 
    NEW_GAME
}; 

std::map<moveType, std::string> outcomes {
    {NOT_WHITES_TURN, "It is not White's turn to move"}, 
    {NOT_BLACKS_TURN, "It is not Black's turn to move"}, 
    {NO_PIECE, "There is no piece at position: "},
    {CANNOT_MOVE, " cannot move to "},
    {CHECK, " is in check"}, 
    {CHECKMATE, " is in checkmate"},
    {NEW_GAME, "A new game has started!"}
} ; 

void alert(moveType movetype, const std::string &trailingMessage = "", const std::string &leadingMessage = "") {
    std::string alert = ""; 
    alert.append(leadingMessage); 
    alert.append(outcomes.at(movetype)); 
    alert.append(trailingMessage); 
    std::cout << alert << "\n"; 
}

#endif

