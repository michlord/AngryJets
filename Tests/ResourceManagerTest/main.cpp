#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../Engine/ResourceManager.h"
#include <tuple>
using namespace std;

int main()
{

    engine::ResourceManager* res = engine::rm;
    //or engine::ResourceManager* res = engine::ResourceManager::getInstance();

    engine::ResourceManager::resources_list_t resources_list;
    std::string directory = "C:/Dev/AngryJets/Tests/ResourceManagerTest/Resources/";
    resources_list.push_back(std::make_tuple("texture",directory+"texture.bmp",engine::ResourceManager::resource_type::TEXTURE));
    resources_list.push_back(std::make_tuple("sound",directory+"sound.wav",engine::ResourceManager::resource_type::SOUND));
    resources_list.push_back(std::make_tuple("font",directory+"font.ttf",engine::ResourceManager::resource_type::FONT));
    res->batchLoadResources(resources_list);

    sf::Sprite sprite;
    sprite.setTexture(res->getTexture("texture"));

    //Maybe lets make an utility function taking font name and string and returning sf::Text.
    sf::Text text;
    text.setFont(res->getFont("font"));
    text.setString("notice sound playing");
    text.setPosition(0,50);

    sf::Sound sound;
    sound.setBuffer(res->getSoundBuffer("sound"));

    sf::RenderWindow window(sf::VideoMode(300, 300), "ResourceManager test");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite);
        window.draw(text);
        if(sound.getStatus() != sf::Sound::Status::Playing){
           sound.play();
        }
        window.display();
    }
    return 0;
}
