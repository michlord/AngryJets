#include "Hud.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StringUtil.h"
namespace game{
Hud::Hud(sf::IntRect geometry_,Player* player_){

	geometry = geometry_;
	player = player_;
	layout = new engine::GuiHorizontalLayout();
	hull_lbl = new engine::GuiHighlightedLabel("Hull: ",&engine::rm->getFont("menu/font"));
	hull_lbl->setFontSize(17);
	ammo_lbl = new engine::GuiHighlightedLabel("Ammo: ",&engine::rm->getFont("menu/font"));
	ammo_lbl->setFontSize(17);
	fuel_lbl = new engine::GuiHighlightedLabel("Fuel: ",&engine::rm->getFont("menu/font"));
	fuel_lbl->setFontSize(17);
	missles_lbl = new engine::GuiHighlightedLabel("Missles: ",&engine::rm->getFont("menu/font"));
	missles_lbl->setFontSize(17);
	lives_lbl = new engine::GuiHighlightedLabel("Lives: ",&engine::rm->getFont("menu/font"));
	lives_lbl->setFontSize(17);
	score_lbl = new engine::GuiHighlightedLabel("Score: ",&engine::rm->getFont("menu/font"));
	score_lbl->setFontSize(17);
	layout->addChild(hull_lbl);
	layout->addChild(fuel_lbl);
	layout->addChild(ammo_lbl);
	layout->addChild(missles_lbl);
	layout->addChild(lives_lbl);
	layout->addChild(score_lbl);
	layout->setGeometry(geometry);
}

void Hud::update(){
    hull_lbl->setText("Hull:\n" + engine::convertToStdString(player->current_vehicle->hull));
    fuel_lbl->setText("Fuel:\n" + engine::convertToStdString(player->current_vehicle->fuel));
    ammo_lbl->setText("Ammo:\n" + engine::convertToStdString(player->current_vehicle->ammo));
    missles_lbl->setText("Missles:\n" + engine::convertToStdString(player->current_vehicle->missles));
    lives_lbl->setText("Lives:\n" + engine::convertToStdString(player->lives));
    score_lbl->setText("Score:\n" + engine::convertToStdString(player->score));

}

void Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(*layout);
}

}
