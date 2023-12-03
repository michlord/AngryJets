#include "Collision.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <stdexcept>


engine::BitmaskManager* engine::BitmaskManager::instance = nullptr;

namespace engine{

BitmaskManager::~BitmaskManager(){
	for(auto it=masks.begin(); it!=masks.end(); ++it){
		delete it->second;
	}
}

BitmaskManager* BitmaskManager::getInstance(){
	if(instance == nullptr){
		instance = new BitmaskManager();
	}
	return instance;
}

void BitmaskManager::addMask(const sf::Texture& texture,const sf::Image& mask){
	sf::Image *mask_copy = new sf::Image();
	*mask_copy = mask;
	masks[&texture] = mask_copy;
}

const sf::Image& BitmaskManager::getMask(const sf::Texture& texture){
	if(masks.find(&texture) != masks.end()){
		return (*masks[&texture]);
	} else {
		throw std::runtime_error("Unable to find mask for specified texture");
	}
}

bool BitmaskManager::isMaskAvailable(const sf::Texture& texture){
    return masks.find(&texture) != masks.end();
}

BitmaskManager::BitmaskManager(){

}

namespace collision{

bool checkIfPointInRectBounds(sf::Vector2f point, sf::IntRect bounds){
	return point.x > 0 && point.y > 0 && point.x < bounds.width && point.y < bounds.height;
}

bool spriteSpriteTest(const sf::Sprite& left_sprite, const sf::Image* left_mask, const sf::Sprite& right_sprite, const sf::Image* right_mask, sf::Color left_alpha_color, sf::Color right_alpha_color){

	if(left_mask == nullptr){
        if(BitmaskManager::getInstance()->isMaskAvailable(*left_sprite.getTexture()) == false){
            BitmaskManager::getInstance()->addMask(*left_sprite.getTexture(),left_sprite.getTexture()->copyToImage());
        }
        left_mask = &BitmaskManager::getInstance()->getMask(*left_sprite.getTexture());
    }

    if(right_mask == nullptr){
        if(BitmaskManager::getInstance()->isMaskAvailable(*right_sprite.getTexture()) == false){
            BitmaskManager::getInstance()->addMask(*right_sprite.getTexture(),right_sprite.getTexture()->copyToImage());
        }
        right_mask = &BitmaskManager::getInstance()->getMask(*right_sprite.getTexture());
    }

	sf::FloatRect intersection;
	if (left_sprite.getGlobalBounds().intersects(right_sprite.getGlobalBounds(), intersection)){
		sf::IntRect left_bounds  = left_sprite.getTextureRect();
		sf::IntRect right_bounds = right_sprite.getTextureRect();
		for (int i = intersection.left; i < intersection.left+intersection.width; i++) {
				for (int j = intersection.top; j < intersection.top+intersection.height; j++) {
				sf::Vector2f o1v = left_sprite.getInverseTransform().transformPoint(i, j);
				sf::Vector2f o2v = right_sprite.getInverseTransform().transformPoint(i, j);
				if (checkIfPointInRectBounds(o1v,left_bounds) && checkIfPointInRectBounds(o2v,right_bounds)) {
					int x1,x2,y1,y2;
					x1 = (int)(o1v.x)+left_bounds.left;
					y1 = (int)(o1v.y)+left_bounds.top;
					x2 = (int)(o2v.x)+right_bounds.left;
					y2 = (int)(o2v.y)+right_bounds.top;

					sf::Color left_color  = left_mask->getPixel(x1,y1);
					sf::Color right_color = right_mask->getPixel(x2,y2);

                    //handle special case for transparent alpha color because
                    //there are many colors that can be transparent and only alpha value
                    //is important
                    if(left_alpha_color == sf::Color::Transparent){
                            if(left_color.a == 0)
                                left_color = sf::Color::Transparent;
                    }
                    if(right_alpha_color == sf::Color::Transparent){
                            if(right_color.a == 0)
                                right_color = sf::Color::Transparent;
                    }

					if((left_color != left_alpha_color) && (right_color != right_alpha_color)){
					    //std::cout << "left color: r: " << (int)left_color.r << " g: " << (int)left_color.g << " b: " << (int)left_color.b << " a: " << (int)left_color.a <<"\n";
                        //std::cout << "right color: r: " << (int)right_color.r << " g: " << (int)right_color.g << " b: " << (int)right_color.b << " a: " << (int)right_color.a <<"\n";
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool spriteSpriteTest(const sf::Sprite& left_sprite, const sf::Sprite& right_sprite, sf::Color left_alpha_color, sf::Color right_alpha_color){

    if(BitmaskManager::getInstance()->isMaskAvailable(*left_sprite.getTexture()) == false){
        BitmaskManager::getInstance()->addMask(*left_sprite.getTexture(),left_sprite.getTexture()->copyToImage());
    }
    if(BitmaskManager::getInstance()->isMaskAvailable(*right_sprite.getTexture()) == false){
        BitmaskManager::getInstance()->addMask(*right_sprite.getTexture(),right_sprite.getTexture()->copyToImage());
    }

    const sf::Image& left_mask    = BitmaskManager::getInstance()->getMask(*left_sprite.getTexture());
    const sf::Image& right_mask   = BitmaskManager::getInstance()->getMask(*right_sprite.getTexture());

    return spriteSpriteTest(left_sprite,&left_mask,right_sprite,&right_mask,left_alpha_color,right_alpha_color);
}

bool pointSpriteTest(const sf::Sprite& sprite, const sf::Image& mask, sf::Vector2f point, sf::Color alpha_color ){
	if( sprite.getGlobalBounds().contains(point) ){
		sf::IntRect texture_bounds = sprite.getTextureRect();
		sf::Vector2f position_on_texture = sprite.getInverseTransform().transformPoint(point);
        if( checkIfPointInRectBounds(position_on_texture,texture_bounds) == true ){
            sf::Color color = mask.getPixel(position_on_texture.x,position_on_texture.y);

            if(alpha_color == sf::Color::Transparent){
                if(color.a == 0)
                    color = sf::Color::Transparent;
            }

			if(color != alpha_color){
				return true;
			}
        }
	}
	return false;
}

bool pointSpriteTest(const sf::Sprite& sprite, sf::Vector2f point, sf::Color alpha_color){
    if(BitmaskManager::getInstance()->isMaskAvailable(*sprite.getTexture()) == false){
        BitmaskManager::getInstance()->addMask(*sprite.getTexture(),sprite.getTexture()->copyToImage());
    }
    const sf::Image& mask = BitmaskManager::getInstance()->getMask(*sprite.getTexture());
    return pointSpriteTest(sprite,mask,point,alpha_color);
}

}
}
