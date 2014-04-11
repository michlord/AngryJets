#include <SFML/Graphics.hpp>
#include "Ground.h"
#include <iostream>
#include <cmath>


static sf::VertexArray arr(sf::PrimitiveType::Points);

class Particle{
    public:

    sf::Vector2f position;
    sf::Vector2f speed;
    void init(sf::Vector2f initial_pos){
        speed.x = rand()%20-10;
        speed.y = rand()%20-10;
        position = initial_pos;
    }
    void update(float dt){
        //gravity
        speed.y += dt;
        //air resistance
        speed.x = 0.99*speed.x;
        position.x += speed.x*dt;
        position.y += speed.y*dt;
    }

};


int main()
{
    std::vector<Particle> particles;

    sf::RenderWindow window(sf::VideoMode(800, 600), "AngryJets");

    sf::Texture ground_foreground;
    ground_foreground.loadFromFile("assets/map/mount_doom_fg.png");
    sf::Texture ground_background;
    ground_background.loadFromFile("assets/map/mount_doom_bg.png");
    sf::Image ground_mask;
    ground_mask.loadFromFile("assets/map/mount_doom_mask.png");

    Ground ground(ground_background,ground_foreground,ground_mask);
    ground.sprite.setScale(1.4f,1.4f);
    ground.sprite.move(-50,-800);
    //ground.sprite.rotate(4);

    sf::Vector2f position(200,200);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            //localPosition.y += 400;
            //std::cout << localPosition.x << " " << localPosition.y << "\n";
            //ground.makeSquareHole(sf::Vector2f(localPosition.x,localPosition.y),20);
            std::vector<sf::Vector2f> out = ground.makeHole(sf::Vector2f(localPosition.x,localPosition.y),50);
            int old_size = particles.size();
            particles.resize(particles.size()+out.size());
            arr.resize(particles.size()+out.size());
            for(int i=old_size-1;i<particles.size();++i){

                particles[i].init(out[i-old_size+1]);
            }
            //particles.insert( particles.end(), out.begin(), out.end() );
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            position.y += 1.8;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            position.x -= 1.8;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            position.x += 1.8;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            position.y -= 1.8;
        }
        for(auto it=particles.begin();it!=particles.end();++it){
            it->update(.1);
        }
        for(int i=0;i<particles.size();++i){
            arr[i].color = sf::Color::White;
            arr[i].position = particles[i].position;
        }
        ground.makeSquareHole(position,20);
        //ground.sprite.rotate(.03);
        window.clear();
        window.draw(ground);
        //for(auto it=particles.begin();it!=particles.end();++it){
           // window.draw(*it);
        //}
        window.draw(arr);
        window.display();
    }

    return 0;
}
