#pragma once
#ifndef idE9BE60CE_206F_459B_8B8A9B8C163B0C4B
#define idE9BE60CE_206F_459B_8B8A9B8C163B0C4B
#include <SFML/Graphics.hpp>
namespace game{
class Collidable{
public:
	virtual sf::Sprite 		 getCollisionSprite()=0;
	virtual sf::Color		 getAlphaColor()=0;
	virtual const sf::Image* getCollisionMask() {return nullptr;}
};
}

#endif // header
