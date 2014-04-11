#include "GuiLayout.h"

namespace engine{

GuiLayout::~GuiLayout(){
	for(auto it = children.begin(); it != children.end(); ++it){
		delete (*it);
	}
}

void GuiLayout::setGeometry(sf::IntRect geometry_){
	GuiWidget::setGeometry(geometry_);
	updateChildrenGeometry();
}

void GuiLayout::addChild(GuiWidget* child_){
	children.push_back(child_);
	updateChildrenGeometry();
}

void GuiLayout::update(sf::Time delta){
	for(auto it = children.begin(); it != children.end(); ++it){
		(*it)->update(delta);
	}
}

void GuiLayout::handleEvent(const sf::Event& event){
	for(auto it = children.begin(); it != children.end(); ++it){
		(*it)->handleEvent(event);
	}
}

void GuiLayout::draw(sf::RenderTarget &target,sf::RenderStates states) const{
	for(auto it = children.begin(); it != children.end(); ++it){
		target.draw(*(*it));
	}
}

}
