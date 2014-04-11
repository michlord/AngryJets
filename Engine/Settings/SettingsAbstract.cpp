#include "SettingsAbstract.h"

#include <string>
#include <json/json.h>
#include <fstream>
namespace engine{
void SettingsAbstract::loadFromJsonString(const std::string& str){
	Json::Value root;
    Json::Reader reader;
    reader.parse(str, root);
    loadFromJsonObject(root);
}

std::string SettingsAbstract::saveToJsonString(){
	Json::StyledWriter writer;
    std::string output = writer.write( saveToJsonObject() );
    return output;
}

void SettingsAbstract::loadFromJsonFile(const std::string& filename){

	std::fstream in;
	in.open(filename,std::ifstream::in);
	Json::Reader reader;
	Json::Value root;
	bool res = reader.parse(in,root);
	in.close();
    if(res == false)
        throw std::runtime_error("Error parsing json root");
	loadFromJsonObject(root);
}

void SettingsAbstract::saveToJsonFile(const std::string& filename){
	std::fstream out;
	out.open(filename,std::ofstream::out);
	out << saveToJsonObject();

}
}

