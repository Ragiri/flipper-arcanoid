#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include "Assets.hpp"
#include <queue>

enum SCENE {
	MENU,
	PAUSE,
	SETTINGS,
	GAME,
	EXIT,
};

class Events {
    public:
        Events() {};
        ~Events() = default;
        bool closed(sf::Window *_window, SCENE s) {
		    while(_window->pollEvent(_event)) {
                if (_event.type == sf::Event::Closed || s == EXIT) {
		    		_window->close();
                    return true;
                }
            }
            return false;
        };
        bool collide(sf::Sprite first, sf::Sprite second) {
            return first.getGlobalBounds().intersects(second.getGlobalBounds());
        };

        bool collide(sf::Sprite first, sf::Vector2f second) {
            return first.getGlobalBounds().contains(second);
        }

        bool collide(sf::Text first, sf::Vector2f second) {
            return first.getGlobalBounds().contains(second);
        }

        bool quadrantTriggered(std::queue<sf::Keyboard::Key> &input_queue) {
            return false;
        };
        sf::Event *getEvent() { return &_event; };
    private:
        sf::Event _event;
        sf::Clock _clock;
};

#endif /* !EVENTS_HPP_ */
