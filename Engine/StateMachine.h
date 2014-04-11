#pragma once
#ifndef idBB599521_6DE7_4969_9991EB1A2421C41D
#define idBB599521_6DE7_4969_9991EB1A2421C41D

#include "State.h"
#include <map>




namespace engine{

class StateMachine{
public:
	StateMachine();
	~StateMachine();
	void handleEvents(const sf::Event& event);
	void update();
	void draw();
	void addState(const std::string& name, State* state);
	void removeState(const std::string& name);
	void switchState(const std::string& name);
private:
	State * current_state;
	std::map < std::string, State* > states;
};

}


#endif // header
