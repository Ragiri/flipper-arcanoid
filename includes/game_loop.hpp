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
		int countCharacter(std::string s, char c) {
		  int count = 0;

		  for (int i = 0; i < s.size(); i++)
		    if (s[i] == c) count++;
		  return count;
		}
		int findNOccur(std::string str, char ch, int N) {
		    int occur = 0;
		    for (int i = 0; i < str.length(); i++) {
		        if (str[i] == ch) occur++;
		        if (occur == N) return i;
		    }
		    return -1;
		}

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
		std::vector<sf::Vector2f> add_to_vector(std::string line, std::vector<sf::Vector2f> vect) {
			int count = countCharacter(line, '(');
			for (int i = 0; i != count; i++) {
				int one = std::stoi(line.substr(findNOccur(line, '(', i + 1) + 1, line.size() - (line.size() - findNOccur(line, ',', i + 1) - 1)));
				int two = std::stoi(line.substr(findNOccur(line, ',', i + 1) + 1, line.size() - (line.size() - findNOccur(line, ')', i + 1) - 1)));
				vect.push_back(sf::Vector2f(one, two));
			}
			return vect;
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
		void print_vect() {
			for (auto &d: _bumper)
				std::cout << d.first.x << " " << d.second << std::endl;
			std::cout << _resolution.x << " " << _resolution.y << std::endl;
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
