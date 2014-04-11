#pragma once
#ifndef id3795623D_19B6_440B_95CF1E7FB285EDA0
#define id3795623D_19B6_440B_95CF1E7FB285EDA0

#include <SFML/Graphics.hpp>
#include "Collidable.h"

namespace game{

class Bullet : public sf::Drawable, public Collidable{
public:
	Bullet(sf::Vector2f position_,sf::Vector2f speed_,const sf::Texture* texture_);

	virtual sf::Sprite 		 	getCollisionSprite();
	virtual sf::Color		 	getAlphaColor();

	virtual sf::Vector2f  	    getPosition();
	virtual sf::Vector2f  	    getSpeed();

	virtual void 				update()      = 0;
	virtual void 				onHit()       = 0;
	virtual void 				onLaunch()    = 0;
	virtual float 				getDamage()   = 0;
	virtual float				getAmmoCost() = 0;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite   sprite;
	sf::Vector2f speed;

};
}
#endif // header
