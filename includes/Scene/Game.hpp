#ifndef GAME_HPP_
#define GAME_HPP_

#include <nlohmann/json.hpp>
#include "../Assets.hpp"
#include "../Scene.hpp"
#include "../LevelGenerator.hpp"

enum GRAVITY_STATUS
{
	CD_BEFORE_START,
	CD_START,
	COOLDOWN,
	CD_END,

};
class Game : public Scene
{
public:
	Game(sf::RenderWindow *window, Events *event, sf::View *view, sf::Uint32 style) : Scene(window, event, view, style),
																					  _bg(spriteAssets["GameBG"]), _musicbg(audioAssets["MainMenu"])
	{
		_actual_lvl = 0;
		_ballTexture.loadFromFile(textureAssets["Ball"]);
		_rstatus = NONE;
		_gravity = 0.01;
		_dir.x = 0;
		_dir.y = 0.3;
		create_flipper();
		loadGame(LvlAssets[_actual_lvl]);
	}
	~Game() = default;

	void create_flipper()
	{
		_ball = sf::CircleShape(10);
		_ball.setTexture(&_ballTexture);
		_ball.setPosition(sf::Vector2f(500, 300));
		_flipperLeft = sf::RectangleShape(sf::Vector2f(100.f, 5.f));
		_flipperLeft.setRotation(45.f);
		_flipperLeft.setFillColor(sf::Color::Green);
		_flipperLeft.setPosition(sf::Vector2f(480, 500));
		_flipperRight = sf::RectangleShape(sf::Vector2f(100.f, 5.f));
		_flipperRight.setOrigin(sf::Vector2f(100, 0));
		_flipperRight.setRotation(-45.f);
		_flipperRight.setFillColor(sf::Color::Blue);
		_flipperRight.setPosition(sf::Vector2f(670, 500));
	}
	void loadGame(std::string lvl_name)
	{
		_lvlgen.parseLvl(lvl_name);
		_walls = _lvlgen.createWalls();
		_bumpers = _lvlgen.createBumpers();
		_tiles = _lvlgen.createTiles();
		initAssets();
	}

	void onClickNextLvl()
	{
		_lvlgen.clearAll();
		_sprites.clear();
		_shapes.clear();
		_actual_lvl += 1;
		loadGame(LvlAssets[_actual_lvl]);
	};

	void setBallDirection(sf::Vector2f collidePoint, sf::Vector2f first, sf::Vector2f second)
	{
		sf::Vector2f dirPoint;
		float m = (second.y - first.y) / (second.x - first.x);
		std::cout << "m: " << m << std::endl;
		float m2 = (int)m == 0 ? 0 : (float)(-(1 / (float)m));
		float b2 = collidePoint.y - (m2 * collidePoint.x);
		std::cout << m2 << " b2: " << b2 << std::endl;
		if (collidePoint.y > first.y && collidePoint.y > second.y) {
			(int)m2 == 0 || (int)m2 == -0 ? dirPoint = {0, collidePoint.y + 50} : 
			dirPoint = {((collidePoint.y + 50) / (float)m2) + (-(float)b2 / (float)m2), collidePoint.y + 50};
		}
		else {
			(int)m2 == 0 || (int)m2 == -0 ? dirPoint = {0, collidePoint.y - 50} : 
			dirPoint = {((collidePoint.y - 50) / (float)m2) + (-b2 / (float)m2), collidePoint.y - 50};
		}
		std::cout << dirPoint.x << " " << dirPoint.y << std::endl;
		_dir = {(float)((dirPoint.x - collidePoint.x) / 300.0), (float)((dirPoint.y - collidePoint.y) / 300.0)};
		std::cout << _dir.x << " " << _dir.y << std::endl;
		_gravity = 0;
		_cancelGravity = CD_BEFORE_START;
	};

