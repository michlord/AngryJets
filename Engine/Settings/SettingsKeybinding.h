#ifndef SETTINGSKEYBINDING_H
#define	SETTINGSKEYBINDING_H


#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <json/json.h>
#include "SettingsAbstract.h"
namespace engine{
class SettingsKeybinding : public SettingsAbstract {
public:
    void loadFromJsonObject(const Json::Value& root);
    Json::Value saveToJsonObject();

    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key up;
    sf::Keyboard::Key primary;
    sf::Keyboard::Key secondary;
};
}


#endif	/* SETTINGSKEYBINDING_H */

