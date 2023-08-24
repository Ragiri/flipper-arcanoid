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
        sf::Keyboard::Key getKeySetting(sf::Window *_window) {
		    while(_window->pollEvent(_event)) {
				while (!_event.KeyPressed);
				return _event.key.code;
            }
        }
        bool collide(sf::Sprite first, sf::Sprite second) {
            return first.getGlobalBounds().intersects(second.getGlobalBounds());
        };
        bool collide(sf::Sprite first, sf::Vector2f second) {
            return first.getGlobalBounds().contains(second);
        }
        bool collide(sf::RectangleShape first, sf::FloatRect second) {
            return first.getGlobalBounds().intersects(second);
        }
        bool collide(sf::Text first, sf::Vector2f second) {
            return first.getGlobalBounds().contains(second);
        }
        void moveFlippers(sf::Sprite *left, sf::Sprite *right) {
            if (sf::Keyboard::isKeyPressed(keyboardSet["Left"])) {
                left->setPosition(sf::Vector2f(left->getPosition().x - 2, left->getPosition().y));
                right->setPosition(sf::Vector2f(right->getPosition().x - 2, right->getPosition().y));
            }
            if (sf::Keyboard::isKeyPressed(keyboardSet["Right"])) {
                left->setPosition(sf::Vector2f(left->getPosition().x + 2, left->getPosition().y));
                right->setPosition(sf::Vector2f(right->getPosition().x + 2, right->getPosition().y));
            }
        }
        sf::Event *getEvent() { return &_event; };
    private:
        sf::Event _event;
        sf::Clock _clock;
};

#endif /* !EVENTS_HPP_ */
