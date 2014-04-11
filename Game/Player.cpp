#include "Player.h"

namespace game{
Player::Player(){
    lives = 15;
    score = 0;
    current_vehicle = nullptr;
    current_primary_gun = nullptr;
    vehicle_type = SHIP;

}
Player::Player(int lives_,int score_,Vehicle* current_vehicle_, Gun* current_primary_gun_,VehicleType vehicle_type_){
    lives = lives_;
    score = score_;
    current_vehicle = current_vehicle_;
    current_primary_gun = current_primary_gun_;
    vehicle_type = vehicle_type_;
}
void Player::onDie(){
    lives -= 1;
}
void Player::onScore(int amt){
    score += amt;
}
}
