#include "BulletMinigun.h"
#include "../Engine/ResourceManager.h"
#include <SFML/Audio.hpp>
#include "../Engine/SoundRecycler.h"



namespace game {
BulletMinigun::BulletMinigun(sf::Vector2f position_,sf::Vector2f speed_,const sf::Texture* texture_):
	Bullet(position_,speed_,texture_)
{
}

void BulletMinigun::update(){
	sprite.move(speed.x,-speed.y);
}

void BulletMinigun::onHit(){
    sf::Sound* sound = new sf::Sound();
    sound->setBuffer(engine::rm->getSoundBuffer("gameplay/sound/explosion"));
    sound->play();
    engine::sr->addSound(sound);
}

void BulletMinigun::onLaunch(){
    sf::Sound* sound = new sf::Sound();
    sound->setBuffer(engine::rm->getSoundBuffer("gameplay/sound/shotgun"));
    sound->play();
    engine::sr->addSound(sound);

}

float BulletMinigun::getDamage(){
	return 20.0f;
}

float BulletMinigun::getAmmoCost(){
	return 1.0f;
}

}
