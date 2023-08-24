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
		sf::Vector2f _resolution;

	public:
		game_loop(int x, int y): _sm(&_window, &_events) {
			_window.setKeyRepeatEnabled(false);
		};
		~game_loop() = default;
		bool createWindow() {
			_window.create(sf::VideoMode(_resolution.x, _resolution.y), "Flipper");
			return true;
		}
		sf::RenderWindow *getWindow() {
			return &_window;
		}

		void parse_map(std::string map_name) {
			std::string tmp;
			std::ifstream f(map_name);
			if (f.is_open()) {
    			getline(f,tmp);
				_resolution = sf::Vector2f(std::stoi(tmp.substr(0, tmp.size() - (tmp.size() - findNOccur(tmp, ',', 1) - 1))),
				std::stoi(tmp.substr(findNOccur(tmp, ',', 1) + 1, tmp.size() - findNOccur(tmp, '(', 1) + 1)));
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
