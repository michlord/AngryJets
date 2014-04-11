#include "GameLoop.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateMenu.h"
#include "StateGameplay.h"


namespace game{

GameLoop::GameLoop(){
	setup();
	loop();
}

GameLoop::~GameLoop(){
    //delete settings;
    //delete state_machine;

    //delete window;

}

void GameLoop::run(){
    static const float timestep = 1.0f/float(settings->fps);
    float accumulator = 0;
    timer.restart();
    while (window->isOpen())
    {
        while (accumulator >= timestep){
            //std::cout << "accumulator: " << accumulator << "\n";
            loop();
            accumulator -= timestep;
        }
        draw();
        accumulator += timer.restart().asSeconds();
    }
}

void GameLoop::setup(){
	settings = new engine::SettingsGame();
	settings->loadFromJsonFile("../Assets/settings.json");
	sf::VideoMode mode = sf::VideoMode(800, 600, 32);
    if(settings->fullscreen && mode.isValid()){
        window = new sf::RenderWindow(mode, "AngryJets", sf::Style::Fullscreen);
    } else {
        window = new sf::RenderWindow(mode, "AngryJets");
    }
    state_machine = new engine::StateMachine();

    StateGameplay * gameplay_state = new StateGameplay(*window,settings);
	StateMenu * menu_state = new StateMenu(*window,settings);
    state_machine->addState("gameplay",gameplay_state);
    state_machine->addState("menu",menu_state);
    state_machine->switchState("menu");

    menu_state->play_signal.connect(this,&GameLoop::onStartGameplay);
    menu_state->exit_signal.connect(this,&GameLoop::onExit);
    gameplay_state->exit_signal.connect(this,&GameLoop::onExit);
}

void GameLoop::loop(){
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        state_machine->handleEvents(event);
    }

    state_machine->update();
}

void GameLoop::draw(){
    window->clear();
    state_machine->draw();
    window->display();
}

void GameLoop::onSaveSettings(){

}

void GameLoop::onStartGameplay(){
    state_machine->switchState("gameplay");
}

void GameLoop::onEndGameplay(){

}

void GameLoop::onExit(){
    window->close();
}

}
