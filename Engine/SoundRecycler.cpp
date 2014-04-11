#include "SoundRecycler.h"

engine::SoundRecycler* engine::SoundRecycler::instance = nullptr;

namespace engine{

void SoundRecycler::addSound(sf::Sound* sound){
		sounds.push_back(sound);
}
void SoundRecycler::recycle(){
	for(auto it=sounds.begin();it!=sounds.end();++it){
		if( (*it)->getStatus() == sf::SoundSource::Status::Stopped ){
			delete *it;
			it = sounds.erase(it);
		}
	}
}
SoundRecycler* SoundRecycler::getInstance(){
	if(instance == nullptr)
		instance = new SoundRecycler();
	return instance;
}

SoundRecycler::SoundRecycler(){
}
SoundRecycler::~SoundRecycler(){
    for(auto it = sounds.begin(); it != sounds.end(); ++it){
		delete (*it);
	}
}

}
