#include "Flag.h"

namespace game{

Flag::Flag(const sf::Texture& texture_, sf::Vector2f spawn_){
	sprite.setTexture(texture_);
	sprite.setPosition(spawn_);
	spawn = spawn_;
	captor = nullptr;
}

void Flag::update(){
	if(captor != nullptr){
		sprite.setPosition(captor->current_vehicle->getPosition());
	}else{
		sprite.setPosition(spawn);
	}
}

void Flag::setCaptor(Player* captor_){
	captor = captor_;
	update();
}

bool Flag::isCaptured(){
	return captor != nullptr;
}

void Flag::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(sprite);
}

sf::Sprite Flag::getCollisionSprite(){
	return sprite;
}

sf::Color Flag::getAlphaColor(){
	return sf::Color::Transparent;
}

}
