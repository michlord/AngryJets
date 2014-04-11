#pragma once
#ifndef id330A1277_E4C0_47B2_AF1453403B01FCB7
#define id330A1277_E4C0_47B2_AF1453403B01FCB7
#include "Bullet.h"
#include <SFML/Audio.hpp>
namespace game {

class BulletMinigun : public Bullet {
public:
	BulletMinigun(sf::Vector2f position_,sf::Vector2f speed_,const sf::Texture* texture_);
	void 	update();
	void 	onHit();
	void 	onLaunch();
    float 	getDamage();
    float	getAmmoCost();
private:
};

}

#endif // header
