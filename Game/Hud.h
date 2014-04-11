#pragma once
#ifndef id5AA1E112_A260_41BD_91DF1FAD25348B7B
#define id5AA1E112_A260_41BD_91DF1FAD25348B7B
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "../Engine/StringUtil.h"
#include "../Engine/Gui.h"
namespace game{
class Hud : public sf::Drawable{
public:
	Hud(sf::IntRect geometry_,Player* player_);
	void update();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::IntRect geometry;
	Player* player;
	engine::GuiHorizontalLayout* layout;
	engine::GuiHighlightedLabel* hull_lbl;
	engine::GuiHighlightedLabel* ammo_lbl;
	engine::GuiHighlightedLabel* fuel_lbl;
	engine::GuiHighlightedLabel* missles_lbl;
	engine::GuiHighlightedLabel* lives_lbl;
	engine::GuiHighlightedLabel* score_lbl;
};
}

#endif // header
