#include "StateGameplay.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SoundRecycler.h"
#include "../Engine/Collision.h"
#include "GunMinigun.h"
#include <SFML/Audio.hpp>
#include "../Engine/Gui.h"
#include <iostream>
#include <cmath>

namespace game {
StateGameplay::StateGameplay(sf::RenderWindow& window,engine::SettingsGame * settings_):
    State(window){
    settings = settings_;



}
StateGameplay::~StateGameplay(){
    delete map_settings;
    delete ground;
    for(int i=0;i<2;++i){
        delete ships[i];
        delete flags[i];
        delete jetmans[i];
    }
    delete game_end_msg;
}
void StateGameplay::handleEvents(const sf::Event& event){

}
void StateGameplay::update(){





    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        exit_signal.emit();
    }

    if(game_end == true)
        return;

    engine::sr->recycle();

    for(int i=0;i<2;++i){
        float x = players[i].current_vehicle->getPosition().x - map_settings->player_spawn[i].ship_pos.x*map_settings->scale;
        float y = players[i].current_vehicle->getPosition().y - map_settings->player_spawn[i].ship_pos.y*map_settings->scale;
        float distance_to_base = sqrt(x*x+y*y);
        if(players[i].current_vehicle->landed &&
           players[i].vehicle_type != Player::VehicleType::SHIP){
            if(distance_to_base < 100.0f){
                players[i].vehicle_type = Player::VehicleType::SHIP;
                players[i].current_vehicle = ships[i];
                players[i].current_vehicle->reset(100,100,100,100,0.0f,
                                                sf::Vector2f(map_settings->player_spawn[i].ship_pos.x*map_settings->scale,
                                                map_settings->player_spawn[i].ship_pos.y*map_settings->scale));
            }
        }
        if(players[i].current_vehicle->landed && distance_to_base < 100.0f){
            if((flags[i]->isCaptured() == false) && (flags[!i]->isCaptured() == true)){
                flags[!i]->setCaptor(nullptr);
                players[i].score += 5;
                sf::Sound *excellent_sound = new sf::Sound(engine::rm->getSoundBuffer("gameplay/sound/excellent"));
                excellent_sound->play();
                engine::sr->addSound(excellent_sound);
            }
        }
    }

    for(int i=0;i<2;++i){



        if(players[i].current_vehicle->dead == true){
            switch (players[i].vehicle_type){

                case Player::VehicleType::JETMAN:
                {
                    players[i].vehicle_type = Player::VehicleType::SHIP;
                    players[i].current_vehicle = ships[i];
                    players[i].current_vehicle->reset(100,100,100,100,0.0f,
                                                        sf::Vector2f(map_settings->player_spawn[i].ship_pos.x*map_settings->scale,
                                                         map_settings->player_spawn[i].ship_pos.y*map_settings->scale));
                    players[i].onDie();
                    sf::Sound *jetman_die_sound = new sf::Sound(engine::rm->getSoundBuffer("gameplay/sound/blood_splash"));
                    jetman_die_sound->play();
                    engine::sr->addSound(jetman_die_sound);

                    if(players[i].lives == 0){
                        game_end = true;
                        if(players[0].score > players[1].score){
                            game_end_msg->setText("GameOver\nLeft player wins!");
                        }else if (players[0].score == players[1].score){
                            game_end_msg->setText("GameOver\nDraw!");
                        } else {
                            game_end_msg->setText("GameOver\nRight player wins!");
                        }
                        return;
                    }

                    flags[!i]->setCaptor(nullptr);


                    break;
                }
                case Player::VehicleType::SHIP:
                default:
                {
                    players[i].vehicle_type = Player::VehicleType::JETMAN;
                    sf::Vector2f crash_place = players[i].current_vehicle->getPosition();
                    players[i].current_vehicle = jetmans[i];
                    players[i].current_vehicle->reset(50,50,50,50,0.0f,
                                                        crash_place);
                    sf::Sound *ship_die_sound = new sf::Sound(engine::rm->getSoundBuffer("gameplay/sound/ship_crash"));
                    ship_die_sound->play();
                    engine::sr->addSound(ship_die_sound);

                    break;
                }
            }
            players[i].current_vehicle->dead = false;
            players[!i].onScore(1);
        }

    }

