#include "Ground.h"
#include <iostream>
namespace game{
bool checkIfPointInRectBounds(sf::Vector2f point, sf::IntRect bounds){
	return point.x > 0 && point.y > 0 && point.x < bounds.width && point.y < bounds.height;
}

Ground::Ground(const sf::Texture& background_,const sf::Texture& foreground_, const sf::Image& mask_){
	mask = mask_;
	foreground = foreground_;
	background = background_;
	//texture.loadFromImage(mask);
	sprite.setTexture(foreground);
}
void Ground::makeCircleHole(sf::Vector2f position, float radius){

}
void Ground::makeSquareHole(sf::Vector2f position, int size){
	if( sprite.getGlobalBounds().contains(position) ){
		sf::IntRect texture_bounds = sprite.getTextureRect();
		sf::Vector2f position_on_texture = sprite.getInverseTransform().transformPoint(position);

		sf::Vector2i top_left_position(position_on_texture.x-size/2,position_on_texture.y-size/2);
		for(int i=top_left_position.x;i<=position_on_texture.x+size/2;++i){
		    for(int j=top_left_position.y;j<=position_on_texture.y+size/2;++j){
		        sf::Vector2f final_position(i,j);
                if( checkIfPointInRectBounds(final_position,texture_bounds) == true ){
                    if(mask.getPixel(final_position.x,final_position.y) != sf::Color::Red){
                        mask.setPixel(final_position.x,final_position.y,sf::Color::Black);
                        sf::Image pixel;
                        pixel.create(1,1,sf::Color::Transparent);
                        foreground.update(pixel,final_position.x,final_position.y);
                    }
                }
		    }
        }

		//std::cout << position_on_texture.x << " " << position_on_texture.y << "\n";
		/*
            if( checkIfPointInRectBounds(position_on_texture,texture_bounds) == true ){
                mask.setPixel(position_on_texture.x,position_on_texture.y,sf::Color::Black);
                sf::Image pixel;
                pixel.create(1,1,sf::Color::Transparent);
                foreground.update(pixel,position_on_texture.x,position_on_texture.y);
            }
        */
	}
}

std::vector<sf::Vector2f> Ground::makeSquareHoleGetPixels(sf::Vector2f position, int size){
    std::vector<sf::Vector2f> output;
    output.reserve(size*size);
    if( sprite.getGlobalBounds().contains(position) ){
		sf::IntRect texture_bounds = sprite.getTextureRect();
		sf::Vector2f position_on_texture = sprite.getInverseTransform().transformPoint(position);

		sf::Vector2i top_left_position(position_on_texture.x-size/2,position_on_texture.y-size/2);
		for(int i=top_left_position.x;i<=position_on_texture.x+size/2;++i){
		    for(int j=top_left_position.y;j<=position_on_texture.y+size/2;++j){
		        sf::Vector2f final_position(i,j);
		        if(mask.getPixel(final_position.x,final_position.y) != sf::Color::Black)
                    output.push_back(sprite.getTransform().transformPoint(final_position));
                if( checkIfPointInRectBounds(final_position,texture_bounds) == true ){
                    mask.setPixel(final_position.x,final_position.y,sf::Color::Black);
                    sf::Image pixel;
                    pixel.create(1,1,sf::Color::Transparent);
                    foreground.update(pixel,final_position.x,final_position.y);
                }
		    }
        }
	}
	return output;
}
void Ground::makeSpriteHole(sf::Sprite sprite){

}
void Ground::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Sprite tmp = sprite;
    tmp.setTexture(background);
    target.draw(tmp);
    tmp.setTexture(foreground);
    target.draw(tmp);
}

sf::Sprite Ground::getCollisionSprite(){
	return sprite;
}
sf::Color Ground::getAlphaColor(){
	return sf::Color::Black;
}
const sf::Image* Ground::getCollisionMask(){
	return &mask;
}

void Ground::setScale(float scale){
    sprite.setScale(scale,scale);
}

sf::Vector2f Ground::getSize(){
    return sf::Vector2f(background.getSize().x*sprite.getScale().x,background.getSize().y*sprite.getScale().y);
}

}
