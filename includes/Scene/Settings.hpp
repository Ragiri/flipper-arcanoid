#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <nlohmann/json.hpp>
#include <filesystem>
#include "../Assets.hpp"
#include "../Scene.hpp"

class Settings: public Scene {
    public:
        Settings(sf::RenderWindow *window,  Events *event, sf::View *view, sf::Uint32 style): Scene(window, event, view, style), 
		_bg(spriteAssets["MainMenuBG"]), _a(audioAssets["MainMenu"]),
		outside(spriteAssets["AudioOutside"]), inside(spriteAssets["AudioInside"]) {

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
				if(j["type"] == "audio") {
					outside.setPosition(sf::Vector2f(tmp.getText()->getPosition().x, tmp.getText()->getPosition().y));
					inside.setPosition(sf::Vector2f(tmp.getText()->getPosition().x, tmp.getText()->getPosition().y));
					_audioSettings.insert(std::make_pair(tmp, j["value"]));
					_audio_sliders.insert(std::make_pair(tmp, std::make_pair(outside, inside)));
					_sprites.push_back(&outside);
					_sprites.push_back(&inside);
				} if(j["type"] == "keyboard")
					_keyboardSettings.insert(std::make_pair(tmp, j["value"]));
				if(j["type"] == "graphic")
					_graphicSettings.insert(std::make_pair(tmp, j["value"]));
			}
			_audio.push_back(_a);
			return true;
		}
		void run() {};
		void action_keyboard(Text t) {
			if(_event->collide(*t.getText(), (sf::Vector2f)sf::Mouse::getPosition(*_window))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				_keyboardSettings[t] = _event->getKeySetting(_window);
				keyboardSet[t.getString()] = _keyboardSettings[t];
			}
		}

		void action_audio(Text t) {
			if (_event->collide(_audio_sliders[t].first.getSprite(), (sf::Vector2f)sf::Mouse::getPosition(*_window))) {
				int tmp = _audio_sliders[t].first.getSprite().getTexture()->getSize().x * (1 / 100);
				sf::IntRect actual_size = _audio_sliders[t].second.getSprite().getTextureRect();
				_audioSettings[t] = tmp;
				_audio_sliders[t].second.getSprite().setTextureRect(sf::IntRect(actual_size.left, actual_size.top, tmp,actual_size.height));
			}
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
        std::map<Text, sf::Keyboard::Key> _keyboardSettings;
		std::map<Text, std::pair<Sprite, Sprite>> _audio_sliders;
		std::vector<std::string> _graphic_resolution;
		std::map<Text, int> _audioSettings;
		std::map<Text, int> _graphicSettings;
		Sprite outside;
		Sprite inside;
		Audio _a;
};

#endif /* !SETTINGS_HPP_ */
