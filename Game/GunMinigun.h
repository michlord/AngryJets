#pragma once
#ifndef id665CF2CE_F98B_45E4_92075DBAE7611800
#define id665CF2CE_F98B_45E4_92075DBAE7611800
#include "Gun.h"
namespace game{
class GunMinigun : public Gun{
public:
	GunMinigun(float frames_between_shots_);
private:
	virtual std::list<Bullet*> shootStrategy(Vehicle* vehicle);
};

}

#endif // header
