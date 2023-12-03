#include "Vehicle.h"
#include <cmath>

namespace game{
Vehicle::Vehicle(const sf::Texture& texture){
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width/2.0f,sprite.getLocalBounds().height/2.0f);
	reset(1.0f,1.0f,1.0f,1.0f);
}

sf::Sprite Vehicle::getCollisionSprite(){
	return sprite;
}

sf::Color Vehicle::getAlphaColor(){
	return sf::Color::Transparent;
}

const sf::Image* Vehicle::getCollisionMask(){
	return nullptr;
}
bool Vehicle::canRequestAmmo(float amt_){
	return (ammo - amt_) >= 0;
}

bool Vehicle::canRequestMissles(float amt_){
	return (missles - amt_) >= 0;
}

void Vehicle::setPosition(sf::Vector2f pos){
	sprite.setPosition(pos);
}
void Vehicle::setSpeed(sf::Vector2f speed_){
	speed = speed_;
}
void Vehicle::setRotation(float rotation_){
	sprite.setRotation(rotation_);
}
sf::Vector2f Vehicle::getPosition(){
	return sprite.getPosition();
}
sf::Vector2f Vehicle::getSpeed(){
	return speed;
}
float Vehicle::getRotation(float rotation_){
	return sprite.getRotation();
}

void Vehicle::takeDamage(float amt_){
    hull -= amt_;
    if( fabs(hull) < 0.01 || hull < 0.0f)
        hull = 0.0f;
    if(hull == 0.0f){
        dead = true;
        onDie();
    }
}

void Vehicle::onDie(){

}

void Vehicle::setLanded(){
    landed = true;
    sprite.setRotation(0.0f);
}


void Vehicle::reset(float hull_,float ammo_,float missles_,float fuel_, float rotation_, sf::Vector2f position_){
	hull    = hull_;
	ammo    = ammo_;
	fuel    = fuel_;
	missles = missles_;
	sprite.setRotation(rotation_);
	sprite.setPosition(position_);
	speed  = sf::Vector2f(0.0f,0.0f);
	dead   = false;
	landed = false;
}
void Vehicle::restoreSupplies(){
    hull    += 0.1f;
    ammo    += 0.1f;
    missles += 0.1f;
	fuel    += 0.1f;
	if(hull>100.0f)
        hull = 100.0f;
    if(ammo>100.0f)
        ammo = 100.0f;
    if(missles>100.0f)
        missles = 100.0f;
    if(fuel>100.0f)
        fuel = 100.0f;
}


void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite);
}
}
