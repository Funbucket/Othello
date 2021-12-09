#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./Header/Cell.h"
#include "./Header/OthelloBoard.h"

OthelloBoard::OthelloBoard() : current_player_("None") {}

OthelloBoard* OthelloBoard::instance_ = nullptr;

OthelloBoard* OthelloBoard::GetInstance() {
    if ( instance_ == nullptr ) {
        instance_ = new OthelloBoard();
    }
    return instance_;
}

int OthelloBoard::size(){ return size_; }

void OthelloBoard::SetSize(int size) {
    size_ = size;
    othello_board_ = new Cell*[size];

    for (int i=0; i<size; i++) {
        othello_board_[i] = new Cell[size];
    }

    // 초기 값 세팅
    for (int m=0; m < size; m++) {
        for (int n=0; n < size; n++) {
            othello_board_[m][n] = Cell();
        }
    }
    int i = size / 2;
    othello_board_[i - 1][i - 1].Change("W");
    othello_board_[i - 1][i].Change("B");
    othello_board_[i][i - 1].Change("B");
    othello_board_[i][i].Change("W");
}

void OthelloBoard::CreateBoard(Player* black, Player* white) {
    // 현재 플레이어 변경
    if (current_player_ == "None") {
        current_player_ = "B";
    } else if (current_player_ == "B") {
        current_player_ = "W";
    } else {
        current_player_ = "B";
    }

    // status 갱신, 이전 ValidMove 삭제
    if (current_player_ == "B") {
        for (int i=0; i < size_; i++) {
            for (int j=0; j < size_; j++) {
                if (othello_board_[j][i].color() == "B") {
                    black->PushStatus({j, i});
                } else if (othello_board_[j][i].color() == "#") {
                    othello_board_[j][i].Change("empty");
                }
            }
        }
    } else if (current_player_ == "W") {
        for (int i=0; i < size_; i++) {
            for (int j=0; j < size_; j++) {
                if (othello_board_[j][i].color() == "W") {
                    white->PushStatus({j, i});
                } else if (othello_board_[j][i].color() == "#") {
                    othello_board_[j][i].Change("empty");
                }
            }
        }
    }

    is_pushed_ = false;
    for (std::vector<int> position : ValidMove(black, white)) {
        // 돌을 놓을 수 있는 위치들을 현재 플레이어의 벡터에 추가
        is_pushed_ = true;
        if (current_player_ == "B") {
            black->PushValid(position);
        } else if (current_player_ == "W") {
            white->PushValid(position);
        }
        // 돌을 놓을 수 있는 위치들을 보드에 반영
        othello_board_[position[0]][position[1]].Change("#");
    }

    char c = 'A';
    std::cout << "    ";
    for (int i = 0; i < size_; i++) {
        std::cout << "   " << (char)(c + i) << "   ";
    }
    std::cout << "\n";

    for(int i = 0; i < size_; i++) {

        //+ - - -
        std::cout << "   ";
        for(int j=0; j<size_; j++){
            std::cout << "+ - - -";
        }
        std::cout << "+\n";

        //:      or :   B
        if (i < 9) {
            std::cout << " " << i + 1 << " ";
        } else {
            std::cout << " " << i + 1;
        }
        for(int j=0; j<size_; j++){
            if ( othello_board_[j][i].color() == "empty" ) {
                std::cout << ":      ";
            } else {
                std::cout << ":  " << othello_board_[j][i].color() << "   ";
            }
        }
        std::cout << ":\n";

        //:
        std::cout << "   ";
        for (int j = 0; j < size_; j++) {
            std::cout << ":      ";
        }
        std::cout << ":\n";
    }

    std::cout << "   ";
    for (int i = 0; i < size_; i++) {
        std::cout << "+ - - -";
    }
    std::cout << "+\n";

}

std::vector<std::vector<int>> OthelloBoard::ValidMove(Player* black, Player* white) {
    std::vector<int> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
    std::vector<int> dy = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::string cur_color;
    std::vector<std::vector<int>> cur_status;
    std::vector<std::vector<int>> valid_position;

    // 현재 플레이어의 색깔과 status 저장
    if (current_player_ == "B") {
        cur_color = black->color();
        cur_status = black->status();
    } else if (current_player_ == "W") {
        cur_color = white->color();
        cur_status = white->status();
    }

    // 현재 플레이어의 status에서 좌표를 하나씩 꺼내면서 그 위치에서 8방향 탐색
    // 방향마다 벽을 만나지 않으면서(조건 1) 다른 색깔(조건 2), 공백(조건 3) 순으로 만나는지 탐색
    for (std::vector<int> position : cur_status) {
        for (int i=0; i < 8; i++) {
            int x = position[0];
            int y = position[1];
            bool is_diff = false;
            bool is_empty = false;

            // 조건 1 : 벽을 만나지 않는 범위에서 반복
            while ((x + dx[i]) != -1 && (y + dy[i]) != -1
                   && (x + dx[i]) != size_ && (y + dy[i]) != size_) {
                x = x + dx[i];
                y = y + dy[i];

                // 조건 2 : 다른 색깔 만나기
                if (othello_board_[x][y].color() != cur_color
                    && othello_board_[x][y].color() != "empty") {
                    is_diff = true;
                }

                else if (othello_board_[x][y].color() == cur_color) {
                    break;
                }

                else if (othello_board_[x][y].color() == "empty") {
                    // 조건 2를 만족하지 않고 바로 공백을 만나면 조건 불만족, 반복 종료
                    if (is_diff == false) {
                        break;
                    } else {
                        // 조건 3 : 다른 색깔 후 공백 만나면 조건 만족, 반복 종료
                        is_empty = true;
                        break;
                    }
                }
            }


            //std::cout << x << y << is_diff << is_empty << "\n";

            // 현재 방향에서 모든 조건을 만족한다면
            if (is_diff && is_empty) {
                // 현재 위치(돌을 놓을 수 있는 좌표)가 보드의 사이즈 안에 있는 위치라면 벡터에 추가
                if (x > -1 && x < size_ && y > -1 && y < size_) {
                    valid_position.push_back({x, y});
                }
            }


        }
    }
    //중복 제거
    sort(valid_position.begin(), valid_position.end());
    valid_position.erase(unique(valid_position.begin(), valid_position.end()), valid_position.end());

    return valid_position;
}

std::string OthelloBoard::CurrentPlayer() { return current_player_; }

Cell** OthelloBoard::GetBoard() { return othello_board_; }

bool OthelloBoard::GetPushed() { return is_pushed_; }
