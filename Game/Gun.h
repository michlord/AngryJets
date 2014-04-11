#pragma once
#ifndef id51E1506A_9B2F_447A_9DEDDF902EED2DBC
#define id51E1506A_9B2F_447A_9DEDDF902EED2DBC

#include "Vehicle.h"
#include <list>
#include "Bullet.h"

namespace game{
class Gun {
public:
	Gun(float frames_between_shots_);
	virtual void update();
	virtual std::list<Bullet*> shoot(Vehicle* vehicle);
protected:
	virtual std::list<Bullet*> shootStrategy(Vehicle* vehicle) = 0;
	float frames_between_shots;
	float remaining_frames;
	//sf::Vector2f getVehicleNose(Vehicle* vehicle);
	//sf::Vector2f getSpeedVector(Vehicle* vehicle,float speed);
private:
};
}

#endif // header