    //Get input
    for(int i=0;i<2;++i){
        if (sf::Keyboard::isKeyPressed(settings->player_settings[i].keybinding.left)){
            players[i].current_vehicle->onLeft();
        }
        if (sf::Keyboard::isKeyPressed(settings->player_settings[i].keybinding.right)){
            players[i].current_vehicle->onRight();
        }
        if (sf::Keyboard::isKeyPressed(settings->player_settings[i].keybinding.up)){
            players[i].current_vehicle->onUp();
        }
        if (sf::Keyboard::isKeyPressed(settings->player_settings[i].keybinding.primary)){
            players[i].current_vehicle->onPrimary();
            std::list<Bullet*> list = players[i].current_primary_gun->shoot(players[i].current_vehicle);
            bullets.insert(bullets.begin(),list.begin(),list.end());
        }
        if (sf::Keyboard::isKeyPressed(settings->player_settings[i].keybinding.secondary)){
            players[i].current_vehicle->onSecondary();
        }
    }
    //Update logic
    for(int i=0;i<2;++i){
        players[i].current_vehicle->update();
        players[i].current_primary_gun->update();
        flags[!i]->update();
    }

    for(auto it = bullets.begin(); it != bullets.end(); ++it){
            (*it)->update();
    }

    //ground->makeSquareHole(players[0].current_vehicle->getPosition(),20);

    for(int i=0;i<2;++i){
        //Does the ship collide with the ground?
        //If yes then check if it landed on a spacestation
        if(engine::collision::spriteSpriteTest(players[i].current_vehicle->getCollisionSprite(),nullptr,
                                               ground->getCollisionSprite(),ground->getCollisionMask(),
                                               players[i].current_vehicle->getAlphaColor(),
                                               ground->getAlphaColor())){
            sf::Vector2f bottom_sensor(players[i].current_vehicle->getCollisionSprite().getOrigin().x,players[i].current_vehicle->getCollisionSprite().getOrigin().y+35);
            bottom_sensor = players[i].current_vehicle->getCollisionSprite().getTransform().transformPoint(bottom_sensor);
            if(engine::collision::pointSpriteTest(ground->getCollisionSprite(),*ground->getCollisionMask(),bottom_sensor,sf::Color::Red) == false){
                players[i].current_vehicle->setLanded();
            } else { //crashed into the ground
                players[i].current_vehicle->takeDamage(100.0f);
            }
        }
    }



    for(int i=0;i<2;++i){
        if(!ground->getCollisionSprite().getGlobalBounds().intersects(players[i].current_vehicle->getCollisionSprite().getGlobalBounds())){
            players[i].current_vehicle->takeDamage(100.0f);
        }
    }


    if(engine::collision::spriteSpriteTest(players[0].current_vehicle->getCollisionSprite(),
                                           players[0].current_vehicle->getCollisionMask(),
                                           players[1].current_vehicle->getCollisionSprite(),
                                           players[1].current_vehicle->getCollisionMask())){
        resolveVehicleCollision(players[0].current_vehicle,players[1].current_vehicle);
    }
    for(int i=0;i<2;++i){
        for(auto it = bullets.begin(); it != bullets.end(); ++it){
        Bullet* b = *it;

            if(engine::collision::spriteSpriteTest(players[i].current_vehicle->getCollisionSprite(),
                                               players[i].current_vehicle->getCollisionMask(),
                                               b->getCollisionSprite(),
                                               b->getCollisionMask())){
                players[i].current_vehicle->takeDamage(b->getDamage());
                b->onHit();
                delete b;
                it = bullets.erase(it);
            }
        }
    }

    for(auto it = bullets.begin(); it != bullets.end(); ++it){
            Bullet * b = *it;
            if(engine::collision::spriteSpriteTest(b->getCollisionSprite(),b->getCollisionMask(),
                                                   ground->getCollisionSprite(),ground->getCollisionMask(),
                                                   b->getAlphaColor(),ground->getAlphaColor())){
                ground->makeSquareHole(b->getPosition(),16);
                b->onHit();
                delete b;
                it = bullets.erase(it);
            }
    }

    //capture flags

