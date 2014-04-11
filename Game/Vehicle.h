#pragma once
#ifndef idF7D64318_1EDD_48C7_91DF7D9903786C48
#define idF7D64318_1EDD_48C7_91DF7D9903786C48

#include <SFML/Graphics.hpp>
#include "Collidable.h"
#include <sigslot.h>
namespace game{
class Vehicle : public sf::Drawable, public Collidable{

public:
	Vehicle(const sf::Texture& texture);

	float 						hull;
	float 						ammo;
	float 						missles;
	float 						fuel;

	bool 					    dead;
	bool 						landed;

	sf::Sprite 					getCollisionSprite();
	sf::Color		 			getAlphaColor();
	const sf::Image* 			getCollisionMask();

	virtual bool				canRequestAmmo(float amt_);
	virtual bool				canRequestMissles(float amt_);

	virtual void 				setPosition(sf::Vector2f pos);
	virtual void 				setSpeed(sf::Vector2f speed_);
	virtual void 				setRotation(float rotation_);
	virtual sf::Vector2f 		getPosition();
	virtual sf::Vector2f  		getSpeed();
	virtual float 				getRotation(float rotation_);

	virtual sf::Vector2f		getNose() = 0;
	virtual sf::Vector2f		getBulletSpeedVector(float speed_) =0;

	virtual void 				onLeft()      = 0;
	virtual void 				onRight()     = 0;
	virtual void 				onUp()        = 0;
	virtual void 				onPrimary()   = 0;
	virtual void 				onSecondary() = 0;
	virtual void				update()      = 0;

	virtual void                takeDamage(float amt_);
	virtual void                onDie();

	virtual void                setLanded();

	virtual void                restoreSupplies();

	virtual void				reset(float hull_,float ammo_,float missles_,float fuel_,
										float rotation_ = 0.0f, sf::Vector2f position_ = sf::Vector2f(0,0));

protected:

sf::Vector2f speed;
sf::Sprite sprite;

virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
}

#endif // header
