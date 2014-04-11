#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>
#include "Collidable.h"

#include <vector>
namespace game{
class Ground : public sf::Drawable, public Collidable {
public:
	Ground(const sf::Texture& background_,const sf::Texture& foreground_, const sf::Image& mask_);
	void 						makeCircleHole(sf::Vector2f position, float radius=1.0f);
	void 						makeSquareHole(sf::Vector2f position, int size=1);
    std::vector<sf::Vector2f> 	makeSquareHoleGetPixels(sf::Vector2f position, int size=1);
	void 						makeSpriteHole(sf::Sprite sprite);
	sf::Sprite 					getCollisionSprite();
	sf::Color		 			getAlphaColor();
	const sf::Image* 			getCollisionMask();
	void                        setScale(float scale=1.0f);
	sf::Vector2f                getSize();

private:
	sf::Sprite  sprite;
	sf::Texture background;
	sf::Texture foreground;
	sf::Image	mask;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
}
#endif /* GROUND_H */
