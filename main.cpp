#include "Header/OthelloController.h"

int main() {
    OthelloController* controller = OthelloController::GetInstance();
    controller->playOthello();
    return 0;
}
