#ifndef _PLAYER_H
#define _PLAYER_H
#include <vector>
#include <string>

class Player {
public:
    Player(std::string name);
    virtual std::vector<std::vector<int>> status() = 0;
    virtual void PushStatus(std::vector<int> position) = 0;
    virtual std::vector<std::vector<int>> ValidPosition() = 0;
    virtual void PushValid(std::vector<int> position) = 0;
    virtual bool Move(int x, int y) = 0;
    virtual const std::string color() = 0;
    const std::string name();
    virtual ~Player() = 0;
private:
    std::string name_;

};

#endif  // _PLAYER_H