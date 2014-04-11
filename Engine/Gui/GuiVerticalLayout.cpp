#include "GuiVerticalLayout.h"

#include <iostream>
namespace engine{


void GuiVerticalLayout::updateChildrenGeometry(){

    if(children.size() == 0)
        return;
	int spacing = getGeometry().height / children.size();
	int counter = 0;
	for(auto it = children.begin(); it != children.end(); ++it, ++counter){
        //std::cout << "left: " <<  getGeometry().left << " top: " << getGeometry().top+spacing*counter << " width: " << getGeometry().width
        //          << "height: " << getGeometry().height << "\n";
		(*it)->setGeometry(sf::IntRect(getGeometry().left,getGeometry().top+spacing*counter,getGeometry().width,getGeometry().height));
	}
}

}
