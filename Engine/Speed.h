#pragma once
#ifndef id8041B29F_4941_4909_9A68A4A792CD88FE
#define id8041B29F_4941_4909_9A68A4A792CD88FE

namespace engine{

class Speed{
public:
	Speed(float pixels_per_second_);
	void 			setSpeed(float pixels_per_second_);
	float 			asPixelsPerSecond();
	float 			asPixelsPerFrame();
	static void 	setTimeStep(float time_step);
	static float 	getTimeStep();
private:
	float 			pixels_per_second;
	static float 	time_step;
};
}

#endif // header
