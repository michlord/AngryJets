#include "GuiWindow.h"
namespace engine{
GuiWindow::GuiWindow(const sf::RenderWindow& window_):window(window_),child(nullptr){

}
GuiWindow::~GuiWindow(){
	if(child != nullptr){
		delete child;
	}
}

void GuiWindow::setChild(GuiWidget* widget_){
	if(child != nullptr){
		delete child;
	}
	child = widget_;
	child->setGeometry(sf::IntRect(0,0,window.getSize().x,window.getSize().y));
}

void GuiWindow::update(sf::Time delta){
	if(child != nullptr){
		child->update(delta);
	}
}

void GuiWindow::handleEvent(const sf::Event& event){
	if(child != nullptr){
		child->handleEvent(event);
	}
}

void GuiWindow::draw (sf::RenderTarget &target,sf::RenderStates states) const{
	if(child != nullptr){
       target.draw(*child,states);
	}
}
}
