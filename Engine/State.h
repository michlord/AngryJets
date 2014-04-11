#pragma once
#ifndef idDEB1D5DD_1096_4D57_B86C4AB38A112BE4
#define idDEB1D5DD_1096_4D57_B86C4AB38A112BE4

#include <SFML/Graphics.hpp>

namespace engine{
class State{
public:
	State(sf::RenderWindow& window);
	virtual ~State();
	virtual void handleEvents(const sf::Event& event) = 0;
	virtual void update()       = 0;
	virtual void draw()         = 0;
	virtual void onEnter()      = 0;
	virtual void onExit()       = 0;
protected:
	sf::RenderWindow& window;
};
}

#endif // header
