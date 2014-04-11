#ifndef SETTINGSABSTRACT_H
#define	SETTINGSABSTRACT_H


#include <string>
#include <json/json.h>
namespace engine{
class SettingsAbstract {
public:
    virtual void loadFromJsonObject(const Json::Value& root) = 0;
    virtual void loadFromJsonString(const std::string& str);
	virtual void loadFromJsonFile(const std::string& filename);
    virtual Json::Value saveToJsonObject() = 0;
    virtual std::string saveToJsonString();
	virtual void saveToJsonFile(const std::string& filename);
};
}


#endif	/* SETTINGSABSTRACT_H */

