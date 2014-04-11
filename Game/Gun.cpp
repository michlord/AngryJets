#include "Gun.h"

namespace game{

Gun::Gun(float frames_between_shots_):
		frames_between_shots(frames_between_shots_),
		remaining_frames(0)
{

}

void Gun::update(){
	if(remaining_frames > 0){
		--remaining_frames;
	}
}

std::list<Bullet*> Gun::shoot(Vehicle* vehicle){
	if(remaining_frames <= 0){
		remaining_frames = frames_between_shots;
		return shootStrategy(vehicle);
	}
	return std::list<Bullet*>();
}



}
