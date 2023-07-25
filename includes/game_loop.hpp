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
	public:
		game_loop(int x, int y): _window(sf::VideoMode(x, y), "Flipper"), _sm(&_window, &_events) {
			_window.setKeyRepeatEnabled(false);
		};
		~game_loop() = default;
		sf::RenderWindow *getWindow() {
			return &_window;
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
