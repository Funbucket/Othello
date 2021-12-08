#include <iostream>
#include <string>
#include <vector>
#include "Header/OthelloController.h"
#include "Header/OthelloBoard.h"
#include "Header/Cell.h"
#include "Header/Player.h"
#include "Header/Black.h"
#include "Header/White.h"

int main() {
    OthelloController* controller = OthelloController::GetInstance();
    controller->playOthello();
    return 0;
}
