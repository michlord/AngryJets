AngryJets
===
A split-screen game for two players. Capture the opponent's flag to score 5 points. Killing the opponent gives you 1 point.
Game ends when one of the players runs out of lives. 

Left player controls:

+ left, right and up arrows for steering
+ down arrow for shooting

Right player controls:

+ WAD keys for steering
+ S key for shooting

Running the game
---
In Win32exe there is AngryJets.exe file that you can run on Windows. Before first run set appropriate directory path in
/Assets/settings.json file.

Compilation
---
Due to the Code::Block's poor project handling I was unable to provide cross-platform automated build.
I am planning to devise some CMake build scripts in the future. For now you have to specify appropriate build dependencies
in Code::Block's compiler options. They are outlined in Doc/Dokumentacja.pdf file (sorry - Polish lang. only).
The game uses following libs: SFML 2.1, [jsoncpp](http://jsoncpp.sourceforge.net/), [sigslot](http://sigslot.sourceforge.net/).
I've included them in Lib.7z archive.

Assets license
---
This is a clone of a game called ["Jetmen REVIVAL"](http://www.crew42.dk/).
The graphics were straight ripped from the mentioned game. Sound effects come from
[opengameart.org](http://opengameart.org). I've made this game for educational purposes and mostly care to share
the code, the assets are just placeholders. If you are the owner of any of the assets and don't want them to be
published with my game, please contact me - I will take it down.

Screenshots
---
![Image](screenshots/menu.png?raw=true)
![Image](screenshots/gameplay.png?raw=true)

Todo
---
At the time I was writing this game I didn't remember to use virtual destructors...
This should probably be fixed.