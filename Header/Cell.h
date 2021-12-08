#ifndef _CELL_H
#define _CELL_H
#include <string>

class Cell {
public:
    Cell();
    std::string color();
    void Change(std::string color);

private:
    std::string color_;

};

#endif  // _CELL_H