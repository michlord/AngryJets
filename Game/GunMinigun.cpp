#include "GunMinigun.h"
#include "BulletMinigun.h"
#include "../Engine/ResourceManager.h"

namespace game{
GunMinigun::GunMinigun(float frames_between_shots_):
	Gun(frames_between_shots_){
}
std::list<Bullet*> GunMinigun::shootStrategy(Vehicle* vehicle){
	std::list<Bullet* > list;
	//Bullet * bullet = new BulletMinigun(getVehicleNose(vehicle),getSpeedVector(vehicle,13),&engine::rm->getTexture("gameplay/ammo/minigun"));
	Bullet * bullet = new BulletMinigun(vehicle->getNose(),vehicle->getBulletSpeedVector(13),&engine::rm->getTexture("gameplay/ammo/minigun"));
	if(vehicle->canRequestAmmo(bullet->getAmmoCost())){
		vehicle->ammo -= bullet->getAmmoCost();
		bullet->onLaunch();
		list.push_back(bullet);
	} else {
		delete bullet;
	}
	return list;
}

}
