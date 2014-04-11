#pragma once
#ifndef idD7D28894_9476_46AE_BB8F38284DDE389E
#define idD7D28894_9476_46AE_BB8F38284DDE389E

#include "GuiWidget.h"
#include <list>

namespace engine{
class GuiLayout : public GuiWidget {
public:
	virtual ~GuiLayout();
	void setGeometry(sf::IntRect geometry_);
    void addChild(GuiWidget* child_);
	void update(sf::Time delta);
	void handleEvent(const sf::Event& event);
protected:
	virtual void updateChildrenGeometry() = 0;
	std::list<GuiWidget*> children;
	void draw(sf::RenderTarget &target,sf::RenderStates states) const;
};
}

#endif // header
