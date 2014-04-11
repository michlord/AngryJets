#include "StateMachine.h"
namespace engine{
StateMachine::StateMachine(){
	current_state = nullptr;
}

StateMachine::~StateMachine(){
	for(auto it=states.begin();it!=states.end();++it){
        if(it->second != nullptr)
            delete it->second;
	}
}

void StateMachine::handleEvents(const sf::Event& event){
	if(current_state != nullptr){
		current_state->handleEvents(event);
	}
}

void StateMachine::update(){
	if(current_state != nullptr){
		current_state->update();
	}
}

void StateMachine::draw(){
	if(current_state != nullptr){
		current_state->draw();
	}
}

void StateMachine::addState(const std::string& name, State* state){
	states[name] = state;
}

void StateMachine::removeState(const std::string& name){
	auto it = states.find(name);
	if(it != states.end())
		states.erase(it);
}

void StateMachine::switchState(const std::string& name){
	auto it = states.find(name);
	if(it != states.end()){
        if(current_state != nullptr)
                current_state->onExit();
		current_state = it->second;
		if(current_state != nullptr)
            current_state->onEnter();
	}
}

}
