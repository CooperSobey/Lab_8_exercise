#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <map>

#include "sprite.h"
#include <SFML/Graphics.hpp>

using SpriteID = size_t;

class SpriteManager {

public:
    template <typename... Args>
    SpriteID createSprite(Args&&... args) {
        sprites.emplace_back(std::forward<Args>(args)...);
        return sprites.size() - 1;
    }

    sf::Texture& registerTexture(const std::string& filepath) {
        //idempotent check, makes sure double registering returns the same reference
        if (textures.find(filepath) != textures.end()) {
            return textures.find(filepath)->second;
        }

        textures.emplace(filepath, sf::Texture(filepath));
        return textures.at(filepath);
    }

    Sprite& getSprite(SpriteID id) {
        return sprites[id];
    }
private:
std::vector<Sprite> sprites;
std::map<std::string, sf::Texture> textures;

};

#endif  // SPRITE_MANAGER_H
