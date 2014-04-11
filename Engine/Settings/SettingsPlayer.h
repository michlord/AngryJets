#ifndef SETTINGSPLAYER_H
#define	SETTINGSPLAYER_H

#include "SettingsAbstract.h"
#include "SettingsKeybinding.h"
#include <string>
#include <json/json.h>
namespace engine{
class SettingsPlayer : public SettingsAbstract {
public:
    void loadFromJsonObject(const Json::Value& root);
    Json::Value saveToJsonObject();

	std::string name;
	std::string flag;
	std::string ship;
	SettingsKeybinding keybinding;
};
}


#endif	/* SETTINGSPLAYER_H */

