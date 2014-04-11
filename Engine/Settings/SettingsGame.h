#ifndef SETTINGSGAME_H
#define	SETTINGSGAME_H

#include "SettingsAbstract.h"
#include "SettingsPlayer.h"
#include <string>
#include <json/json.h>
#include <vector>
namespace engine{
class SettingsGame : public SettingsAbstract {
public:
    void loadFromJsonObject(const Json::Value& root);
    Json::Value saveToJsonObject();

	std::string directory;
	std::string selected_map;
	std::vector< std::string > map;
	std::vector< std::string > ship;
	bool fullscreen;
	int fps;
	static const int PLAYER_AMT = 2;
	SettingsPlayer player_settings[PLAYER_AMT];
};
}


#endif	/* SETTINGSGAME_H */

