#pragma once
#ifndef id6C5D064B_6AE6_43BF_8C12A9CC089E27B3
#define id6C5D064B_6AE6_43BF_8C12A9CC089E27B3

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

namespace engine{

class GuiWidget : public sf::Drawable {
public:
	virtual void            setGeometry(sf::IntRect geometry_);
	virtual sf::IntRect     getGeometry();
	virtual void            update(sf::Time delta) = 0;
	virtual void            handleEvent(const sf::Event& event) = 0;

protected:
	sf::IntRect geometry;

private:
	virtual void            draw(sf::RenderTarget &target,sf::RenderStates states) const = 0;
};

}
#endif // header
