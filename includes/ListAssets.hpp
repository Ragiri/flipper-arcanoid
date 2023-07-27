#ifndef LISTASSETS_HPP_
#define LISTASSETS_HPP_
#include <iostream>
#include <map>

enum InputType {
    UP,
    LEFT,
    RIGHT,
    START,
    SELECT,
    SPACE,
};

enum ActionType {
    Move_Right,
    Move_Left,
    Jump,
    Bend_Down,
    Grab,
    Frontal_Attack,
    Ranged_Attack,
};

inline std::map<std::string, std::string> audioAssets = {
    std::make_pair("MainMenu", "assets/audio/mainmenu.json"),
    std::make_pair("Game", "assets/audio/mainmenu.json"),
};

inline std::map<std::string, std::string> settingsAssets = {
    std::make_pair("keyboard_setting", "assets/commandList/Touches.json"),
    std::make_pair("audio_setting", "assets/commandList/AudioSettings.json"),
    std::make_pair("graphics_setting", "assets/commandList/GraphicsSettings.json"),
};

inline std::map<std::string, std::string> LvlAssets = {
    std::make_pair("lvl1", "assets/backgrounds/mainmenu.json"),
    std::make_pair("lvl2", "assets/backgrounds/mainmenu.jpg"),
};


inline std::map<std::string, std::string> spriteAssets = {
    std::make_pair("MainMenuBG", "assets/backgrounds/mainmenu.json"),
    std::make_pair("GameBG", "assets/backgrounds/mainmenu.jpg"),
};


inline std::map<std::string, std::string> fontAssets = {
    std::make_pair("interface", "assets/font/OpenSans-Bold.ttf"),
};

template<typename T>
void pop_front(std::vector<T>& vec) { vec.erase(vec.begin()); }

#endif