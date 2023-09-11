#ifndef SCENEMANAGEMENT_HPP_
#define SCENEMANAGEMENT_HPP_
#include <map>
#include <unordered_map>
#include "Scene/Menu.hpp"
#include "Scene/Game.hpp"

class SceneManagement {
    public:
        SceneManagement(sf::RenderWindow *window, Events *event, sf::Uint32 style, sf::View *view): m(window, event, view, style),
		g(window, event, view, style) {
			_scenes[MENU] =  &m;
			_scenes[GAME] = &g;
			_actual_scene = MENU;
		};
        ~SceneManagement() = default;

		Scene *getActualScene() {
			return _scenes[_actual_scene];
		}
		SCENE setScene(SCENE s) {
			_actual_scene = s;
			return _actual_scene;
		};
    private:
		std::map<SCENE, Scene *> _scenes;
	    SCENE _actual_scene;
		Menu m;
		Game g;
};

#endif /* !SCENEMANAGEMENT_HPP_ */
