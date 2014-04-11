#ifndef SETTINGSMAP_H
#define SETTINGSMAP_H
#include "SettingsAbstract.h"
#include <SFML/System.hpp>
namespace engine{

class SettingsPlayerSpawn : public SettingsAbstract{
public:
	void loadFromJsonObject(const Json::Value& root);
	Json::Value saveToJsonObject();
	sf::Vector2f flag_pos;
	sf::Vector2f ship_pos;
};

class SettingsMap : public SettingsAbstract {
public:
	void loadFromJsonObject(const Json::Value& root);
	Json::Value saveToJsonObject();
	float scale;
	std::string background;
	std::string foreground;
	std::string mask;
	SettingsPlayerSpawn player_spawn[2];
};



}

#endif
