#pragma once
#ifndef idA1E8AA34_1FB5_4EBB_8E2EF8136DBDF06A
#define idA1E8AA34_1FB5_4EBB_8E2EF8136DBDF06A

#include "../Engine/State.h"
#include <sigslot.h>
#include "../Engine/Gui.h"
#include "../Engine/Settings.h"
#include "../Engine/Settings/SettingsMap.h"
#include "Ground.h"
#include "Player.h"
#include "Ship.h"
#include "Jetman.h"
#include "Bullet.h"
#include <list>
#include "Hud.h"
#include "Flag.h"
namespace game {
class StateGameplay : public engine::State, public sigslot::has_slots<>  {
public:
	StateGameplay(sf::RenderWindow& window,engine::SettingsGame * settings);
	~StateGameplay();
	void handleEvents(const sf::Event& event);
	void update();
	void draw();
	void onEnter();
	void onExit();
	sigslot::signal0<> exit_signal;
private:
	engine::SettingsMap *       map_settings;
	engine::SettingsGame *      settings;

    Ground*                     ground;
    sf::View                    views[2];
    sf::RectangleShape          splitting_line;

    Player                      players[2];
    Ship*                       ships[2];
    Jetman*                     jetmans[2];
    Flag*                       flags[2];

    std::list<Bullet* >         bullets;

    Hud*                        huds[2];


    bool                        game_end;
    engine::GuiLabel*           game_end_msg;

    sf::Vector2f GetBoundedCameraPosition(sf::Vector2f requestedPos_, sf::Vector2f bounds_, sf::Vector2f viewSize_);
    void resolveVehicleCollision(Vehicle *left, Vehicle *right);




};

}

#endif // header
