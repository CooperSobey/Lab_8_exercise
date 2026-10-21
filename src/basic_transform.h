#ifndef BASIC_TRANSFORM_H
#define BASIC_TRANSFORM_H

#include <cassert>

#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    //NOTE: basic transform is (scale, transform)
    // TODO: Determine if possible in general, else provide counterexample:
    // compose(f, g) is equivalent to first applying g, then applying f.
    static BasicTransform compose(const BasicTransform& f, const BasicTransform& g) {
        return {sf::Vector2f{f.scale.x * g.scale.x, f.scale.y * g.scale.y}, sf::Vector2f{f.scale.x * g.translation.x + f.translation.x, f.scale.y * g.translation.y + f.translation.y}};
        //Apply Scale
        //sf::Vector2f{f.scale.x * g.scale.x, f.scale.y * g.scale.y};
        //Apply translation
        //sf::Vector2f{f.scale.x * g.translation.x + f.translation.x, f.scale.y * g.translation.y + f.translation.y};
    };

    // TODO: Determine if possible in general, else provide counterexample:
    static BasicTransform inverse(const BasicTransform& f) {
        return {
            sf::Vector2f(1/f.scale.x, 1/f.scale.y), sf::Vector2f(-f.translation.x / (1/f.scale.x), -f.translation.y / (1/f.scale.y))

        };
        //Has to be one to one and onto:
        //One to one: no two inputs have the same outputs
        //Fails if we have a 0 in the scale. but since we ignore that case it passes one to one
        //Onto: Every output in codomain is hit. cant think of a place where it fails, look into more

        //y-1 = (1/scale) * y + (-transform/scale)
        //      scale var       transform var
    };

    constexpr BasicTransform(const sf::Vector2f& scale = {1.f, 1.f},
                             const sf::Vector2f& translation = {0.f, 0.f})
        : scale{scale}, translation{translation} {}

    constexpr sf::Vector2f applyPoint(const sf::Vector2f& p) const {
        // first scale, then translate -- if you do the reverse, the translation gets messed up.
        return {p.x * scale.x + translation.x, p.y * scale.y + translation.y};
    }

    constexpr sf::Vector2f applyVector(const sf::Vector2f& p) const {
        // vectors are not translated by transformations
        return {p.x * scale.x, p.y * scale.y};
    }

    constexpr bool operator==(const BasicTransform& other) const {
        return scale == other.scale && translation == other.translation;
    }

    sf::Vector2f scale;
    sf::Vector2f translation;
};

#endif