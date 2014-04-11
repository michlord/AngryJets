

#include "SettingsPlayer.h"

#include <string>
#include <json/json.h>
namespace engine{
void SettingsPlayer::loadFromJsonObject(const Json::Value& root){
	name = root["name"].asString();
	flag = root["flag"].asString();
	ship = root["ship"].asString();
	keybinding.loadFromJsonObject(root["keybinding"]);
}
Json::Value SettingsPlayer::saveToJsonObject(){
	Json::Value root;
	root["name"] = name;
	root["flag"] = flag;
	root["ship"] = ship;
	root["keybinding"] = keybinding.saveToJsonObject();
	return root;
}
}