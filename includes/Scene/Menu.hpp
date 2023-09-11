#ifndef MENU_HPP_
#define MENU_HPP_

#include <iostream>
#include "../Scene.hpp" 

class Menu: public Scene {
	public:
		Menu(sf::RenderWindow *window,  Events *event, sf::View *view, sf::Uint32 style): Scene(window, event, view, style), _background(spriteAssets["MainMenuBG"]), _menu(spriteAssets["MainMenu"]),
		q("Quit", {0, 0}, 35, sf::Color::Black), t("GAME", {0, 0}, 35, sf::Color::Black),
		p("Settings", {0, 0}, 35, sf::Color::Black), a(audioAssets["MainMenu"]) {
			std::map<std::string, SCENE> scenes = {
				{"Settings", SETTINGS},
				{"GAME", GAME},
				{"Quit", EXIT},
			};
			_scenes = scenes;
			_menu.setPosition(sf::Vector2f((float)(_background.getSprite().getTextureRect().width / 2) - (_menu.getSprite().getTextureRect().width / 2),
			(float)(_background.getSprite().getTextureRect().height / 2) - (_menu.getSprite().getTextureRect().height / 2)));

			t.setPosition(sf::Vector2f((_background.getSprite().getTextureRect().width / 2) - 50,
			(_background.getSprite().getTextureRect().height / 2) - 100));
			q.setPosition(sf::Vector2f((_background.getSprite().getTextureRect().width / 2) - 50 ,
			(_background.getSprite().getTextureRect().height / 2) + 100));
			p.setPosition(sf::Vector2f((_background.getSprite().getTextureRect().width / 2) - 50 ,
			(_background.getSprite().getTextureRect().height / 2)));
			this->initAssets();
		};
		~Menu() = default;
		void run() {};
		bool initAssets() override {
			_texts.push_back(t);
			_texts.push_back(q);
			_texts.push_back(p);
			_sprites.push_back(&_background);
			_sprites.push_back(&_menu);
			_audio.push_back(a);
			return true;
		}
		SCENE action() override {
			int i = 0;
			for (auto &t: _texts) {
				if(_event->collide(*t.getText(), (sf::Vector2f)sf::Mouse::getPosition(*_window))
				&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					return _scenes[t.getString()];
				}
				i++;
			}
			return MENU;
		}
	private:
		std::map<std::string, SCENE> _scenes;
		Sprite _background;
		Sprite _menu;
		Text q;
		Text p;
		Text t;
		Audio a;
};

#endif /* !MENU_HPP_ */
