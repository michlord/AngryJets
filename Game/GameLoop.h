#pragma once
#ifndef id5DA2D097_1784_4852_930C4E586324C3D5
#define id5DA2D097_1784_4852_930C4E586324C3D5

#include "../Engine/Settings.h"
#include "../Engine/StateMachine.h"
#include "../Engine/ResourceManager.h"
#include <sigslot.h>

namespace game{

class GameLoop : public sigslot::has_slots<>{
public:
	GameLoop();
	~GameLoop();
	void run();
private:

	void setup();
	void loop();
	void draw();

	engine::SettingsGame *  settings;
	engine::StateMachine *  state_machine;
	sf::RenderWindow *		window;
	sf::Clock               timer;



	void onSaveSettings();
	void onStartGameplay();
	void onEndGameplay();
	void onExit();
};

}

#endif
