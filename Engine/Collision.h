#pragma once
#ifndef idE2FC9137_3697_419C_B21082E09B82FE64
#define idE2FC9137_3697_419C_B21082E09B82FE64

#include "NonCopyable.h"
#include <SFML\Graphics.hpp>
#include <map>

#define bm BitmaskManager::getInstance()

namespace engine{

class BitmaskManager : public NonCopyable {
public:
	~BitmaskManager();
	static BitmaskManager* 				 getInstance();
	void 								 addMask(const sf::Texture& texture,const sf::Image& mask);
	const sf::Image& 					 getMask(const sf::Texture& texture);
	bool                                 isMaskAvailable(const sf::Texture& texture);
private:
	BitmaskManager();

	static BitmaskManager* 			     instance;
	std::map< const sf::Texture*,sf::Image* >  masks;
};

namespace collision{


bool spriteSpriteTest(const sf::Sprite& left_sprite, const sf::Image* left_mask, const sf::Sprite& right_sprite, const sf::Image* right_mask, sf::Color left_alpha_color = sf::Color::Transparent, sf::Color right_alpha_color = sf::Color::Transparent);

bool spriteSpriteTest(const sf::Sprite& left_sprite, const sf::Sprite& right_sprite, sf::Color left_alpha_color = sf::Color::Transparent, sf::Color right_alpha_color = sf::Color::Transparent);

bool pointSpriteTest(const sf::Sprite& sprite, const sf::Image& mask, sf::Vector2f point, sf::Color alpha_color = sf::Color::Transparent);

bool pointSpriteTest(const sf::Sprite& sprite, sf::Vector2f point, sf::Color alpha_color = sf::Color::Transparent);

}

}

#endif
