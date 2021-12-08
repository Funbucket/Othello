#include <string>
#include <vector>
#include "./Header/White.h"
#include "./Header/OthelloBoard.h"

White::White(std::string name, int size) :
        Player(name), color_("W") {}

std::vector<std::vector<int>> White::status() { return status_; }

void White::PushStatus(std::vector<int> position) { status_.push_back(position); }

std::vector<std::vector<int>> White::ValidPosition() { return valid_position_; }

void White::PushValid(std::vector<int> position) { valid_position_.push_back(position); }

bool White::Move(int x, int y) {
    // 돌을 놓을 수 있는지 검사
    bool is_valid = false;
    for (std::vector<int> position : valid_position_) {
        if (position[0] == x && position[1] == y) {
            is_valid = true;
        }
    }
    if (!is_valid) {
        return false;
    }

    OthelloBoard* othello_board = OthelloBoard::GetInstance();

    std::vector<int> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
    std::vector<int> dy = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::vector<std::vector<int>> target_position;

    // 방향마다 벽을 만나지 않으면서(조건 1) 다른 색깔(조건 2), 같은 색깔(조건 3) 순으로 만나는지 탐색
    for (int i=0; i < 8; i++) {
        int nx = x;
        int ny = y;
        bool is_diff = false;
        bool is_same = false;
        int count = 0;

        // 조건 1 : 벽을 만나지 않는 범위에서 반복
        while ((nx + dx[i]) != -1 && (ny + dy[i]) != -1
               && (nx + dx[i]) != othello_board->size()
               && (ny + dy[i]) != othello_board->size()) {
            nx = nx + dx[i];
            ny = ny + dy[i];

            // 조건 2 : 다른 색깔 만나고 벡터에 추가
            if (othello_board->GetBoard()[nx][ny].color() == "B") {
                count++;
                is_diff = true;
            } else if (othello_board->GetBoard()[nx][ny].color() == color_) {
                // 조건 2를 만족하지 않고 바로 같은 색깔을 만나면 조건 불만족, 반복 종료
                if (is_diff == false) {
                    break;
                } else {
                    // 조건 3 : 다른 색깔 후 같은 색깔 만나면 조건 만족, 반복 종료
                    is_same = true;
                    break;
                }
            }
        }
        if (is_diff && is_same) {
            for (int j=0; j < (count); j++) {
                nx = nx - dx[i];
                ny = ny - dy[i];
                target_position.push_back({nx, ny});
            }
        }
    }


    // 뒤집히는 돌 보드에 반영
    othello_board->GetBoard()[x][y].Change(color_);
    for (std::vector<int> position : target_position) {
        othello_board->GetBoard()[position[0]][position[1]].Change(color_);
    }
    status_.clear();
    valid_position_.clear();
    return true;
}

const std::string White::color() { return color_; }

White::~White() {}