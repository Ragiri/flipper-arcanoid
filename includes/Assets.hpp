#ifndef ASSETS_HPP_
#define ASSETS_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "AnimationManagement.hpp"

//namespace game {
class Texture {
	public:
	    Texture() {};
	    Texture(std::string path, sf::Vector2i size) {
			if (!_texture.loadFromFile(path, sf::Rect<int>(0,0, size.x, size.y)))
    			std::cerr << "error opening File : " << path << std::endl;
	    };
	    Texture(std::string path) {
		    if (!_texture.loadFromFile(path))
		    	std::cerr << "error opening File : " << path << std::endl;
	    };
	    ~Texture() = default;
	    void setSmooth(bool smooth) {  _texture.setSmooth(smooth); };
	    sf::Texture &getTexture(void) {return this->_texture;};
	    bool isSmooth(void) const {return _texture.isSmooth();};
	private:
	    sf::Texture _texture;
};

class Text {
	public:
		Text(std::string str) {
			_millisecond = 0;
			if (!_font.loadFromFile(fontAssets["interface"]))
            	std::cerr << "Could not load texture" << std::endl;
			this->setStr(str);
			_display = true;
		};
		Text(std::string str, sf::Vector2f vect, int size, sf::Color color) {
			_millisecond = 0;
			if (!_font.loadFromFile(fontAssets["interface"]))
            	std::cerr << "Could not load texture" << std::endl;
			this->setStr(str);
			this->setText(vect, size, color);
			_display = true;
		};
		~Text() = default;
		sf::Text createText(std::string str, sf::Vector2f vect, int size, sf::Color color) {
        	sf::Text text(str, _font, size);
        	text.setPosition(vect);
			text.setFont(_font);
        	text.setFillColor(color);
			text.setCharacterSize(size);
        	_text = text;
        	return text;
    	};
		void setText(sf::Vector2f vect, int size, sf::Color color) {
        	_text.setPosition(vect);
			_text.setCharacterSize(size);
        	_text.setFillColor(color);
			_text.setFont(_font);
    	};
		sf::Text *getText(void) { return &_text; };
		std::string getString(void) { return _initial_str; };
    	void setPosition(sf::Vector2f vect) {_text.setPosition(vect);};
		void setStr(std::string str) {
			_initial_str = str;
			_actual_str = "";
			_text.setString(_actual_str);
		};
    	sf::FloatRect getRect() { return _text.getGlobalBounds(); };
    	void displayTextWithDelay(sf::RenderWindow *window) {
			if (_initial_str == _actual_str) {
    	    		window->draw(_text);
			} else {
				for (int i = 0; i != _initial_str.size(); i++) {
					while (_clock.getElapsedTime().asMicroseconds() < 50000);
					_actual_str.append(_initial_str.substr(i, 1));
					_text.setString(_actual_str);
					window->clear(sf::Color::Black);
    	    		window->draw(_text);
					window->display();
					_clock.restart();
				}
			}
    	};
		void displayText(sf::RenderWindow *window) {
			_text.setString(_initial_str);
    	    window->draw(_text);
		};
		bool _display;
	private:
		std::string _initial_str;
		std::string _actual_str;
		sf::Text _text;
    	sf::Font _font;
		sf::Clock _clock;
		float _millisecond;
		float size;
};

class Audio {
	public:
		Audio(std::string filename) {
			std::ifstream f(filename);
			nlohmann::json _json = nlohmann::json::parse(f);
			_sb.loadFromFile(_json["ressourceName"]);
			_sound.setBuffer(_sb);
            _sound.setVolume(_json["volume"]);
            _sound.setLoop(_json["loop"]);
			_active = _json["active"];
		};
		~Audio() = default;
		void setVolume(float vol) { 
            _json["volume"] = vol;
            _sound.setVolume(vol);
        };
		float getVolume() {return _sound.getVolume(); }
		void setVolumeWithEffect(float vol) {
			if (vol > _sound.getVolume())
				for(;_sound.getVolume() < vol; _sound.setVolume(_sound.getVolume() + 0.3));
			else
				for(;_sound.getVolume() > vol; _sound.setVolume(_sound.getVolume() - 0.3));
		}
		void play() {
			_sound.play();
		};
		void pause() { _sound.pause(); };
		void setSpacial3D(float attenuation, float x, float y, float z) {
			_sound.setAttenuation(attenuation);
			_sound.setPosition(x, y, z);
		};
		bool playing() {
			if (_sound.getStatus() == sf::Sound::Playing)
				return true;
			return false;
		};
		bool _active;
    	sf::Sound *getSound(void) {return &_sound;};
	private:
		nlohmann::json _json;
    	sf::SoundBuffer _sb;
    	sf::Sound _sound;
};

class Sprite {
	public:
		Sprite(std::string filename): _json(nlohmann::json::parse(std::ifstream(filename))) {
			std::cout << "geg" << std::endl;
			_texture = Texture(_json["ressourceName"]).getTexture();
			_sprite.setTexture(_texture);
			_sprite.setTextureRect(sf::IntRect(_json["rect"].at(0), _json["rect"].at(1),
			_json["rect"].at(2), _json["rect"].at(3)));
			_sprite.setPosition(sf::Vector2f(_json["position"].at(0), _json["position"].at(1)));
			_sprite.setScale(sf::Vector2f(_json["scale"].at(0), _json["scale"].at(1)));
			_display = true;
		};
		~Sprite() = default;
		void setPosition(sf::Vector2f pos) { _sprite.setPosition(pos);};
		void setRotation(float rotate) {_sprite.setRotation(rotate);};
		void setScale(sf::Vector2f scale) {_sprite.setScale(scale);};
		void setOrigin(sf::Vector2f pos) {_sprite.setOrigin(pos);};
		void setTexture(sf::Texture &cpy) {
		    _texture = cpy;
		    _sprite.setTexture(_texture);
		};
		void setRect(sf::Rect<int> rect) {_sprite.setTextureRect(rect);};
		void setVisible(bool visible) {_visible = visible;};
		void setMoving(bool move) {_move = move;};
    	sf::Sprite &getSprite(void) {return _sprite;};
    	bool isMove(void) const noexcept {return _move;};
    	bool isVisible(void) const noexcept {return _visible;};
		void display(sf::RenderWindow *win) { win->draw(_sprite);};

		void animate (std::string animationName, AnimationManagement* animationManagement) {
			animationManagement->addAnimation(_json, &_sprite, animationName);
		};
		bool _display;
	private:
		nlohmann::json _json;
    	sf::Texture _texture;
    	sf::Sprite _sprite;
		sf::Clock _clock;
    	bool _visible;
    	bool _move;
};

#endif /* !_HPP_ */
