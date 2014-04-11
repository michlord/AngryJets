#pragma once
#ifndef id69E633F6_DB8D_4CE1_819830B76B1074EF
#define id69E633F6_DB8D_4CE1_819830B76B1074EF

#include <SFML/Audio.hpp>
#include <list>
#include "NonCopyable.h"

#define sr SoundRecycler::getInstance()

namespace engine{
class SoundRecycler : public NonCopyable{
public:
    ~SoundRecycler();
	void addSound(sf::Sound* sound);
	void recycle();
	static SoundRecycler* getInstance();
private:
	static SoundRecycler* instance;
	SoundRecycler();
	std::list<sf::Sound*> sounds;
};
}
#endif // header
