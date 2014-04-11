#include "SettingsKeybinding.h"
#include <string>
#include <SFML/Window/Keyboard.hpp>
namespace engine{
void SettingsKeybinding::loadFromJsonObject(const Json::Value& root) {
    left = static_cast<sf::Keyboard::Key>(root["left"].asInt());
    right = static_cast<sf::Keyboard::Key>(root["right"].asInt());
    up = static_cast<sf::Keyboard::Key>(root["up"].asInt());
    primary = static_cast<sf::Keyboard::Key>(root["primary"].asInt());
    secondary = static_cast<sf::Keyboard::Key>(root["secondary"].asInt());
}

Json::Value SettingsKeybinding::saveToJsonObject() {
    Json::Value root;
    root["left"] = (static_cast<int> (left));
    root["right"] = (static_cast<int> (right));
    root["up"] = (static_cast<int> (up));
    root["primary"] = (static_cast<int> (primary));
    root["secondary"] = (static_cast<int> (secondary));
    return root;
}

}