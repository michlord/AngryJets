#include <iostream>
#include "../../Engine/ResourceManager.h"
#include "../../Engine/Collision.h"

void loadResources(){
    engine::ResourceManager::resources_list_t resources_list;
    std::string directory = "C:/Dev/AngryJets/Tests/CollisionTest/Resources/";
    resources_list.push_back(std::make_tuple("arwing",directory+"arwing_ship.png",engine::ResourceManager::resource_type::TEXTURE));
    resources_list.push_back(std::make_tuple("thrust",directory+"thrust_ship.png",engine::ResourceManager::resource_type::TEXTURE));
    resources_list.push_back(std::make_tuple("font",directory+"font.ttf",engine::ResourceManager::resource_type::FONT));
    engine::rm->batchLoadResources(resources_list);
}

int main()
{
    loadResources();

    sf::Sprite  arwing(engine::rm->getTexture("arwing"));
    sf::Sprite  thrust(engine::rm->getTexture("thrust"));

    sf::Image   arwing_img = arwing.getTexture()->copyToImage();
    sf::Image   thrust_img = thrust.getTexture()->copyToImage();

    engine::BitmaskManager::getInstance()->addMask(*arwing.getTexture(),arwing_img);
    engine::BitmaskManager::getInstance()->addMask(*thrust.getTexture(),thrust_img);

    arwing.move(100,100);
    thrust.move(80,70);

    sf::Text text;
    text.setFont(engine::rm->getFont("font"));
    text.setString("Collision");
    text.setPosition(0,0);
    text.setColor(sf::Color::White);

    sf::RenderWindow window(sf::VideoMode(300, 300), "ResourceManager test");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        thrust.rotate(0.5f);


        window.clear(sf::Color::Blue);
        //if(engine::collision::spriteSpriteTest(arwing,engine::BitmaskManager::getInstance()->getMask(*arwing.getTexture()),
        //                            thrust,engine::BitmaskManager::getInstance()->getMask(*thrust.getTexture()))){
        if(engine::collision::spriteSpriteTest(arwing,thrust)){
            window.draw(text);
        }
        window.draw(arwing);
        window.draw(thrust);
        window.display();
    }
    return 0;

}
