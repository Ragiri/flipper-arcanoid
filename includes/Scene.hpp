#ifndef SCENE_HPP_
#define SCENE_HPP_
#include "Events.hpp"
#include "ListAssets.hpp"

class Scene {
    public:
        Scene(sf::RenderWindow *window, Events *event): _window(window), _event(event) {
            _sprites.clear();
            _texts.clear();
            _audio.clear();
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
                if (a._active)
                    a.play();
            
        }
        virtual SCENE action() = 0;
        virtual bool initAssets() = 0;
    protected:
        sf::RenderWindow *_window;
        std::vector<Text> _texts;
        std::vector<Sprite*> _sprites;
        std::vector<Audio> _audio;
        AnimationManagement _am;
        Events *_event;
};

#endif /* !SCENE_HPP_ */
