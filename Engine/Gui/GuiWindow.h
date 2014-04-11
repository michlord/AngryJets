#pragma once
#ifndef idC0171E24_B339_4702_AAC5E459B9FFA0F6
#define idC0171E24_B339_4702_AAC5E459B9FFA0F6

#include "GuiWidget.h"

namespace engine{

class GuiWindow : public GuiWidget {
public:
	GuiWindow(const sf::RenderWindow& window_);
	virtual ~GuiWindow();

	void 	setChild(GuiWidget* widget_);
	void 	update(sf::Time delta);
	void 	handleEvent(const sf::Event& event);
private:
	const sf::RenderWindow& window;
	GuiWidget* child;

	void draw (sf::RenderTarget &target,sf::RenderStates states) const;
};

}

#endif // header
