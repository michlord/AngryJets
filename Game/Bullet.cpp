#include "Bullet.h"

namespace game{

Bullet::Bullet(sf::Vector2f position_,sf::Vector2f speed_,const sf::Texture* texture_){
	sprite.setTexture(*texture_);
	sprite.setPosition(position_);
	speed = speed_;
}

sf::Sprite Bullet::getCollisionSprite(){
	return sprite;
}
sf::Color Bullet::getAlphaColor(){
	return sf::Color::Transparent;
}

sf::Vector2f Bullet::getPosition(){
	return sprite.getPosition();
}
sf::Vector2f Bullet::getSpeed(){
	return speed;
}
void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite);
}

}
