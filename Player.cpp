#include <string>
#include "./Header/Player.h"

Player::Player(std::string name) : name_(name){}

const std::string Player::name() {return name_; }

Player::~Player() {}