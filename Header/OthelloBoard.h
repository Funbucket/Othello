#ifndef _OTHELLOBOARD_H
#define _OTHELLOBOARD_H
#include <string>
#include <vector>
#include "Cell.h"
#include "Black.h"
#include "White.h"

class OthelloBoard {
public:
    void CreateBoard(Black* black, White* white);
    std::vector<std::vector<int>> ValidMove(Black* black, White* white);
    void SetSize(int size);
    static OthelloBoard* GetInstance();
    int size();
    std::string CurrentPlayer();
    Cell** GetBoard();
    bool GetPushed();
private:
    OthelloBoard();
    static OthelloBoard* instance_;
    int size_;
    Cell** othello_board_;
    std::string current_player_;
    bool is_pushed_;
};

#endif  // _OTHELLOBOARD_H