    for(int i=0;i<2;++i){
        if(flags[i]->isCaptured() == false){
            if(engine::collision::spriteSpriteTest(players[!i].current_vehicle->getCollisionSprite(),
                                                    players[!i].current_vehicle->getCollisionMask(),
                                                   flags[i]->getCollisionSprite(),
                                                   flags[i]->getCollisionMask())){
                flags[i]->setCaptor(&players[!i]);
            }
        }
    }



    //Update camera
    for(int i=0;i<2;++i){
        views[i].setCenter(GetBoundedCameraPosition(players[i].current_vehicle->getPosition(),
                                                     ground->getSize(),
                                                     views[i].getSize()));
    }
    for(int i=0;i<2;++i){
        huds[i]->update();
    }


}
void StateGameplay::draw(){
    window.setView(window.getDefaultView());
    window.clear();

    for(int i=0;i<2;++i){
        window.setView(views[i]);

        window.draw(*ground);
        for(int i=0; i<2;++i){
            if(players[i].current_vehicle->dead == false){
                window.draw(*players[i].current_vehicle);
            }
            window.draw(*flags[i]);
        }
        for(auto it = bullets.begin(); it != bullets.end(); ++it){
            window.draw(**it);
        }

    }
    window.setView(window.getDefaultView());
    window.draw(splitting_line);
    for(int i=0;i<2;++i){
        window.draw(*huds[i]);
    }

    if(game_end){
        window.draw(*game_end_msg);

    }

}
void StateGameplay::onEnter(){

    game_end = false;

    map_settings = new engine::SettingsMap();
    std::string map_settings_path = settings->directory + "Assets/map/" + settings->selected_map + ".json";
	map_settings->loadFromJsonFile(map_settings_path);

    engine::rm->loadTexture("gameplay/texture/left_ship",settings->directory+"Assets/ship/"+settings->player_settings[0].ship+".png");
    engine::rm->loadTexture("gameplay/texture/right_ship",settings->directory+"Assets/ship/"+settings->player_settings[1].ship+".png");
    engine::rm->loadTexture("gameplay/texture/left_flag",settings->directory+"Assets/flag/"+settings->player_settings[0].flag+".png");
    engine::rm->loadTexture("gameplay/texture/right_flag",settings->directory+"Assets/flag/"+settings->player_settings[1].flag+".png");

    engine::rm->loadSoundBuffer("gameplay/sound/laser",settings->directory+"Assets/sound/laser.wav");
    engine::rm->loadSoundBuffer("gameplay/sound/shotgun",settings->directory+"Assets/sound/shotgun.wav");
    engine::rm->loadSoundBuffer("gameplay/sound/explosion",settings->directory+"Assets/sound/explosion.wav");

    engine::rm->loadTexture("gameplay/texture/ground/background",settings->directory+"Assets/map/"+map_settings->background+".png");
    engine::rm->loadTexture("gameplay/texture/ground/foreground",settings->directory+"Assets/map/"+map_settings->foreground+".png");
    engine::rm->loadTexture("gameplay/texture/ground/mask",settings->directory+"Assets/map/"+map_settings->mask+".png");

    ground = new Ground(engine::rm->getTexture("gameplay/texture/ground/background"),
                        engine::rm->getTexture("gameplay/texture/ground/foreground").copyToImage(),
                        engine::rm->getTexture("gameplay/texture/ground/mask").copyToImage());

    ground->setScale(map_settings->scale);


    views[0].setViewport(sf::FloatRect(0, 0, 0.5f, 1));
    views[0].reset(sf::FloatRect(0, 0, window.getSize().x/2, window.getSize().y));
    views[1].setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
    views[1].reset(sf::FloatRect(0, 0, window.getSize().x/2, window.getSize().y));

    splitting_line.setSize(sf::Vector2f(2,window.getSize().y));
    splitting_line.setPosition(window.getSize().x/2,0);
    splitting_line.setFillColor(sf::Color(115,115,115));

    ships[0] = new Ship(engine::rm->getTexture("gameplay/texture/left_ship"));
    ships[0]->reset(100.0f,100.0f,100.0f,100.0f,0.0f,sf::Vector2f(map_settings->player_spawn[0].ship_pos.x*map_settings->scale,map_settings->player_spawn[0].ship_pos.y*map_settings->scale));
    ships[1] = new Ship(engine::rm->getTexture("gameplay/texture/right_ship"));
    ships[1]->reset(100.0f,100.0f,100.0f,100.0f,0.0f,sf::Vector2f(map_settings->player_spawn[1].ship_pos.x*map_settings->scale,map_settings->player_spawn[1].ship_pos.y*map_settings->scale));

    engine::rm->loadTexture("gameplay/ammo/minigun",settings->directory+"Assets/ammo/minigun.png");
    engine::rm->loadSoundBuffer("gameplay/sound/shotgun",settings->directory+"Assets/sound/shotgun.wav");
    engine::rm->loadSoundBuffer("gameplay/sound/laser",settings->directory+"Assets/sound/laser.wav");
    engine::rm->loadSoundBuffer("gameplay/sound/explosion",settings->directory+"Assets/sound/explosion.wav");
    engine::rm->loadSoundBuffer("gameplay/sound/bullet_hit",settings->directory+"Assets/sound/bullet_hit.wav");
    engine::rm->loadSoundBuffer("gameplay/sound/ship_crash",settings->directory+"Assets/sound/ship_crash.wav");
    engine::rm->loadSoundBuffer("gameplay/sound/blood_splash",settings->directory+"Assets/sound/blood_splash.wav");
     engine::rm->loadSoundBuffer("gameplay/sound/excellent",settings->directory+"Assets/sound/excellent.wav");

    for(int i=0;i<2;++i){
        players[i] = Player(5,0,ships[i],new GunMinigun(5),Player::VehicleType::SHIP);
    }

    huds[0] = new Hud(sf::IntRect(0,window.getSize().y-50,window.getSize().x/2,50),&players[0]);
    huds[1] = new Hud(sf::IntRect(window.getSize().x/2,window.getSize().y-50,window.getSize().x/2,50),&players[1]);


    engine::rm->loadTexture("gameplay/texture/jetman",settings->directory+"Assets/ship/jetman.png");
    jetmans[0] = new Jetman(engine::rm->getTexture("gameplay/texture/jetman"));
    jetmans[1] = new Jetman(engine::rm->getTexture("gameplay/texture/jetman"));

    game_end_msg = new engine::GuiLabel("Game over",&engine::rm->getFont("menu/font"));
    game_end_msg->setGeometry(sf::IntRect(0,0,window.getSize().x,window.getSize().y));
    game_end_msg->setAlignment(engine::GuiLabel::alignment::CENTER);

    flags[0] = new Flag(engine::rm->getTexture("gameplay/texture/left_flag"),sf::Vector2f(map_settings->player_spawn[0].flag_pos.x*map_settings->scale,
                                                                                          map_settings->player_spawn[0].flag_pos.y*map_settings->scale));
    flags[1] = new Flag(engine::rm->getTexture("gameplay/texture/right_flag"),sf::Vector2f(map_settings->player_spawn[1].flag_pos.x*map_settings->scale,
                                                                                          map_settings->player_spawn[1].flag_pos.y*map_settings->scale));



}
void StateGameplay::onExit(){
}


sf::Vector2f StateGameplay::GetBoundedCameraPosition(sf::Vector2f requestedPos_, sf::Vector2f bounds_, sf::Vector2f viewSize_){
        if(requestedPos_.x < viewSize_.x/2.0f)
            requestedPos_.x = viewSize_.x/2.0f;
        if(requestedPos_.x + viewSize_.x/2.0f > bounds_.x)
            requestedPos_.x = bounds_.x - viewSize_.x/2.0f;
        if(requestedPos_.y < viewSize_.y/2.0f)
            requestedPos_.y = viewSize_.y/2.0f;
        if(requestedPos_.y + viewSize_.y/2.0f > bounds_.y)
            requestedPos_.y = bounds_.y - viewSize_.y/2.0f;
        return requestedPos_;
}

void StateGameplay::resolveVehicleCollision(Vehicle *left, Vehicle *right){
    left->takeDamage(30);
    right->takeDamage(30);
    left->setSpeed(sf::Vector2f(-left->getSpeed().x/2.0f,-left->getSpeed().y/2.0f));
    right->setSpeed(sf::Vector2f(-right->getSpeed().x/2.0f,-right->getSpeed().y/2.0f));


}

}
