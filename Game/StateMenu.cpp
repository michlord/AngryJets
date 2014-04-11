#include "StateMenu.h"
#include <SFML/Graphics.hpp>
#include "../Engine/ResourceManager.h"
#include <stdexcept>
namespace game {

StateMenu::StateMenu(sf::RenderWindow& window,engine::SettingsGame * settings_):
State(window){



    settings = settings_;

    map_idx   = 0;
    ship1_idx = 0;
    ship2_idx = 0;
    if(menu_music.openFromFile(settings->directory+"Assets/sound/menu.ogg") == false){
        throw std::runtime_error("Error loading menu music");
    }


    engine::rm->loadTexture("menu/logo",settings->directory+"Assets/misc/logo.png");
    logo.setTexture(engine::rm->getTexture("menu/logo"));
    logo.setPosition(320,400);

    engine::rm->loadFont("menu/font",settings->directory+"Assets/font/nokia.ttf");
    menu_window = new engine::GuiWindow(window);
    vlayout = new engine::GuiVerticalLayout();
    play = new engine::GuiHighlightedLabel("Play",&engine::rm->getFont("menu/font"),sf::Color::White,sf::Color::Red);
    map_select = new engine::GuiHighlightedLabel(settings->map[map_idx],&engine::rm->getFont("menu/font"),sf::Color::White,sf::Color::Yellow);
    map_select->setFontSize(22);
    ship1_select = new engine::GuiHighlightedLabel(settings->ship[ship1_idx],&engine::rm->getFont("menu/font"),sf::Color::White,sf::Color::Yellow);
    ship1_select->setFontSize(22);
    ship2_select = new engine::GuiHighlightedLabel(settings->ship[ship2_idx],&engine::rm->getFont("menu/font"),sf::Color::White,sf::Color::Yellow);
    ship2_select->setFontSize(22);
    exit = new engine::GuiHighlightedLabel("Exit",&engine::rm->getFont("menu/font"),sf::Color::White,sf::Color::Red);

    engine::GuiLabel* map_select_msg = new engine::GuiLabel("Select map",&engine::rm->getFont("menu/font"),sf::Color(176,176,176));
    engine::GuiLabel* ship1_select_msg = new engine::GuiLabel("Select player 1 ship",&engine::rm->getFont("menu/font"),sf::Color(176,176,176));
    engine::GuiLabel* ship2_select_msg = new engine::GuiLabel("Select player 2 ship",&engine::rm->getFont("menu/font"),sf::Color(176,176,176));

    menu_window->setChild(vlayout);
    vlayout->setGeometry(sf::IntRect(100,100,100,400));
    vlayout->addChild(play);
    vlayout->addChild(map_select_msg);
    vlayout->addChild(map_select);
    vlayout->addChild(ship1_select_msg);
    vlayout->addChild(ship1_select);
    vlayout->addChild(ship2_select_msg);
    vlayout->addChild(ship2_select);
    vlayout->addChild(exit);

    play->clicked.connect(this,&StateMenu::onPlaySelect);
    map_select->clicked.connect(this,&StateMenu::onMapSelect);
    ship1_select->clicked.connect(this,&StateMenu::onShip1Select);
    ship2_select->clicked.connect(this,&StateMenu::onShip2Select);
    exit->clicked.connect(this,&StateMenu::onExitSelect);

}
StateMenu::~StateMenu(){}
void StateMenu::handleEvents(const sf::Event& event){
    menu_window->handleEvent(event);

}
void StateMenu::update(){}
void StateMenu::draw(){
    window.draw(logo);
    window.draw(*menu_window);
}

void StateMenu::onEnter(){
    menu_music.setLoop(true);
    menu_music.play();
}

void StateMenu::onExit(){
    menu_music.stop();
}

void StateMenu::onPlaySelect(){
    play_signal.emit();
}
void StateMenu::onMapSelect(){
    map_idx = (map_idx + 1) % settings->map.size();
    map_select->setText(settings->map[map_idx]);
    settings->selected_map = settings->map[map_idx];
}
void StateMenu::onShip1Select(){
    ship1_idx = (ship1_idx + 1) % settings->ship.size();
    ship1_select->setText(settings->ship[ship1_idx]);
    settings->player_settings[0].ship = settings->ship[ship1_idx];
}
void StateMenu::onShip2Select(){
    ship2_idx = (ship2_idx + 1) % settings->ship.size();
    ship2_select->setText(settings->ship[ship2_idx]);
    settings->player_settings[1].ship = settings->ship[ship2_idx];
}
void StateMenu::onExitSelect(){
    exit_signal.emit();
}

}
