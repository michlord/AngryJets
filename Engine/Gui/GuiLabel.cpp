#include "GuiLabel.h"

namespace engine{

void GuiLabel::setGeometry(sf::IntRect geometry_){
	GuiWidget::setGeometry(geometry_);
    setAlignment(alignment__);
}

GuiLabel::GuiLabel(const std::string& text_,const sf::Font* font_,const sf::Color color_){
    setText(text_);
    setFont(font_);
    setAlignment(LEFT);
	setColor(color_);
}

void GuiLabel::setText(const std::string& text_){
    text.setString(text_);
}

void GuiLabel::setFont(const sf::Font* font_){
    text.setFont(*font_);
}

void GuiLabel::setFontSize(int size_){
    text.setCharacterSize(size_);
}

void GuiLabel::setAlignment(alignment alignment_){
    alignment__ = alignment_;
    sf::FloatRect bounds = text.getLocalBounds();
    sf::Vector2f  topleft;
    switch (alignment_){
        case RIGHT:
            topleft = sf::Vector2f(getGeometry().width - bounds.width, getGeometry().top);
            break;
        case CENTER:
            topleft = sf::Vector2f((getGeometry().width - bounds.width)/2,getGeometry().top);
            break;
        default: //LEFT
            topleft = sf::Vector2f(getGeometry().left,getGeometry().top);
    }
    text.setPosition(topleft);
}

void GuiLabel::setColor(sf::Color color_){
	color = color_;
    text.setColor(color);
}

void GuiLabel::update(sf::Time delta){

}
void GuiLabel::handleEvent(const sf::Event& event){
    static bool was_clicked = false;
    if(event.type == sf::Event::EventType::MouseButtonPressed ){
        if(was_clicked == false && event.mouseButton.button == sf::Mouse::Button::Left){
            sf::Vector2f position = sf::Vector2f(event.mouseButton.x,event.mouseButton.y);
            sf::FloatRect bounds = text.getGlobalBounds();
            //std::cout << "x: " <<  position.x << " y: " << position.y << "\n";
            //std::cout << "left: " <<  bounds.left << " top: " << bounds.top << " width: " << bounds.width
            //          << " height: " << bounds.height << "\n";
            if(bounds.contains(position)){
                clicked.emit();
            }
        }
    }
    if(event.type == sf::Event::EventType::MouseButtonPressed ){
        was_clicked = false;
    }
}

void GuiLabel::draw(sf::RenderTarget &target,sf::RenderStates states) const{
    target.draw(text);
}

}
