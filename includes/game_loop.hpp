#ifndef GAME_LOOP_HPP_
#define GAME_LOOP_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "SceneManagement.hpp"
#include "Events.hpp"

//enum Action {
//	SLITHE_PROBE,
//	DISCARD_PROBE,
//	GO_DOWN,
//	JUMP,
//};

class game_loop
{
	private:
		sf::RenderWindow _window;
		Events _events;
		sf::View _view;
		SceneManagement _sm;
		sf::Vector2f _resolution;

	public:
		game_loop(int x, int y): _sm(&_window, &_events, sf::Style::Default, &_view) {
			_window.setKeyRepeatEnabled(false);
			_resolution.x = x;
			_resolution.y = y;
			_view.setSize(_window.getSize().x, _window.getSize().y);
			_window.setView(_view);
		};
		~game_loop() = default;
		bool createWindow() {
			_window.create(sf::VideoMode(_resolution.x, _resolution.y), "Flipper");
			return true;
		}
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
