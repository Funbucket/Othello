#ifndef _WHITE_H
#define _WHITE_H
#include <string>
#include <vector>
#include "Player.h"

class White : public Player {
public:
    White(std::string name, int size);
    std::vector<std::vector<int>> status() override;
    void PushStatus(std::vector<int> position) override;
    std::vector<std::vector<int>> ValidPosition() override;
    void PushValid(std::vector<int> position) override;
    bool Move(int x, int y) override;
    const std::string color() override;
    const std::string name() override;
    ~White();

private:
    std::vector<std::vector<int>> status_;
    std::vector<std::vector<int>> valid_position_;
    std::string name_;
    const std::string color_;
};
#endif  // _WHITE_H