#include "Jetman.h"
#include <cmath>

namespace game{

Jetman::Jetman(const sf::Texture& texture):Vehicle(texture){
	direction = LEFT;
}

void Jetman::flipLeft(){
	if(direction != LEFT){
		direction = LEFT;
		sprite.setScale(1.0f,1.0f);
	}
}

void Jetman::flipRight(){
	if(direction != RIGHT){
		direction = RIGHT;
		sprite.setScale(-1.0f,1.0f);
	}
}

void Jetman::setRotation(float rotation_){
	return;
}

float Jetman::getRotation(float rotation_){
	if(direction == LEFT)
		return -90.0f;
	if(direction == RIGHT)
		return 90.0f;
    return 0.0f;
}

void Jetman::onLeft(){
	flipLeft();
    if(speed.x > -30.0f)
        speed.x -= 0.8f;
	if(landed)
        sprite.move(-1.0f,0.0f);
}

void Jetman::onRight(){

	flipRight();
	if(speed.x < 30.0f)
        speed.x += 0.8f;
	if(landed)
        sprite.move(1.0f,0.0f);
}

void Jetman::onUp(){
    if(fuel != 0.0f){
        fuel -= 0.3f;
        if( fabs(fuel) < 0.01f || fuel < 0.0f)
                    fuel = 0.0f;
        if(speed.y < 30.0f)
            speed.y += 0.6f;
        landed = false;
    }
}

void Jetman::onPrimary(){

}

void Jetman::onSecondary(){

}

void Jetman::update(){
	 //gravity
    speed.y -= .2;

    if(landed){
        restoreSupplies();
        speed.x = 0.0f;
        speed.y = 0.0f;
    }

	sprite.move(speed.x,-speed.y);

}

sf::Vector2f Jetman::getNose(){
        return getCollisionSprite().getTransform().transformPoint(sf::Vector2f(0,getCollisionSprite().getLocalBounds().height/2));
}

sf::Vector2f Jetman::getBulletSpeedVector(float speed){
	sf::Vector2f nose = getNose();
    sf::Vector2f origin = getPosition();
    sf::Vector2f result(nose.x-origin.x,nose.y-origin.y);
    float mag = sqrt(result.x*result.x+result.y*result.y);
    result = sf::Vector2f(speed*result.x/mag+getSpeed().x,-speed*result.y/mag+getSpeed().y);
    return result;

}

}
