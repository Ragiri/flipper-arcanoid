#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <nlohmann/json.hpp>
#include "../Assets.hpp"
#include "../Scene.hpp"

class Settings: public Scene {
    public:
        Settings(sf::RenderWindow *window,  Events *event): Scene(window, event), _bg(spriteAssets["MainMenuBG"]), _audio(audioAssets["MainMenu"]) {

        };
        ~Settings() = default;

		SCENE action() override {
			for (auto &t: _texts) {
				if((_event->collide(*t.getText(), (sf::Vector2f)sf::Mouse::getPosition(*_window))
				&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					return _scenes[t.getString()];
				}
			}
			return SETTINGS;
		}
        
    private:
		std::map<std::string, SCENE> _scenes;
		Sprite _bg;
        std::map<Text, int> keyboardSettings;
		std::map<Text, int> audioSettings;
		std::map<Text, int> graphicSettings;
		Audio _audio;
};

#endif /* !SETTINGS_HPP_ */
