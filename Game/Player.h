#pragma once
#ifndef id83F93626_7700_432A_A45419540618C9BE
#define id83F93626_7700_432A_A45419540618C9BE

#include "Vehicle.h"
#include "Gun.h"
namespace game{

class Player {
public:
    enum VehicleType {JETMAN,SHIP};
    Player();
    Player(int lives_,int score_,Vehicle* current_vehicle_, Gun* current_primary_gun_,VehicleType vehicle_type_);
	int 			lives;
	int 			score;
	Vehicle*		current_vehicle;
	Gun*            current_primary_gun;
	VehicleType     vehicle_type;

	void onDie();
	void onScore(int amt=1);
private:
};

}

#endif // header
