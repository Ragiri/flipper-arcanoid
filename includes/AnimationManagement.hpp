#ifndef ANIMATIONMANAGEMENT_HPP_
#define ANIMATIONMANAGEMENT_HPP_

#include "ListAssets.hpp"
#include "Animation.hpp"

class AnimationManagement {
    public:
        AnimationManagement() {

        };
        void addAnimation(nlohmann::json json, sf::Sprite *s, std::string animationName) {
            _animations.push_back(Animation(true, json, animationName, s));
        };
        std::vector<Animation> getAnimations() { return _animations; };
        //Animation getAnimation(std::string animationName) {
        //    for (auto &a: _animations)
        //        if (a.getAnimationName() == animationName)
        //            return a;
        //    return _animations.at(0);
        //};
        ~AnimationManagement() = default;
    private:
        std::vector<Animation> _animations;
};

#endif /* !ANIMATIONMANAGEMENT_HPP_ */
