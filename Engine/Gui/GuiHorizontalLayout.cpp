#include "GuiHorizontalLayout.h"

#include <iostream>
namespace engine{


void GuiHorizontalLayout::updateChildrenGeometry(){

    if(children.size() == 0)
        return;
	int spacing = getGeometry().width / children.size();
	int counter = 0;
	for(auto it = children.begin(); it != children.end(); ++it, ++counter){
        std::cout << "left: " <<  getGeometry().left << " top: " << getGeometry().top+spacing*counter << " width: " << getGeometry().width
                  << "height: " << getGeometry().height << "\n";
		(*it)->setGeometry(sf::IntRect(getGeometry().left+spacing*counter,getGeometry().top,spacing,getGeometry().height));
	}
}

}
