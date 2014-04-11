#pragma once
#ifndef idE8E1DD33_F6B6_4778_9BBE6DEED69CB5B6
#define idE8E1DD33_F6B6_4778_9BBE6DEED69CB5B6
#include "GuiWidget.h"
#include <sigslot.h>
namespace engine{
class GuiLabel : public GuiWidget {
public:
    void setGeometry(sf::IntRect geometry_);
    enum alignment {LEFT,CENTER,RIGHT};
    GuiLabel(const std::string& text_,const sf::Font* font_,const sf::Color color_ = sf::Color::White);
    void setText(const std::string& text_);
    void setFont(const sf::Font* font_);
    void setFontSize(int size_);
    void setAlignment(alignment alignment_ = LEFT);
    void setColor(sf::Color color_);
    void update(sf::Time delta);
	void handleEvent(const sf::Event& event);
    sigslot::signal0<> clicked;
protected:
	sf::Color color;
    sf::Text text;
    alignment alignment__;
    virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const;

};
}
#endif // header
