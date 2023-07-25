#ifndef GAME_HPP_
#define GAME_HPP_

#include <nlohmann/json.hpp>
#include "../Assets.hpp"
#include "../Scene.hpp"


class Game: public Scene {
    public:
        Game(sf::RenderWindow *window,  Events *event): Scene(window, event), _bg(spriteAssets["MainMenuBG"]), _audio(audioAssets["MainMenu"]) {
        }
        ~Game() = default;

        void loadLvl(std::string lvl_name) {
            std::ifstream m(LvlAssets[lvl_name]);
			_map = nlohmann::json::parse(m);
        };

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
		Audio _audio;
        nlohmann::json _map;
};

#endif /* !GAME_HPP_ */
