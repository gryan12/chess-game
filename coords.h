#ifndef COORDS_H
#define COORDS_H
#include <string> 

struct Coords {
    int x; 
    int y; 

    Coords(int x_, int y_) : x(x_), y(y_) {
    }

    Coords() : x(0), y(0) {
    }

    //throw error if incorrect
    Coords(std::string notation) {
        y = notation[0] - 'A'; 
        x = (notation[1] - '0') - 1; 
    }

    bool operator != (const Coords &other) const {
        return !(other.x == x && other.y == y); 
    }

    std::string toString() const {
        std::string ans = ""; 
        ans += (y + 'A'); 
        ans += ('1' + x); 
        return ans; 
    }


}; 




#endif
