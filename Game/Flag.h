#pragma once
#ifndef idA36CC31A_2C5E_4C54_8D98245B30AA863D
#define idA36CC31A_2C5E_4C54_8D98245B30AA863D

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Vehicle.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SoundRecycler.h"
#include "Collidable.h"

namespace game{
class Flag : public sf::Drawable, public Collidable{
public:
	Flag(const sf::Texture& texture_, sf::Vector2f spawn_);
	void update();
	void setCaptor(Player* captor_=nullptr);
	bool isCaptured();
	
	sf::Sprite getCollisionSprite();
	sf::Color getAlphaColor();
private:
	Player *  captor;
	sf::Vector2f spawn;
	sf::Sprite sprite;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};

}


#endif // header
