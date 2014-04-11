#pragma once
#ifndef id09BCAE6F_2E77_4EB9_8158157D6C78832A
#define id09BCAE6F_2E77_4EB9_8158157D6C78832A
#include "GuiLayout.h"
namespace engine{
class GuiVerticalLayout : public GuiLayout {
protected:
	void updateChildrenGeometry();
};
}

#endif // header