	void move_ball()
	{
		_ball.setPosition(sf::Vector2f(_ball.getPosition().x + _dir.x, _ball.getPosition().y + _dir.y + _gravity));
		for (auto &w : _walls)
		{
			if (_event->collide(_ball, w))
			{
				sf::Vector2f min(5000, 5000);
				int index_min = 0;
				for (int i = 0; i != w.getPointCount(); i++)
					if (w.getTransform().transformPoint(w.getPoint(i)).x < min.x && w.getTransform().transformPoint(w.getPoint(i)).y < min.y) {
						min = w.getTransform().transformPoint(w.getPoint(i));
						index_min = i;
					}
				if (index_min == w.getPointCount() - 1)
					index_min -= 1;
				setBallDirection(_ball.getPosition(),
					w.getTransform().transformPoint(w.getPoint(index_min)),
					w.getTransform().transformPoint(w.getPoint(index_min + 1)));
			}
			// std::cout << w.getGlobalBounds().left << " " << w.getGlobalBounds().width << std::endl;
		}
		for (auto &t: _tiles) {
		if (_event->collide(_ball, t.getSprite()) && t._display) {
			setBallDirection(_ball.getPosition(),
				t.getSprite().getTransform().transformPoint(t.getSprite().getPosition()),
				t.getSprite().getTransform().transformPoint(sf::Vector2f(t.getSprite().getPosition().x + t.getSprite().getGlobalBounds().width, t.getSprite().getPosition().y))
			);
			t._display = false;
		}
		}
		if (_ball.getPosition().x < 0 || _ball.getPosition().x + _ball.getGlobalBounds().width > 1092 || _ball.getPosition().y < 0)
			_dir = {_dir.x * -1, _dir.y * -1};
		if (_event->collide(_ball, _flipperLeft))
			setBallDirection(_ball.getPosition(),
							 _flipperLeft.getTransform().transformPoint(_flipperLeft.getPoint(0)),
							 _flipperLeft.getTransform().transformPoint(_flipperLeft.getPoint(1)));
		if (_event->collide(_ball, _flipperRight))
			setBallDirection(_ball.getPosition(),
							 _flipperRight.getTransform().transformPoint(_flipperRight.getPoint(0)),
							 _flipperRight.getTransform().transformPoint(_flipperRight.getPoint(1)));
	};

	bool initAssets() override
	{
		//_texts.push_back(_scoreText);
		//_texts.push_back(_lvlText);
		//_texts.push_back(p);
		_sprites.push_back(&_bg);
		_shapes.push_back(&_ball);
		_shapes.push_back(&_flipperLeft);
		_shapes.push_back(&_flipperRight);
		_shapes.push_back(&_ball);
		_audio.push_back(_musicbg);
		for (auto &w : _walls)
			_shapes.push_back(&w);
		for (auto &b : _bumpers)
			_shapes.push_back(&b);
		for (auto &t : _tiles)
			_sprites.push_back(&t);
		return true;
	}

	SCENE action() override
	{
		_event->moveFlippers(&_flipperLeft, &_flipperRight);
		_rstatus = _event->flip(_rstatus);
		_rstatus = _event->onRotate(&_flipperLeft, &_flipperRight, _rstatus);
		move_ball();
		gravityStatus();
		return GAME;
	}

private:
	void gravityStatus()
	{
		if (_cancelGravity == CD_BEFORE_START)
		{
			_cd.restart();
			_cancelGravity = CD_START;
		}
		else if (_cd.getElapsedTime().asMilliseconds() > 1500 && _cancelGravity == CD_START)
		{
			_cd.restart();
			_cancelGravity = COOLDOWN;
		}
		else if (_cd.getElapsedTime().asSeconds() < 4 && _cancelGravity == COOLDOWN)
			_gravity += 0.0001;
		else if (_cd.getElapsedTime().asSeconds() > 4 && _cancelGravity == COOLDOWN)
		{
			_dir.x /= 2;
			_cancelGravity = CD_END;
		}
		else if (_cancelGravity == CD_END)
		{
			_gravity += 0.00001;
		}
	}

private:
	std::map<std::string, SCENE> _scenes;
	Sprite _bg;
	int _actual_lvl;
	long int _score;
	sf::Texture _ballTexture;
	sf::CircleShape _ball;
	sf::RectangleShape _flipperLeft;
	sf::RectangleShape _flipperRight;
	Audio _musicbg;
	LevelGenerator _lvlgen;
	sf::Clock _cd;
	RotateStatus _rstatus;
	float _gravity;
	double angle;
	GRAVITY_STATUS _cancelGravity;
	sf::Vector2f _dir;
	std::vector<sf::ConvexShape> _walls;
	std::vector<sf::CircleShape> _bumpers;
	std::vector<Sprite> _tiles;
	nlohmann::json _map;
};

#endif /* !GAME_HPP_ */
