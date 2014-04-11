#pragma once
#ifndef id5E94400F_BBF0_431E_8632A91562BDB22C
#define id5E94400F_BBF0_431E_8632A91562BDB22C

#include "../Engine/State.h"
#include "../Engine/Settings.h"
#include "../Engine/Gui.h"
#include <SFML/Audio.hpp>
#include <sigslot.h>

namespace game{

class StateMenu : public engine::State, public sigslot::has_slots<> {
public:
	StateMenu(sf::RenderWindow& window,engine::SettingsGame * settings);
	~StateMenu();
	void handleEvents(const sf::Event& event);
	void update();
	void draw();
    void onEnter();
    void onExit();

    sigslot::signal0<> play_signal;
    sigslot::signal0<> exit_signal;

protected:
    sf::Music                    menu_music;
    sf::Sprite                   logo;

    engine::SettingsGame*        settings;

    engine::GuiWindow*           menu_window;
    engine::GuiVerticalLayout*   vlayout;
    engine::GuiLabel*            play;
    engine::GuiLabel*            map_select;
    engine::GuiLabel*            ship1_select;
    engine::GuiLabel*            ship2_select;
    engine::GuiLabel*            exit;

    int                          map_idx;
    int                          ship1_idx;
    int                          ship2_idx;

    //slots
    void onPlaySelect();
    void onMapSelect();
    void onShip1Select();
    void onShip2Select();
    void onExitSelect();

};

}


#endif // header
