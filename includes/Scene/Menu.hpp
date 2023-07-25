#ifndef MENU_HPP_
#define MENU_HPP_

#include <iostream>
#include "../Scene.hpp" 

class Menu: public Scene {
	public:
		Menu(sf::RenderWindow *window,  Events *event): Scene(window, event), s(spriteAssets["MainMenuBG"]),
		q("Quit", {150, 100}, 14, sf::Color::White), t("Test", {150, 50}, 14, sf::Color::White),
		a(audioAssets["MainMenu"]) {
			std::map<std::string, SCENE> scenes = {
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
		Text t;
		Audio a;
};

#endif /* !MENU_HPP_ */
