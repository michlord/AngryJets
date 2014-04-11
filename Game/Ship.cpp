#include "Ship.h"
#include <cmath>
namespace game{
Ship::Ship(const sf::Texture& texture):Vehicle(texture){
}
void Ship::onLeft(){
    sprite.rotate(-8.0f);
    if(sprite.getRotation() < 0.0f){
        sprite.setRotation(360.0f + sprite.getRotation());
    }
}
void Ship::onRight(){
    sprite.rotate(8.0f);
    if(sprite.getRotation() > 360.0f){
        sprite.rotate(-360.0f);
    }
}
void Ship::onUp(){
    static const float degToRad = 0.0174532925f;
    if(fuel != 0.0f){
        fuel -= 0.3f;
        if( fabs(fuel) < 0.01f || fuel < 0.0f)
                    fuel = 0.0f;
        landed = false;
        float acceleration = 1.0f;
        speed.x -= cos((sprite.getRotation()+90.0f)*degToRad)*acceleration;
        speed.y += sin((sprite.getRotation()+90.0f)*degToRad)*acceleration;
    }
}
void Ship::onPrimary(){
}
void Ship::onSecondary(){
}
void Ship::update(){


    //gravity
    speed.y -= .2;

    if(landed){
        restoreSupplies();
        speed.x = 0.0f;
        speed.y = 0.0f;
    }

    static const float max_speed = 40;
    float mag = sqrt(speed.x*speed.x+speed.y*speed.y);

    if(mag>max_speed){
        speed.x = 0.5f*max_speed*speed.x/mag;
        speed.y = 0.5f*max_speed*speed.y/mag;
    }

    sprite.move(speed.x,-speed.y);
}

sf::Vector2f Ship::getNose(){
	sf::Vector2f nose(getCollisionSprite().getLocalBounds().width/2,0);
    nose = getCollisionSprite().getTransform().transformPoint(nose);
    return nose;
}

sf::Vector2f Ship::getBulletSpeedVector(float speed){
	sf::Vector2f nose = getNose();
    sf::Vector2f origin = getPosition();
    sf::Vector2f result(nose.x-origin.x,nose.y-origin.y);
    float mag = sqrt(result.x*result.x+result.y*result.y);
    result = sf::Vector2f(speed*result.x/mag+getSpeed().x,-speed*result.y/mag+getSpeed().y);
    return result;

}

}
