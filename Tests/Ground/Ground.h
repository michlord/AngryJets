#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>

#include <vector>

class Ground : public sf::Drawable {
public:
	Ground(const sf::Texture& background_,const sf::Texture& foreground_, const sf::Image& mask_);
	void makeCircleHole(sf::Vector2f position, float radius=1.0f);
	void makeSquareHole(sf::Vector2f position, int size=1);
    std::vector<sf::Vector2f> makeHole(sf::Vector2f position, int size=1);
	void makeSpriteHole(sf::Sprite sprite);

//private:
	sf::Sprite  sprite;
	sf::Texture background;
	sf::Texture foreground;
	sf::Image	mask;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
#endif /* GROUND_H */
