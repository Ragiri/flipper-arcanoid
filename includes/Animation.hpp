#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <map>
#include <fstream>
#include "ListAssets.hpp"

class Animation {
    public:
        Animation(bool active, nlohmann::json json, std::string animationName, sf::Sprite *s) {
            _active = active;
            _json = json;
            _animationName = animationName;
            sprite = s;
            //step_left = 0;
            //step_top = 0;
        };
        void triggered() {
        };

        void animationFinished() {
            if (_json["animation"][_animationName]["index"] != nullptr)
                _animationName = _json["animation"][_animationName]["index"];
            else if (!_json["animation"][_animationName]["loop"])
                _animationName = "idle";
        };
        void animate() {
			static int dir = 1;
            static int step_left = 0;
            static int step_top = 0;

            std::cout << _json["animation"][_animationName]["step_left"].size() << std::endl;
            std::cout << step_left << std::endl;
			sprite->setTextureRect(sf::IntRect((int)_json["animation"][_animationName]["step_left"].at(step_left), 
			((int)_json["animation"][_animationName]["step_top"].at(step_top)), _json["animation"][_animationName]["size"].at(0),
			_json["animation"][_animationName]["size"].at(1)));

            step_left = dir < 0 ? step_left - 1 : step_left + 1;
            step_top = dir < 0 ? step_top - 1 : step_top + 1;

			if ((_json["animation"][_animationName]["step_left"].size() - 1 == step_left || step_left <= 0) &&
                (_json["animation"][_animationName]["step_top"].size() - 1 == step_top || step_top <= 0) &&
				_json["animation"][_animationName]["reversible"])
                    dir *= -1;
                else _active = false;
        };
        std::string getAnimationName() { return _animationName; };
        float getDuration() { return _json["animation"][_animationName]["duration"]; };
		bool _active;
        ~Animation() = default;
    private:
        nlohmann::json _json;
        std::string _animationName;
        sf::Sprite *sprite;
};

#endif /* !ANIMATION_HPP_ */
