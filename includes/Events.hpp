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

enum RotateStatus {
    NONE,
    GO_UP,
    GO_DOWN,
};

class Events {
    public:
        Events() {};
        ~Events() = default;
        bool closed(sf::RenderWindow *_window, SCENE s) {
		    while(_window->pollEvent(_event)) {
                if(_event.type == sf::Event::Resized) {
                    sf::FloatRect view(0, 0, _event.size.width, _event.size.height);
                    _window->setView(sf::View(view));
                }
                if (_event.type == sf::Event::Closed || s == EXIT) {
		    		_window->close();
                    return true;
                }
            }
            return false;
        };
        sf::Keyboard::Key getKeySetting(sf::RenderWindow *_window) {
		    while(_window->pollEvent(_event)) {
				while (!_event.KeyPressed);
				return _event.key.code;
            }
        }
        sf::FloatRect coveringRect(const sf::Shape& shape) {
            return shape.getTransform().transformRect(shape.getLocalBounds());
        }
        bool collide(sf::CircleShape c, sf::Vector2f p){
            sf::Vector2f center = c.getPosition();
            float a = (p.x - center.x);
            float b = (p.y - center.y);
            a *= a;
            b *= b;
            float r = c.getRadius() * c.getRadius();
        
            return (( a + b ) < r);
        }
        
        bool collideTransformRect(sf::CircleShape first, sf::RectangleShape second) {
            sf::Vector2f point1 = second.getTransform().transformPoint(second.getPoint(0));
            sf::Vector2f pointTmp = second.getTransform().transformPoint(second.getPoint(0));
            sf::Vector2f point2 = second.getTransform().transformPoint(second.getPoint(1));
            double tmpx = (point2.x - point1.x) / 300.00;
            double tmpy = (point2.y - point1.y) / 300.00;
            for (; ; ) {
                if (pointTmp.x < point2.x)
                    pointTmp.x += tmpx;
                if (pointTmp.y < point2.y)
                    pointTmp.y += tmpy;
                if (((int)pointTmp.x >= (int)point2.x ||(int)pointTmp.x >= (int)point2.x -1 || (int)pointTmp.x >= (int)point2.x +1 )
                && ((int)pointTmp.y >= (int)point2.y ||(int)pointTmp.y >= (int)point2.y -1 || (int)pointTmp.y >= (int)point2.y +1 ))
                    break;
                if (collide(first, pointTmp))
                    return true;
            }
        
            return false;
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
        bool collide(sf::CircleShape first, sf::CircleShape second) {
            return first.getGlobalBounds().intersects(second.getGlobalBounds());
        }
        bool collide(sf::CircleShape first, sf::RectangleShape second) {
            return collideTransformRect(first, second);
        }
        bool collide(sf::CircleShape first, sf::Sprite second) {
            return first.getGlobalBounds().intersects(second.getGlobalBounds());
        }
        bool collide(sf::CircleShape first, sf::ConvexShape second) {
            return second.getGlobalBounds().intersects(first.getGlobalBounds());
        }
        bool collide(sf::Text first, sf::Vector2f second) {
            return first.getGlobalBounds().contains(second);
        }
        RotateStatus flip (RotateStatus s) {
            if (sf::Keyboard::isKeyPressed(keyboardSet["Flip"]) && s == NONE) {
                s = GO_UP;
                std::cout << "flip\n";
            }
            return s;
        }
        void moveFlippers(sf::RectangleShape *left, sf::RectangleShape *right) {
            if (left->getPosition().x > 0 &&sf::Keyboard::isKeyPressed(keyboardSet["Left"])) {
                left->setPosition(sf::Vector2f(left->getPosition().x - 1, left->getPosition().y));
                right->setPosition(sf::Vector2f(right->getPosition().x - 1, right->getPosition().y));
            }
            if (right->getPosition().x < 1092  && sf::Keyboard::isKeyPressed(keyboardSet["Right"])) {
                left->setPosition(sf::Vector2f(left->getPosition().x + 1, left->getPosition().y));
                right->setPosition(sf::Vector2f(right->getPosition().x + 1, right->getPosition().y));
            }
        }
        RotateStatus onRotate(sf::RectangleShape *left, sf::RectangleShape *right, RotateStatus s) {
            if (s == GO_UP) {
                left->rotate(-0.1);
                right->rotate(0.1);
                if ((int)left->getRotation() <= 0)
                    s = GO_DOWN;
            } if (s == GO_DOWN) {
                left->rotate(0.1);
                right->rotate(-0.1);
                if ((int)left->getRotation() >= 45)
                    s = NONE;
            }
            return s;
        };
        sf::Event *getEvent() { return &_event; };
    private:
        sf::Event _event;
        sf::Clock _clock;
};

#endif /* !EVENTS_HPP_ */
