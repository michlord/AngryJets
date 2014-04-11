
#include "SettingsGame.h"

#include <string>
#include <json/json.h>
#include <stdexcept>
namespace engine{
void SettingsGame::loadFromJsonObject(const Json::Value& root){
	directory	 = root["directory"].asString();
	selected_map = root["selected_map"].asString();
	for(int i=0; i<root["map"].size(); ++i){
        map.push_back(root["map"][i].asString());
	}
	for(int i=0; i<root["ship"].size(); ++i){
        ship.push_back(root["ship"][i].asString());
	}
	fullscreen 	= root["fullscreen"].asBool();
	fps 		= root["fps"].asInt();
	if(root["players"].size() != PLAYER_AMT)
        throw std::runtime_error("Bad amount of players");
	for(int i=0;i<PLAYER_AMT;++i){
		player_settings[i].loadFromJsonObject(root["players"][i]);
	}
}
Json::Value SettingsGame::saveToJsonObject(){
	Json::Value root;
	root["directory"] = directory;
	root["selected_map"] = selected_map;
	root["fullscreen"] = fullscreen;
	root["fps"] = fps;
	Json::Value maps;
	maps.resize(map.size());
	for(int i=0;i<map.size();++i){
        maps[i] = map[i];
	}
	Json::Value ships;
	ships.resize(ship.size());
	for(int i=0;i<ship.size();++i){
        ships[i] = ship[i];
	}
	root["map"] = maps;
	root["ship"] = ships;
	Json::Value players;
	players.resize(PLAYER_AMT);
	for(int i=0;i<PLAYER_AMT;++i){
		players[i] = player_settings[i].saveToJsonObject();
	}
	root["players"] = players;
	return root;
}
}
