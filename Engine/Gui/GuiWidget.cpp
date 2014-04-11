#include "GuiWidget.h"
namespace engine{
void GuiWidget::setGeometry(sf::IntRect geometry_){
	geometry = geometry_;
}

sf::IntRect GuiWidget::getGeometry(){
	return geometry;
}

}

