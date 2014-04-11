#include "SettingsMap.h"

namespace engine{


void SettingsMap::loadFromJsonObject(const Json::Value& root){
	scale       = root["scale"].asDouble();
	background  = root["graphics"]["background"].asString();
	mask        = root["graphics"]["mask"].asString();
	foreground  = root["graphics"]["foreground"].asString();
	for(int i=0;i<2;++i){
		player_spawn[i].loadFromJsonObject(root["player_spawn"][i]);
	}
}

Json::Value SettingsMap::saveToJsonObject(){
	//nothing
	return Json::Value();
}

void SettingsPlayerSpawn::loadFromJsonObject(const Json::Value& root){
	flag_pos.x = root["flag"]["x"].asDouble();
	flag_pos.y = root["flag"]["y"].asDouble();
	ship_pos.x = root["ship"]["x"].asDouble();
	ship_pos.y = root["ship"]["y"].asDouble();

}

Json::Value SettingsPlayerSpawn::saveToJsonObject(){
	//nothing
	return Json::Value();
}



}
