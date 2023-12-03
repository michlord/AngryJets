cmake_minimum_required(VERSION 3.27)

project(
	AngryJets
	VERSION 1.0
	LANGUAGES CXX)

find_package(jsoncpp REQUIRED)

set(ENGINE_SRC 
	"Engine/Collision.cpp"
	"Engine/Collision.h"
	"Engine/Gui.h"
	"Engine/NonCopyable.h"
	"Engine/ResourceManager.cpp"
	"Engine/ResourceManager.h"
	"Engine/Settings.h"
	"Engine/SoundRecycler.cpp"
	"Engine/SoundRecycler.h"
	"Engine/Speed.cpp"
	"Engine/Speed.h"
	"Engine/State.cpp"
	"Engine/State.h"
	"Engine/StateMachine.cpp"
	"Engine/StateMachine.h"
	"Engine/StringUtil.h"
	"Engine/Settings/SettingsAbstract.cpp"
	"Engine/Settings/SettingsAbstract.h"
	"Engine/Settings/SettingsGame.cpp"
	"Engine/Settings/SettingsGame.h"
	"Engine/Settings/SettingsKeybinding.cpp"
	"Engine/Settings/SettingsKeybinding.h"
	"Engine/Settings/SettingsMap.cpp"
	"Engine/Settings/SettingsMap.h"
	"Engine/Settings/SettingsPlayer.cpp"
	"Engine/Settings/SettingsPlayer.h"	 
	"Engine/Gui/GuiHighlightedLabel.cpp"
	"Engine/Gui/GuiHorizontalLayout.cpp" 
	"Engine/Gui/GuiLabel.cpp" 
	"Engine/Gui/GuiLayout.cpp" 
	"Engine/Gui/GuiVerticalLayout.cpp" 
	"Engine/Gui/GuiWidget.cpp" 
	"Engine/Gui/GuiWindow.cpp" 
	"Engine/Gui/GuiHighlightedLabel.h" 
	"Engine/Gui/GuiHorizontalLayout.h" 
	"Engine/Gui/GuiLabel.h" 
	"Engine/Gui/GuiLayout.h" 
	"Engine/Gui/GuiVerticalLayout.h" 
	"Engine/Gui/GuiWidget.h" 
	"Engine/Gui/GuiWindow.h"          
)
add_library(engine ${ENGINE_SRC})
target_compile_features(engine PUBLIC cxx_std_11)
target_include_directories(engine PRIVATE
	"Engine"
	"3rdParty"
)

SET(GAME_SRC
	"Game/Bullet.cpp"
	"Game/Bullet.h"
	"Game/BulletMinigun.cpp"
	"Game/BulletMinigun.h"
	"Game/Collidable.h"
	"Game/Flag.cpp"
	"Game/Flag.h"
	"Game/GameLoop.cpp"
	"Game/GameLoop.h"
	"Game/Ground.cpp"
	"Game/Ground.h"
	"Game/Gun.cpp"
	"Game/Gun.h"
	"Game/GunMinigun.cpp"
	"Game/GunMinigun.h"
	"Game/Hud.cpp"
	"Game/Hud.h"
	"Game/Jetman.cpp"
	"Game/Jetman.h"
	"Game/Player.cpp"
	"Game/Player.h"
	"Game/Ship.cpp"
	"Game/Ship.h"
	"Game/StateGameplay.cpp"
	"Game/StateGameplay.h"
	"Game/StateMenu.cpp"
	"Game/StateMenu.h"
	"Game/Vehicle.cpp"
	"Game/Vehicle.h"
)
add_library(game ${GAME_SRC})
target_compile_features(game PUBLIC cxx_std_11)
target_include_directories(game PRIVATE
	"Game"
	"Engine"
	"3rdParty"
)
target_link_libraries(game
	engine
)




find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(angryjets
	main.cpp
)
target_compile_features(angryjets PUBLIC cxx_std_11)
target_link_libraries(angryjets
	engine
	game
	sfml-graphics
	sfml-audio
	jsoncpp_lib
)
target_include_directories(angryjets PRIVATE
	"Game"
	"Engine"
	"3rdParty"
)