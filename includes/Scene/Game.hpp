#ifndef GAME_HPP_
#define GAME_HPP_

#include <nlohmann/json.hpp>
#include "../Assets.hpp"
#include "../Scene.hpp"
#include "../LevelGenerator.hpp"

class Game: public Scene {
    public:
        Game(sf::RenderWindow *window,  Events *event): Scene(window, event), _bg(spriteAssets["MainMenuBG"]), _audio(audioAssets["MainMenu"]) {
        }
        ~Game() = default;

		void loadGame(std::string lvl_name) {
			_lvlgen.parseLvl(lvl_name);
			_walls = _lvlgen.createWalls();
			_bumpers = _lvlgen.createBumpers();
			_tiles = _lvlgen.createTiles();
			for (auto &w: _walls)
				_shapes.push_back(&w);
			for (auto &b: _bumpers)
				_shapes.push_back(&b);
			for (auto &t: _tiles)
				_sprites.push_back(&t);
		}

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
		Sprite _ball;
		sf::RectangleShape _flipperLeft;
		sf::RectangleShape _flipperRight;
		Audio _audio;
		LevelGenerator _lvlgen;
		std::vector<sf::ConvexShape> _walls;
		std::vector<sf::CircleShape> _bumpers;
		std::vector<Sprite> _tiles;
        nlohmann::json _map;

};

#endif /* !GAME_HPP_ */
