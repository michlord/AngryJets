#pragma once
#ifndef idC6ACCD0E_54A1_4B74_A93966CA6DE0ADBD
#define idC6ACCD0E_54A1_4B74_A93966CA6DE0ADBD

#include "NonCopyable.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <list>
#include <tuple>


#define rm ResourceManager::getInstance()

namespace engine{

/** \brief A resource manager for textures, sounds and fonts.
 *
 * This SINGLETON class manages resources. They can be requested by specifying resource name.
 * Each name uniquely points to a single resource. Trying to add two or more resources
 * with the same name results in only adding the first resource (if it wasn't already added).
 * One can try to avoid name clashes by using namespaces. For instance you can add "house/window"
 * alongside "barn/window".
 *
 * In order to access this class use either
 * engine::ResourceManager::getInstance()->getTexture("name");
 * or shorthand for the above
 * engine::rm->getTexture("name");
 *
 * This class provides a batchLoadResources(const resources_list_t& list) function which
 * takes a typedef'ed list of tuple < std::string, std::string, resource_type >.
 * First string represents resource name that you want to use in your program.
 * Second string is path to a resource file. Resource type is either ResourceManager::TEXTURE,
 * ResourceManager::SOUND or ResourceManager::FONT and must match resource file type.
 * engine::GuiWindow*           menu_window;
    engine::GuiVerticalLayout*   vlayout;
    engine::GuiLabel*            play;
    engine::GuiLabel*            map_select;
    engine::GuiLabel*            ship1_select;
    engine::GuiLabel*            ship2_select;
 */

class ResourceManager : public NonCopyable {
public:
    ~ResourceManager();

    static ResourceManager* getInstance();

	sf::Texture& 		    getTexture(const std::string& name);
	sf::SoundBuffer& 	    getSoundBuffer(const std::string& name);
	sf::Font& 			    getFont(const std::string& name);

	void 				    addTexture(const std::string& name,const sf::Texture& texture);
	void 				    addSoundBuffer(const std::string& name,const sf::SoundBuffer& sound_buffer);
	void 				    addFont(const std::string& name,const sf::Font& font);

	bool 				    releaseTexture(const std::string& name);
	bool 				    releaseSoundBuffer(const std::string& name);
	bool				    releaseFont(const std::string& name);

	void				    releaseAllResources();

	void				    loadTexture(const std::string& name,const std::string& filename);
	void				    loadSoundBuffer(const std::string& name,const std::string& filename);
	void				    loadFont(const std::string& name,const std::string& filename);

	enum resource_type {TEXTURE,SOUND,FONT};

	//<name, file path, type>
	typedef std::list< std::tuple< std::string, std::string, resource_type > > resources_list_t;

	void                    batchLoadResources(const resources_list_t& list);



private:
	ResourceManager();
	//ResourceManager(const ResourceManager& other);
	//ResourceManager& operator=(const ResourceManager& other);

	static ResourceManager*                     instance;
	std::map< std::string, sf::Texture* >		textures;
	std::map< std::string, sf::SoundBuffer* >	sounds;
	std::map< std::string, sf::Font* >			fonts;

};

}
#endif // header
