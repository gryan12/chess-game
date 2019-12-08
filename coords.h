#ifndef COORDS_H
#define COORDS_H

struct Coords {
    int x; 
    int y; 
    Coords(int x_, int y_) : x(x_), y(y_) {
    }
    Coords() : x(0), y(0) {
    }
    bool operator != (const Coords &other) const {
        return (other.x == x && other.y == y); 
    }
}; 




#endif
