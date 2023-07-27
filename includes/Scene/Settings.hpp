#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <nlohmann/json.hpp>
#include <filesystem>
#include "../Assets.hpp"
#include "../Scene.hpp"

class Settings: public Scene {
    public:
        Settings(sf::RenderWindow *window,  Events *event): Scene(window, event), _bg(spriteAssets["MainMenuBG"]), _a(audioAssets["MainMenu"]) {

        };
        ~Settings() = default;

		bool initAssets() override {
			std::ifstream f("/assets/settings_texts");
			nlohmann::json json = nlohmann::json::parse(f);
			for (auto &j: json) {
				Text tmp(j["str"], sf::Vector2f(j["x"], j["y"]), j["size"],
				sf::Color(j["color"][0], j["color"][1], j["color"][2], j["color"][3]));
				if (j["type"] != _actualSettingType)
					tmp._display = false;
				_texts.push_back(tmp);
				if(j["type"] == "audio")
					_audioSettings.insert(make_pair(tmp, j["value"]));
				if(j["type"] == "keyboard")
					_keyboardSettings.insert(make_pair(tmp, j["value"]));
				if(j["type"] == "graphic")
					_graphicSettings.insert(make_pair(tmp, j["value"]));
			}
			_audio.push_back(_a);
			return true;
		}
		void run() {};
		void action_keyboard(Text t) {
			if(_event->collide(*t.getText(), (sf::Vector2f)sf::Mouse::getPosition(*_window))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				while (!_event->getEvent()->KeyPressed);
				_keyboardSettings[t] = _event->getEvent()->key.code;
			}
		}

		void action_audio(Text t) {
			
		}

		void action_graphic(Text t) {
			
		}
		SCENE action() override {
			for (auto &t: _texts) {
				if((t.getString() == "menu" && _event->collide(*t.getText(), (sf::Vector2f)sf::Mouse::getPosition(*_window))
				&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					return MENU;
				if(_actualSettingType == "audio")
					this->action_audio(t);
				if(_actualSettingType == "keyboard")
					this->action_keyboard(t);
				if(_actualSettingType == "graphic")
					this->action_graphic(t);
			}
			return SETTINGS;
		}

    private:
		std::map<std::string, SCENE> _scenes;
		Sprite _bg;
		std::string _actualSettingType;
        std::map<Text, int> _keyboardSettings;
		std::map<Text, int> _audioSettings;
		std::map<Text, int> _graphicSettings;
		Audio _a;
};

#endif /* !SETTINGS_HPP_ */
