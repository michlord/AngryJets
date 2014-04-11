#pragma once
#ifndef idD6631ECB_B26C_4C37_AD7C5F646B6B2267
#define idD6631ECB_B26C_4C37_AD7C5F646B6B2267

#include "Vehicle.h"

namespace game{

class Jetman : public Vehicle {
public:
	enum Direction {LEFT,RIGHT};

	Jetman(const sf::Texture& texture);
	
	void    flipLeft();
	void    flipRight();
	void 	setRotation(float rotation_);
	float 	getRotation(float rotation_);
	void	onLeft();
	void	onRight();
	void	onUp();
	void	onPrimary();
	void	onSecondary();
	void	update();
	
	sf::Vector2f getNose();
	sf::Vector2f getBulletSpeedVector(float speed_);

private:
	Direction direction;

};

}

#endif // header
