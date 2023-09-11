#ifndef GAME_HPP_
#define GAME_HPP_

#include <nlohmann/json.hpp>
#include "../Assets.hpp"
#include "../Scene.hpp"
#include "../LevelGenerator.hpp"

class Game: public Scene {
    public:
        Game(sf::RenderWindow *window,  Events *event, sf::View *view, sf::Uint32 style): Scene(window, event, view, style),
		_bg(spriteAssets["GameBG"]), _musicbg(audioAssets["MainMenu"]){
			_actual_lvl = 0;
			loadGame(LvlAssets[_actual_lvl]);
        }
        ~Game() = default;

		void loadGame(std::string lvl_name) {
			_lvlgen.parseLvl(lvl_name);
			_walls = _lvlgen.createWalls();
			_bumpers = _lvlgen.createBumpers();
			_tiles = _lvlgen.createTiles();
			initAssets();
		}

		void onClickNextLvl() {
			_lvlgen.clearAll();
			_sprites.clear();
			_shapes.clear();
			_actual_lvl += 1;
			loadGame(LvlAssets[_actual_lvl]);
		};
		bool initAssets() override {
			//_texts.push_back(_scoreText);
			//_texts.push_back(_lvlText);
			//_texts.push_back(p);
			_sprites.push_back(&_bg);
			_shapes.push_back(&_ball);
			_shapes.push_back(&_flipperLeft);
			_shapes.push_back(&_flipperRight);
			_audio.push_back(_musicbg);
			for (auto &w: _walls)
				_shapes.push_back(&w);
			for (auto &b: _bumpers)
				_shapes.push_back(&b);
			for (auto &t: _tiles)
				_sprites.push_back(&t);
			return true;
		}

        SCENE action() override {
			for (auto &t: _texts) {
				if((_event->collide(*t.getText(), (sf::Vector2f)sf::Mouse::getPosition(*_window))
				&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					return _scenes[t.getString()];
				}
			}
			return GAME;
		}

    private:
		std::map<std::string, SCENE> _scenes;
		Sprite _bg;
		int _actual_lvl;
		long int _score;
		sf::CircleShape _ball;
		sf::RectangleShape _flipperLeft;
		sf::RectangleShape _flipperRight;
		Audio _musicbg;
		LevelGenerator _lvlgen;
		std::vector<sf::ConvexShape> _walls;
		std::vector<sf::CircleShape> _bumpers;
		std::vector<Sprite> _tiles;
        nlohmann::json _map;

};

#endif /* !GAME_HPP_ */
