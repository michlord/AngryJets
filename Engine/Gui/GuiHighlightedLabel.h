#pragma once
#ifndef id1864FA00_2AA8_4643_96B5E11E19D7563B
#define id1864FA00_2AA8_4643_96B5E11E19D7563B

#include "GuiLabel.h"

namespace engine{
class GuiHighlightedLabel : public GuiLabel{
public:
	GuiHighlightedLabel(const std::string& text_,const sf::Font* font_,const sf::Color color_ = sf::Color::White, sf::Color highlighted_color_ = sf::Color::Yellow);
	void setHighlightedColor(sf::Color color_);
	void handleEvent(const sf::Event& event);
private:
	sf::Color highlighted_color;
};
}

#endif // header
