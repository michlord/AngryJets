#pragma once
#ifndef idDBE44382_5171_43E2_830E7E535BFDAD51
#define idDBE44382_5171_43E2_830E7E535BFDAD51
#include "Vehicle.h"
namespace game{
class Ship : public Vehicle {
public:
	Ship(const sf::Texture& texture);
	void onLeft();
	void onRight();
	void onUp();
	void onPrimary();
	void onSecondary();
	void update();
	sf::Vector2f getNose();
	sf::Vector2f getBulletSpeedVector(float speed_);
private:
};


}

#endif // header
