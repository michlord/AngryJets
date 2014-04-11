#include "Speed.h"


namespace engine{

Speed::Speed(float pixels_per_second_):
pixels_per_second(pixels_per_second_){
}
void Speed::setSpeed(float pixels_per_second_){
	pixels_per_second = pixels_per_second_;
}
float Speed::asPixelsPerSecond(){
	return pixels_per_second;
}
float Speed::asPixelsPerFrame(){
	return pixels_per_second*time_step;
}
static void Speed::setTimeStep(float time_step_){
	time_step = time_step_;
}
static float Speed::getTimeStep(){
	return time_step;
}


}