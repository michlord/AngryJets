#include "GuiHighlightedLabel.h"

namespace engine{

GuiHighlightedLabel::GuiHighlightedLabel(const std::string& text_,const sf::Font* font_,const sf::Color color_, sf::Color highlighted_color_):
	GuiLabel(text_,font_,color_){
	setHighlightedColor(highlighted_color_);
}

void GuiHighlightedLabel::setHighlightedColor(sf::Color color_){
	highlighted_color = color_;
}

void GuiHighlightedLabel::handleEvent(const sf::Event& event){
	GuiLabel::handleEvent(event);

	if(event.type == sf::Event::EventType::MouseMoved){
        sf::Vector2f mousePosition = sf::Vector2f(event.mouseMove.x,event.mouseMove.y);
        if(text.getGlobalBounds().contains(mousePosition)){
            text.setColor(highlighted_color);
        }else{
            text.setColor(color);
        }
	}
}


}
