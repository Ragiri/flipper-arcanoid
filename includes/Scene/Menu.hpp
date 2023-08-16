#ifndef MENU_HPP_
#define MENU_HPP_

#include <iostream>
#include "../Scene.hpp" 

class Menu: public Scene {
	public:
		Menu(sf::RenderWindow *window,  Events *event): Scene(window, event), s(spriteAssets["MainMenuBG"]),
		q("Quit", {500, 400}, 35, sf::Color::White), t("GAME", {500, 300}, 35, sf::Color::White),
		p("Settings", {500, 350}, 35, sf::Color::White), a(audioAssets["MainMenu"]) {
			std::map<std::string, SCENE> scenes = {
				{"Settings", SETTINGS},
				{"GAME", GAME},
				{"Quit", EXIT},
			};
			_scenes = scenes;
			this->initAssets();
		};
		~Menu() = default;
		void run() {};
		bool initAssets() override {
			_texts.push_back(t);
			_texts.push_back(q);
			_texts.push_back(p);
			_sprites.push_back(&s);
			_audio.push_back(a);
			return true;
		}
		SCENE action() override {
			for (auto &t: _texts) {
				if(_event->collide(*t.getText(), (sf::Vector2f)sf::Mouse::getPosition(*_window))
				&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					return _scenes[t.getString()];
				}
			}
			return MENU;
		}
	private:
		std::map<std::string, SCENE> _scenes;
		Sprite s;
		Text q;
		Text p;
		Text t;
		Audio a;
};

#endif /* !MENU_HPP_ */
