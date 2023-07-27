#ifndef GAME_LOOP_HPP_
#define GAME_LOOP_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "SceneManagement.hpp"
#include "Events.hpp"

enum Action {
	SLITHE_PROBE,
	DISCARD_PROBE,
	GO_DOWN,
	JUMP,
};

class game_loop
{
	private:
		sf::RenderWindow _window;
		Events _events;
		SceneManagement _sm;
		std::vector<std::vector<sf::Vector2f>> _wall;
		std::vector<sf::Vector2f> _bumper;
		std::vector<sf::Vector2f> _tile;
	public:
		game_loop(int x, int y): _window(sf::VideoMode(x, y), "Flipper"), _sm(&_window, &_events) {
			_window.setKeyRepeatEnabled(false);
		};
		~game_loop() = default;
		sf::RenderWindow *getWindow() {
			return &_window;
		}
		std::vector<sf::Vector2f> add_to_vector(std::string line, std::vector<sf::Vector2f> vect) {
			for (int i = 0; i !=)
		}
		void parse_map(std::string map_name) {
			std::string tmp;
			std::ifstream f(map_name);
			if (f.is_open()) {
    			while (getline(f,tmp)) {
					for (int i = 0; i != tmp.size(); i++) {
						switch (tmp[i])
						{
							case '{':
								_wall.push_back(add_to_vector(tmp, std::vector<sf::Vector2f>()));
								break;
							case '(':
								add_to_vector(tmp, _tile);
								break;
							case '[':
								add_to_vector(tmp, _bumper);
								break;
							default:
								break;
					}
				}
			}
			}
		}
		void loop() {
			while (_window.isOpen()) {
				this->clear();
				_sm.getActualScene()->run();
				SCENE s = _sm.getActualScene()->action();
				_sm.setScene(s);
				_events.closed(&_window, s);
				this->display();
			}
		}
		void clear() {
			_window.clear(sf::Color::Black);
		}
		void display() {
    		_window.display();
		}
};

#endif /* !GAME_LOOP_HPP_ */
