#ifndef SCENE_HPP_
#define SCENE_HPP_
#include "Events.hpp"
#include "ListAssets.hpp"

class Scene {
    public:
        Scene(sf::RenderWindow *window, Events *event, sf::View *view, sf::Uint32 style): _window(window), _event(event), _view(view) {
            _sprites.clear();
            _texts.clear();
            _audio.clear();
            _style = style;
        };
        ~Scene() = default;
        void run() {
            for (auto &animation: _am.getAnimations()) {
                if (animation._active)
                    animation.animate();
            }
            for (auto &s: _sprites)
                if (s->_display)
                    s->display(_window);
            for (auto &t: _texts)
                if (t._display)
                    t.displayText(_window);
            for (auto &a: _audio)
                if (a._active && !a.playing())
                    a.play();
            for (auto &s: _shapes)
                _window->draw(*s);
            
        }
        void onResise(int x, int y) {
            _window->setSize(sf::Vector2u(x, y));
            for (auto &s: _sprites)
                s->getSprite().setScale(sf::Vector2f(_window->getSize().x / s->getSprite().getLocalBounds().width, _window->getSize().y / s->getSprite().getLocalBounds().height));
        };
        void onChangeStyle(sf::Uint32 style) {
            _window->create(sf::VideoMode(_window->getSize().x , _window->getSize().y), "Flipper", style);
            //_window->setView(*_view);
        };
        virtual SCENE action() = 0;
        virtual bool initAssets() = 0;
    protected:
        sf::RenderWindow *_window;
        sf::Uint32 _style;
        std::vector<Text> _texts;
		sf::View *_view;
        std::vector<Sprite*> _sprites;
        std::vector<sf::Shape*> _shapes;
        std::vector<Audio> _audio;
        AnimationManagement _am;
        Events *_event;
};

#endif /* !SCENE_HPP_ */
