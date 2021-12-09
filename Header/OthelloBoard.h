#ifndef _OTHELLOBOARD_H
#define _OTHELLOBOARD_H
#include <string>
#include <vector>
#include "Cell.h"
#include "Player.h"

class OthelloBoard {
public:
    // Delete possible copy approaches
    OthelloBoard(OthelloBoard &other) = delete;
    void operator=(const OthelloBoard &) = delete;

    void CreateBoard(Player* black, Player* white);
    std::vector<std::vector<int>> ValidMove(Player* black, Player* white);
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