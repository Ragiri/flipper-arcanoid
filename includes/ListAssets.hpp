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
    std::make_pair("lvl1", "assets/levels/1.tkt"),
    std::make_pair("lvl2", "assets/levels/2.tkt"),
};


inline std::map<std::string, std::string> spriteAssets = {
    std::make_pair("MainMenuBG", "assets/backgrounds/mainmenu.json"),
    std::make_pair("GameBG", "assets/backgrounds/mainmenu.json"),
    std::make_pair("AudioOutside", "assets/sprite/audio_outside.json"),
    std::make_pair("AudioInside", "assets/sprite/audio_inside.json"),
};

inline std::map<std::string, sf::Keyboard::Key> keyboardSet = {
    std::make_pair("Left", sf::Keyboard::Q),
    std::make_pair("Right", sf::Keyboard::D),
    std::make_pair("Flip", sf::Keyboard::Space),
    std::make_pair("Enter", sf::Keyboard::Enter),
};

inline std::map<std::string, std::string> fontAssets = {
    std::make_pair("interface", "assets/font/OpenSans-Bold.ttf"),
};


int countCharacter(std::string s, char c) {
  int count = 0;

  for (int i = 0; i < s.size(); i++)
    if (s[i] == c) count++;
  return count;
}

int findNOccur(std::string str, char ch, int N) {
    int occur = 0;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ch) occur++;
        if (occur == N) return i;
    }
    return -1;
}

template<typename T>
void pop_front(std::vector<T>& vec) { vec.erase(vec.begin()); }

#endif