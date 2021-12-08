#include "./Header/Cell.h"

Cell::Cell() : color_("empty") {}

std::string Cell::color() { return color_; }

void Cell::Change(std::string color) {
    color_ = color;
}