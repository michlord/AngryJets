#include "ResourceManager.h"

#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
engine::ResourceManager* engine::ResourceManager::instance = nullptr;

namespace engine{



sf::Texture& ResourceManager::getTexture(const std::string& name){
	if(textures.find(name) != textures.end()){
        return(*textures[name]);
	} else {
		throw std::runtime_error("Texture not found in the resource manager. Name: " + name);
	}
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& name){
	if(sounds.find(name) != sounds.end()){
        return(*sounds[name]);
	} else {
		throw std::runtime_error("Sound not found in the resource manager. Name: " + name);
	}
}

sf::Font& ResourceManager::getFont(const std::string& name){
	if(fonts.find(name) != fonts.end()){
        return(*fonts[name]);
	} else {
		throw std::runtime_error("Font not found in the resource manager. Name: " + name);
	}
}

void ResourceManager::addTexture(const std::string& name,const sf::Texture& texture){
	sf::Texture *texture_ = new sf::Texture();
	*texture_ = texture;
	textures[name] = texture_;
}

void ResourceManager::addSoundBuffer(const std::string& name,const sf::SoundBuffer& sound_buffer){
	sf::SoundBuffer *sound_buffer_ = new sf::SoundBuffer();
	*sound_buffer_ = sound_buffer;
	sounds[name] = sound_buffer_;
}

void ResourceManager::addFont(const std::string& name,const sf::Font& font){
	sf::Font *font_ = new sf::Font();
	*font_ = font;
	fonts[name] = font_;
}

bool ResourceManager::releaseTexture(const std::string& name){
	auto it = textures.find(name);
	if(it != textures.end()){
		delete (*it).second;
		return true;
	} else {
		return false;
	}
}

bool ResourceManager::releaseSoundBuffer(const std::string& name){
	auto it = sounds.find(name);
	if(it != sounds.end()){
		delete (*it).second;
		return true;
	} else {
		return false;
	}
}

bool ResourceManager::releaseFont(const std::string& name){
	auto it = fonts.find(name);
	if(it != fonts.end()){
		delete (*it).second;
		return true;
	} else {
		return false;
	}
}

void ResourceManager::releaseAllResources(){
	for(auto it=textures.begin(); it!=textures.end(); ++it){
		delete (*it).second;
	}
	textures.clear();
	for(auto it=sounds.begin(); it!=sounds.end(); ++it){
		delete (*it).second;
	}
	sounds.clear();
	for(auto it=fonts.begin(); it!=fonts.end(); ++it){
		delete (*it).second;
	}
	fonts.clear();
}

void ResourceManager::loadTexture(const std::string& name,const std::string& filename){
	sf::Texture *texture = new sf::Texture();
	if(texture->loadFromFile(filename) == false){
		delete texture;
		throw std::runtime_error("Texture of specified file name not found.");
	} else {
		textures[name] = texture;
	}
}

void ResourceManager::loadSoundBuffer(const std::string& name,const std::string& filename){
	sf::SoundBuffer *sound_buffer = new sf::SoundBuffer();
	if(sound_buffer->loadFromFile(filename) == false){
		delete sound_buffer;
		throw std::runtime_error("Sound of specified file name not found.");
	} else {
		sounds[name] = sound_buffer;
	}
}

void ResourceManager::loadFont(const std::string& name,const std::string& filename){
	sf::Font *font = new sf::Font();
	if(font->loadFromFile(filename) == false){
		delete font;
		throw std::runtime_error("Font of specified file name not found.");
	} else {
		fonts[name] = font;
	}
}
void ResourceManager::batchLoadResources(const resources_list_t& list){
    for(auto it=list.begin(); it!=list.end(); ++it){
        const std::string& name     = std::get<0>(*it);
        const std::string& filename = std::get<1>(*it);
        resource_type      type     = std::get<2>(*it);
        switch (type){
            case TEXTURE:
                loadTexture(name,filename);
                break;
            case SOUND:
                loadSoundBuffer(name,filename);
                break;
            case FONT:
                loadFont(name,filename);
                break;
        }
    }
}


ResourceManager* ResourceManager::getInstance(){
	if(instance == nullptr){
		instance = new ResourceManager();
	}
	return instance;
}

ResourceManager::ResourceManager(){

}
ResourceManager::~ResourceManager(){
    releaseAllResources();
}
/*
ResourceManager::ResourceManager(const ResourceManager& other){
}

ResourceManager& ResourceManager::operator=(const ResourceManager& other){
    return *this;
}
*/

}
