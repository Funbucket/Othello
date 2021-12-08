#include "Header/OthelloController.h"

int main() {
    OthelloController* controller = OthelloController::GetInstance();
    controller->PlayOthello();
    return 0;
}
